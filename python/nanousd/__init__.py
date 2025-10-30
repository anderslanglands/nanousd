from . import ffi as _lib
from ._get_property import _get_property, GetPropertyError
from ._set_property import _set_property, SetPropertyError
from .tokens import *
from .array import *

import numpy as np

from typing import Any

from ctypes import (
    c_void_p,
    c_bool,
    c_char_p,
    POINTER,
    byref,
    c_float,
    c_double,
)


def path_get_name(path: str) -> str:
    return _lib.nusd_path_get_name(path.encode("ascii")).decode("utf-8")


# fix up ctypesgen's sometimes wonky typing
_lib.nusd_prim_iterator_next.argtypes = [_lib.nusd_prim_iterator_t, POINTER(c_char_p)]
_lib.nusd_attribute_get_token.argtypes = [
    _lib.nusd_stage_t,
    _lib.String,
    c_double,
    POINTER(c_char_p),
]
_lib.nusd_token_array_iterator_next.argtypes = [
    _lib.nusd_token_array_iterator_t,
    POINTER(c_char_p),
]
_lib.nusd_asset_path_array_iterator_next.argtypes = [
    _lib.nusd_asset_path_array_iterator_t,
    POINTER(c_char_p),
]
_lib.nusd_attribute_get_color_space.argtypes = [
    _lib.nusd_stage_t,
    _lib.String,
    POINTER(c_char_p),
]


class PrimIterator:
    def __init__(self, iterator: c_void_p):
        self._iterator = iterator

    def __del__(self):
        _lib.nusd_prim_iterator_destroy(self._iterator)

    def __iter__(self) -> "PrimIterator":
        return self

    def __next__(self) -> str:
        path = c_char_p(0)
        has_next: c_bool = _lib.nusd_prim_iterator_next(self._iterator, byref(path))
        if not has_next:
            raise StopIteration

        return path.value.decode("utf-8")


_lib.nusd_property_iterator_next.argtypes = [
    _lib.nusd_property_iterator_t,
    POINTER(c_char_p),
    POINTER(_lib.nusd_type_t),
]


class PropertyIterator:
    def __init__(self, iterator: c_void_p):
        self._iterator = iterator

    def __iter__(self) -> "PropertyIterator":
        return self

    def __next__(self) -> str:
        path = c_char_p(0)
        prop_type = _lib.nusd_type_t()
        has_next = _lib.nusd_property_iterator_next(
            self._iterator, byref(path), byref(prop_type)
        )
        if not has_next:
            raise StopIteration

        return path.value.decode("utf-8")


class StageOpenError(RuntimeError):
    pass


class StageCreateError(RuntimeError):
    pass


class GetPropertiesError(RuntimeError):
    pass


class CreatePropertyError(RuntimeError):
    pass


class DefinePrimError(RuntimeError):
    pass


class Stage:
    def __init__(self, stage: c_void_p):
        self._stage = stage

    def __del__(self):
        _lib.nusd_stage_destroy(self._stage)

    @classmethod
    def open(cls, filename: str) -> "Stage":
        stage = _lib.nusd_stage_t(0)
        result = _lib.nusd_stage_open(filename.encode("ascii"), byref(stage))
        if result != _lib.NUSD_RESULT_OK:
            raise StageOpenError(f'failed to open stage "{filename}": {result}')
        return cls(stage)

    @classmethod
    def create_in_memory(cls, identifier: str) -> "Stage":
        stage = _lib.nusd_stage_t(0)
        result = _lib.nusd_stage_create_in_memory(
            identifier.encode("ascii"), byref(stage)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise StageCreateError(f'failed to create stage "{identifier}": {result}')
        return cls(stage)

    def traverse(self) -> PrimIterator:
        it = _lib.nusd_prim_iterator_t(0)
        _lib.nusd_stage_traverse(self._stage, byref(it))
        return PrimIterator(it)

    def __iter__(self) -> PrimIterator:
        return self.traverse()

    def prim_get_properties(self, prim_path: str) -> PropertyIterator:
        it = _lib.nusd_property_iterator_t(0)
        result = _lib.nusd_prim_get_properties(
            self._stage, prim_path.encode("ascii"), byref(it)
        )

        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertiesError(
                f'failed to get properties for "{prim_path}": {result}'
            )

        return PropertyIterator(it)

    def get_property(self, property_path: str, time_code: float = 0.0):
        return _get_property(self, property_path, time_code)

    def set_property(
        self, property_path: str, property_type, value: Any, time_code: float = 0.0
    ):
        return _set_property(self, property_path, property_type, value, time_code)

    def define_prim(self, prim_path: str, prim_type: str):
        result = result = _lib.nusd_stage_define_prim(self._stage, prim_path, prim_type)
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define prim <{prim_path}> of type "{prim_type}": {result}'
            )

    def prim_set_transform(
        self,
        xformable_path: str,
        local_to_parent_matrix: np.ndarray,
        time_code: float = 0.0,
    ):
        """Set the transform matrix for an Xformable prim, positioning it relative to its parent.

        Args:
            xformable_path: USD path to an existing Xformable prim
            local_to_parent_matrix: 4x4 transformation matrix as NumPy array (float64) that transforms
                            from local space to its parent space (row-major order)
            time_code: The time at which to set the transform (default: 0.0)

        Raises:
            SetPropertyError: If xformable_path is invalid or local_to_parent_matrix is wrong shape/type
        """
        if (
            not isinstance(local_to_parent_matrix, np.ndarray)
            or local_to_parent_matrix.shape != (4, 4)
            or local_to_parent_matrix.dtype != np.float64
        ):
            raise SetPropertyError(
                f"local_to_parent_matrix must be a 4x4 float64 NumPy array, got {type(local_to_parent_matrix)} with shape {getattr(local_to_parent_matrix, 'shape', 'N/A')} and dtype {getattr(local_to_parent_matrix, 'dtype', 'N/A')}"
            )

        flat_matrix = local_to_parent_matrix.flatten()
        result = _lib.nusd_prim_set_transform(
            self._stage,
            xformable_path.encode("ascii"),
            flat_matrix.ctypes.data_as(POINTER(c_double)),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set local transform for "{xformable_path}": {result}'
            )

    def prim_compute_local_to_world_transform(
        self, xformable_path: str, time_code: float = 0.0
    ) -> np.ndarray:
        """Compute the complete transformation matrix from a prim's local space to world space.

        Args:
            xformable_path: USD path to a transformable prim (must inherit from UsdGeomXformable)
            time_code: The time at which to evaluate the transformation (default: 0.0)

        Returns:
            4x4 transformation matrix as NumPy array (float64) in row-major order that transforms
            points from the prim's local coordinate space to world space

        Raises:
            GetPropertyError: If xformable_path is invalid or prim is not transformable
        """
        transform = (c_double * 16)()
        result = _lib.nusd_prim_compute_local_to_world_transform(
            self._stage, xformable_path.encode("ascii"), c_double(time_code), transform
        )
        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to compute local-to-world transform for "{xformable_path}": {result}'
            )

        return np.array(transform).reshape(4, 4)

    def prim_create_property(
        self,
        prim: str,
        property_name: str,
        property_type: str,
        value=None,
        time_code: float = 0.0,
    ):
        result = _lib.nusd_prim_create_property(
            self._stage, prim, property_name, property_type
        )
        if result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create property "{property_name} on prim <{prim}>: {result}'
            )

        if value is not None:
            self.set_property(
                f"{prim}.{property_name}", property_type, value, time_code
            )

    def prim_create_primvar(
        self,
        prim_path: str,
        primvar_name: str,
        primvar_type: str,
        primvar_interpolation: str,
        value=None,
        time_code: float = 0.0,
    ):
        """Create a new primvar (primitive variable) on a prim for geometry attribute data.
        
        Args:
            prim_path: USD path to an existing prim (e.g., "/World/Mesh")
            primvar_name: Name of the primvar to create (e.g., "displayColor", "st", "normals")
            primvar_type: USD type for the primvar data (e.g., FLOAT3, FLOAT2, COLOR3F)
            primvar_interpolation: Interpolation mode for the primvar (use INTERPOLATION_* constants)
            value: Optional value to set on the created primvar
            time_code: The time at which to set the value (default: 0.0)
            
        Raises:
            CreatePropertyError: If the primvar cannot be created
            SetPropertyError: If value is provided but cannot be set
            
        Note:
            Primvars store per-vertex, per-face, or per-primitive data such as colors, texture coordinates, and normals.
            The interpolation mode determines how the data is distributed across the geometry:
            - INTERPOLATION_CONSTANT: One value for the entire primitive
            - INTERPOLATION_UNIFORM: One value per face/primitive  
            - INTERPOLATION_VARYING: One value per vertex (same as vertex for most cases)
            - INTERPOLATION_VERTEX: One value per vertex
            - INTERPOLATION_FACEVARYING: One value per face-vertex (allows discontinuities)
            
            The created primvar can be accessed via the "primvars:" namespace 
            (e.g., "/World/Mesh.primvars:displayColor").
        """
        result = _lib.nusd_prim_create_primvar(
            self._stage, prim_path, primvar_name, primvar_type, primvar_interpolation
        )
        if result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create primvar "{primvar_name}" on prim <{prim_path}>: {result}'
            )

        if value is not None:
            primvar_path = f"{prim_path}.primvars:{primvar_name}"
            self.set_property(primvar_path, primvar_type, value, time_code)

    def camera_define(self, camera_path: str):
        """Define a new USD camera prim at the specified path.

        Args:
            camera_path: USD path where the camera should be created (e.g., "/World/Camera")

        Raises:
            DefinePrimError: If the camera cannot be defined at the specified path
        """
        result = _lib.nusd_camera_define(self._stage, camera_path.encode("ascii"))
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define camera at "{camera_path}": {result}'
            )

    def camera_set_fov_w(
        self, camera_path: str, fov_w_deg: float, time_code: float = 0.0
    ):
        """Set the horizontal field of view for a camera by setting its focal length.

        Args:
            camera_path: USD path to an existing camera prim
            fov_w_deg: Horizontal field of view in degrees
            time_code: The time at which to set the field of view (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid
        """
        result = _lib.nusd_camera_set_fov_w(
            self._stage,
            camera_path.encode("ascii"),
            c_float(fov_w_deg),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera FOV for "{camera_path}": {result}'
            )

    def camera_set_exposure(
        self,
        camera_path: str,
        iso: float,
        time: float,
        f_stop: float,
        compensation: float,
        responsivity: float,
        time_code: float = 0.0,
    ):
        """Set the exposure parameters for a camera, simulating real camera controls.

        Args:
            camera_path: USD path to an existing camera prim
            iso: ISO sensitivity value (e.g., 100, 400, 800, 1600)
            time: Exposure time in seconds (e.g., 1/60 = 0.0167 for 60fps)
            f_stop: F-stop value controlling depth of field (e.g., 1.4, 2.8, 5.6, 11)
            compensation: Exposure compensation in stops (positive brightens, negative darkens)
            responsivity: Camera sensor responsivity factor
            time_code: The time at which to set the exposure parameters (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid
        """
        result = _lib.nusd_camera_set_exposure(
            self._stage,
            camera_path.encode("ascii"),
            c_float(iso),
            c_float(time),
            c_float(f_stop),
            c_float(compensation),
            c_float(responsivity),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera exposure for "{camera_path}": {result}'
            )

    def camera_set_clipping_range(
        self, camera_path: str, near: float, far: float, time_code: float = 0.0
    ):
        """Set the near and far clipping distances for a camera's viewing frustum.

        Args:
            camera_path: USD path to an existing camera prim
            near: Near clipping distance in scene units (should be small positive value like 0.1)
            far: Far clipping distance in scene units (should be greater than near)
            time_code: The time at which to set the clipping range (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid
        """
        result = _lib.nusd_camera_set_clipping_range(
            self._stage,
            camera_path.encode("ascii"),
            c_float(near),
            c_float(far),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera clipping range for "{camera_path}": {result}'
            )

    def camera_set_aperture(
        self, camera_path: str, width: float, height: float, time_code: float = 0.0
    ):
        """Set the horizontal and vertical aperture dimensions for a camera.

        Args:
            camera_path: USD path to an existing camera prim
            width: Horizontal aperture in tenths of a scene unit (e.g., millimeters if scene is in centimeters)
            height: Vertical aperture in tenths of a scene unit (e.g., millimeters if scene is in centimeters)
            time_code: The time at which to set the aperture dimensions (default: 0.0)

        Raises:
            SetPropertyError: If camera_path is invalid

        Note:
            The aperture dimensions control the camera's field of view in conjunction with the focal length.
            Common film aperture sizes: 35mm full frame (36x24), Super 35 (24.89x18.66) in tenths of scene units.
            The aspect ratio is determined by width/height and affects the final rendered image proportions.
        """
        result = _lib.nusd_camera_set_aperture(
            self._stage,
            camera_path.encode("ascii"),
            c_float(width),
            c_float(height),
            c_double(time_code),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set camera aperture for "{camera_path}": {result}'
            )

    def material_define(self, material_path: str):
        """Define a new USD material prim at the specified path.

        Args:
            material_path: USD path where the material should be created (e.g., "/World/Materials/MyMaterial")

        Raises:
            DefinePrimError: If the material cannot be defined at the specified path
        """
        result = _lib.nusd_material_define(self._stage, material_path.encode("ascii"))
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define material at "{material_path}": {result}'
            )

    def shader_define(self, shader_path: str, shader_id: str):
        """Define a new USD shader prim at the specified path with the given shader identifier.

        Args:
            shader_path: USD path where the shader should be created (e.g., "/World/Materials/MyMaterial/Shader")
            shader_id: Shader type identifier (e.g., "UsdPreviewSurface", "UsdUVTexture", "UsdPrimvarReader_float2")

        Raises:
            DefinePrimError: If the shader cannot be defined at the specified path

        Note:
            Common shader_id values include "UsdPreviewSurface" for materials, "UsdUVTexture" for textures.
        """
        result = _lib.nusd_shader_define(
            self._stage, shader_path.encode("ascii"), shader_id.encode("ascii")
        )
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define shader at "{shader_path}" with id "{shader_id}": {result}'
            )

    def shader_create_input(
        self,
        shader_path: str,
        input_name: str,
        input_type: str,
        value=None,
        time_code=0.0,
    ):
        """Create an input parameter on a shader for receiving values or connections from other shaders.

        Args:
            shader_path: USD path to an existing shader prim
            input_name: Name of the input parameter to create (e.g., "diffuseColor", "roughness", "st")
            input_type: USD type for the input parameter (e.g., COLOR3F, FLOAT, FLOAT2)
            value: Optional value to set on the input parameter
            time_code: Time code for the value (default: 0.0)

        Raises:
            CreatePropertyError: If the input cannot be created
            SetPropertyError: If input_type is RELATIONSHIP (not supported for shader inputs)

        Note:
            The created input will be automatically placed in the "inputs:" namespace (e.g., "inputs:diffuseColor").
            Shader inputs can receive constant values or connections from other shader outputs.
            If value is provided, it will be automatically set on the input parameter.
        """
        result = _lib.nusd_shader_create_input(
            self._stage,
            shader_path.encode("ascii"),
            input_name.encode("ascii"),
            input_type,
        )
        if result == _lib.NUSD_RESULT_WRONG_TYPE:
            raise SetPropertyError(
                f'RELATIONSHIP type not supported for shader input "{input_name}"'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create shader input "{input_name}" on "{shader_path}": {result}'
            )

        if value is not None:
            input_path = f"{shader_path}.inputs:{input_name}"
            self.set_property(input_path, input_type, value, time_code)

    def shader_create_output(
        self,
        shader_path: str,
        output_name: str,
        output_type: str,
        value=None,
        time_code=0.0,
    ):
        """Create an output parameter on a shader for providing values to other shaders or materials.

        Args:
            shader_path: USD path to an existing shader prim
            output_name: Name of the output parameter to create (e.g., "surface", "rgb", "r")
            output_type: USD type for the output parameter (e.g., TOKEN, COLOR3F, FLOAT)
            value: Optional value to set on the output parameter
            time_code: Time code for the value (default: 0.0)

        Raises:
            CreatePropertyError: If the output cannot be created
            SetPropertyError: If output_type is RELATIONSHIP (not supported for shader outputs)

        Note:
            The created output will be automatically placed in the "outputs:" namespace (e.g., "outputs:rgb").
            Shader outputs provide computed values that can be connected to inputs of other shaders.
            If value is provided, it will be automatically set on the output parameter.
        """
        result = _lib.nusd_shader_create_output(
            self._stage,
            shader_path.encode("ascii"),
            output_name.encode("ascii"),
            output_type,
        )
        if result == _lib.NUSD_RESULT_WRONG_TYPE:
            raise SetPropertyError(
                f'RELATIONSHIP type not supported for shader output "{output_name}"'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create shader output "{output_name}" on "{shader_path}": {result}'
            )

        if value is not None:
            output_path = f"{shader_path}.outputs:{output_name}"
            self.set_property(output_path, output_type, value, time_code)

    def shader_connect(self, source_output_path: str, destination_input_path: str):
        """Connect a shader output to a shader input, creating a data flow connection in the shader network.

        Args:
            source_output_path: Full USD path to the source shader output (e.g., "/World/Materials/Mat/Texture.outputs:rgb")
            destination_input_path: Full USD path to the destination shader input (e.g., "/World/Materials/Mat/Surface.inputs:diffuseColor")

        Raises:
            GetPropertyError: If either the source output or destination input cannot be found
            SetPropertyError: If the connection cannot be established

        Note:
            The connection creates a data flow from the source shader's output to the destination shader's input.
            Connected inputs override any authored constant values on the destination input.
            Both the source and destination must exist before calling this function.
        """
        result = _lib.nusd_shader_connect(
            self._stage,
            source_output_path.encode("ascii"),
            destination_input_path.encode("ascii"),
        )
        if result == _lib.NUSD_RESULT_INVALID_ATTRIBUTE_PATH:
            raise GetPropertyError(
                f'cannot find source output "{source_output_path}" or destination input "{destination_input_path}"'
            )
        elif result == _lib.NUSD_RESULT_CONNECTION_FAILED:
            raise SetPropertyError(
                f'failed to connect "{source_output_path}" to "{destination_input_path}"'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(f"failed to connect shaders: {result}")

    def attribute_set_color_space(self, attribute_path: str, color_space: str):
        """Set the color space metadata for an attribute.

        Args:
            attribute_path: Full USD path to the attribute (e.g., "/World/Mesh.displayColor")
            color_space: Color space string to set (e.g., "sRGB", "linear", "rec709", "acescg")

        Raises:
            SetPropertyError: If the attribute path is invalid or the color space cannot be set
            ValueError: If attribute_path or color_space is None

        Note:
            Color space metadata is used by renderers to correctly interpret color data.
            Common color spaces include "sRGB", "linear", "rec709", "acescg".
        """
        if attribute_path is None:
            raise ValueError("attribute_path cannot be None")
        if color_space is None:
            raise ValueError("color_space cannot be None")

        result = _lib.nusd_attribute_set_color_space(
            self._stage,
            attribute_path.encode("ascii"),
            color_space,
        )
        if result == _lib.NUSD_RESULT_INVALID_ATTRIBUTE_PATH:
            raise SetPropertyError(f'cannot find attribute "{attribute_path}"')
        elif result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set color space for "{attribute_path}": {result}'
            )

    def attribute_get_color_space(self, attribute_path: str) -> str:
        """Get the color space metadata for an attribute.

        Args:
            attribute_path: Full USD path to the attribute (e.g., "/World/Mesh.displayColor")

        Returns:
            Color space string, or empty string if no color space metadata is set

        Raises:
            GetPropertyError: If the attribute path is invalid or the color space cannot be retrieved
            ValueError: If attribute_path is None

        Note:
            The returned string is valid until the stage is destroyed or modified.
            Returns an empty string if no color space metadata is set.
        """
        if attribute_path is None:
            raise ValueError("attribute_path cannot be None")

        color_space = c_char_p()
        result = _lib.nusd_attribute_get_color_space(
            self._stage, attribute_path.encode("ascii"), byref(color_space)
        )
        if result == _lib.NUSD_RESULT_INVALID_ATTRIBUTE_PATH:
            raise GetPropertyError(f'cannot find attribute "{attribute_path}"')
        elif result != _lib.NUSD_RESULT_OK:
            raise GetPropertyError(
                f'failed to get color space for "{attribute_path}": {result}'
            )

        return color_space.value.decode("utf-8") if color_space.value else ""
