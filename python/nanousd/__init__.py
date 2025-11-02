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
    c_int,
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


class ShaderConnectError(RuntimeError):
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

    @classmethod
    def create_new(cls, identifier: str) -> "Stage":
        stage = _lib.nusd_stage_t(0)
        result = _lib.nusd_stage_create_new(
            identifier.encode("ascii"), byref(stage)
        )
        if result != _lib.NUSD_RESULT_OK:
            raise StageCreateError(f'failed to create stage "{identifier}": {result}')
        return cls(stage)

    def save(self):
        _lib.nusd_stage_save(self._stage)

    def traverse(self) -> PrimIterator:
        it = _lib.nusd_prim_iterator_t()
        _lib.nusd_stage_traverse(self._stage, byref(it))
        return PrimIterator(it)

    def __iter__(self) -> PrimIterator:
        return self.traverse()

    def prim_get_properties(self, prim_path: str) -> PropertyIterator:
        it = _lib.nusd_property_iterator_t()
        result = _lib.nusd_prim_get_properties(
            self._stage, prim_path.encode("ascii"), byref(it)
        )

        if result != _lib.NUSD_RESULT_OK:
            raise GetPropertiesError(
                f'failed to get properties for "{prim_path}": {result}'
            )

        return PropertyIterator(it)

    def get_property(self, property_path: str, time_code: float = TIMECODE_DEFAULT):
        return _get_property(self, property_path, time_code)

    def set_property(
        self, property_path: str, property_type, value: Any, time_code: float = TIMECODE_DEFAULT
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
        time_code: float = TIMECODE_DEFAULT,
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
        self, xformable_path: str, time_code: float = TIMECODE_DEFAULT
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
        time_code: float = TIMECODE_DEFAULT,
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
        time_code: float = TIMECODE_DEFAULT,
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
        self, camera_path: str, fov_w_deg: float, time_code: float = TIMECODE_DEFAULT,
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
        time_code: float = TIMECODE_DEFAULT,
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
        self, camera_path: str, near: float, far: float, time_code: float = TIMECODE_DEFAULT,
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
        self, camera_path: str, width: float, height: float, time_code: float = TIMECODE_DEFAULT,
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
        time_code=TIMECODE_DEFAULT,
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
        time_code=TIMECODE_DEFAULT,
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
            GetPropertyError: If either the source output or destination input attribute cannot be found
            ShaderConnectError: If the source is not a valid shader output, destination is not a valid shader input, or connection fails
            SetPropertyError: If other connection-related errors occur

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
        elif result == _lib.NUSD_RESULT_INVALID_SHADER_OUTPUT:
            raise ShaderConnectError(
                f'source attribute "{source_output_path}" is not a valid shader output'
            )
        elif result == _lib.NUSD_RESULT_INVALID_SHADER_INPUT:
            raise ShaderConnectError(
                f'destination attribute "{destination_input_path}" is not a valid shader input'
            )
        elif result == _lib.NUSD_RESULT_CONNECTION_FAILED:
            raise ShaderConnectError(
                f'failed to connect "{source_output_path}" to "{destination_input_path}"'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(f"failed to connect shaders: {result}")

    def material_create_input(
        self,
        material_path: str,
        input_name: str,
        input_type: str,
        value=None,
        time_code=TIMECODE_DEFAULT,
    ):
        """Create an input parameter on a material for receiving connections from shaders.

        Args:
            material_path: USD path to an existing material prim
            input_name: Name of the input parameter to create (e.g., "surface", "displacement", "volume")
            input_type: USD type for the input parameter (e.g., TOKEN, COLOR3F)
            value: Optional value to set on the input parameter
            time_code: Time code for the value (default: 0.0)

        Raises:
            CreatePropertyError: If the input cannot be created
            SetPropertyError: If input_type is RELATIONSHIP (not supported for material inputs)

        Note:
            The created input will be automatically placed in the "inputs:" namespace (e.g., "inputs:surface").
            Material inputs typically receive connections from shader outputs.
            If value is provided, it will be automatically set on the input parameter.
        """
        result = _lib.nusd_material_create_input(
            self._stage,
            material_path.encode("ascii"),
            input_name.encode("ascii"),
            input_type,
        )
        if result == _lib.NUSD_RESULT_WRONG_TYPE:
            raise SetPropertyError(
                f'RELATIONSHIP type not supported for material input "{input_name}"'
            )
        elif result == _lib.NUSD_RESULT_CREATE_INPUT_FAILED:
            raise CreatePropertyError(
                f'failed to create material input "{input_name}" on "{material_path}": {result}'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create material input "{input_name}" on "{material_path}": {result}'
            )

        if value is not None:
            input_path = f"{material_path}.inputs:{input_name}"
            self.set_property(input_path, input_type, value, time_code)

    def material_create_output(
        self,
        material_path: str,
        output_name: str,
        output_type: str,
        value=None,
        time_code=TIMECODE_DEFAULT,
    ):
        """Create an output parameter on a material for providing values to other materials or renderers.

        Args:
            material_path: USD path to an existing material prim
            output_name: Name of the output parameter to create (e.g., "surface", "displacement", "volume")
            output_type: USD type for the output parameter (e.g., TOKEN, COLOR3F)
            value: Optional value to set on the output parameter
            time_code: Time code for the value (default: 0.0)

        Raises:
            CreatePropertyError: If the output cannot be created
            SetPropertyError: If output_type is RELATIONSHIP (not supported for material outputs)

        Note:
            The created output will be automatically placed in the "outputs:" namespace (e.g., "outputs:surface").
            Material outputs define the final result of the material's shader network.
            If value is provided, it will be automatically set on the output parameter.
        """
        result = _lib.nusd_material_create_output(
            self._stage,
            material_path.encode("ascii"),
            output_name.encode("ascii"),
            output_type,
        )
        if result == _lib.NUSD_RESULT_WRONG_TYPE:
            raise SetPropertyError(
                f'RELATIONSHIP type not supported for material output "{output_name}"'
            )
        elif result == _lib.NUSD_RESULT_CREATE_OUTPUT_FAILED:
            raise CreatePropertyError(
                f'failed to create material output "{output_name}" on "{material_path}": {result}'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise CreatePropertyError(
                f'failed to create material output "{output_name}" on "{material_path}": {result}'
            )

        if value is not None:
            output_path = f"{material_path}.outputs:{output_name}"
            self.set_property(output_path, output_type, value, time_code)

    def shader_connect_outputs(self, source_output_path: str, destination_output_path: str):
        """Connect a shader output to another shader output, typically used to connect a shader output to a material output.

        Args:
            source_output_path: Full USD path to the source shader output (e.g., "/World/Materials/Mat/Surface.outputs:surface")
            destination_output_path: Full USD path to the destination shader output (e.g., "/World/Materials/Mat.outputs:surface")

        Raises:
            GetPropertyError: If either the source output or destination output attribute cannot be found
            ShaderConnectError: If either the source or destination attribute is not a valid shader output, or connection fails
            SetPropertyError: If other connection-related errors occur

        Note:
            The connection creates a data flow from the source shader's output to the destination shader's output.
            This is commonly used to connect shader outputs to material outputs.
            Both the source and destination must exist before calling this function.
        """
        result = _lib.nusd_shader_connect_outputs(
            self._stage,
            source_output_path.encode("ascii"),
            destination_output_path.encode("ascii"),
        )
        if result == _lib.NUSD_RESULT_INVALID_ATTRIBUTE_PATH:
            raise GetPropertyError(
                f'cannot find source output "{source_output_path}" or destination output "{destination_output_path}"'
            )
        elif result == _lib.NUSD_RESULT_INVALID_SHADER_OUTPUT:
            raise ShaderConnectError(
                f'source attribute "{source_output_path}" or destination attribute "{destination_output_path}" is not a valid shader output'
            )
        elif result == _lib.NUSD_RESULT_CONNECTION_FAILED:
            raise ShaderConnectError(
                f'failed to connect "{source_output_path}" to "{destination_output_path}"'
            )
        elif result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(f"failed to connect shader outputs: {result}")

    def rect_light_define(self, light_path: str, width: float, height: float, intensity: float, color: list):
        """Define a new USD rectangular light prim at the specified path with light parameters.

        Args:
            light_path: USD path where the rectangular light should be created (e.g., "/World/Lights/MyRectLight")
            width: Width of the rectangular light in scene units
            height: Height of the rectangular light in scene units  
            intensity: Intensity of the light (brightness multiplier)
            color: List or array of 3 float values representing the light color as RGB components (range 0.0 to 1.0)

        Raises:
            DefinePrimError: If the light cannot be defined at the specified path
            ValueError: If color is not a list/array of exactly 3 numbers

        Note:
            Creates a UsdLuxRectLight prim with the specified dimensions, intensity, and color.
            width and height define the physical size of the light emitter in scene units.
            intensity controls the brightness of the light (1.0 is normal intensity).
            color components should typically be in the range [0.0, 1.0] for normalized RGB.
            The light emits from a rectangular area, providing soft shadows and realistic area lighting.
        """
        # Validate color parameter
        if not isinstance(color, (list, tuple, np.ndarray)) or len(color) != 3:
            raise ValueError("color must be a list, tuple, or array of exactly 3 numbers")
        
        # Convert to float array
        try:
            color_array = (c_float * 3)(float(color[0]), float(color[1]), float(color[2]))
        except (ValueError, TypeError):
            raise ValueError("color components must be numeric values")

        result = _lib.nusd_rect_light_define(
            self._stage,
            light_path.encode("ascii"),
            c_float(width),
            c_float(height), 
            c_float(intensity),
            color_array
        )
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define rectangular light at "{light_path}": {result}'
            )

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

    def mesh_define(
        self,
        mesh_path: str,
        face_vertex_counts: np.ndarray,
        face_vertex_indices: np.ndarray,
        vertices: np.ndarray,
    ):
        """Define a new USD mesh prim at the specified path with geometry data.

        Args:
            mesh_path: USD path where the mesh should be created (e.g., "/World/Geometry/MyMesh")
            face_vertex_counts: Array of integers specifying the number of vertices for each face
            face_vertex_indices: Array of integers specifying vertex indices for each face (flattened)
            vertices: Array of vertex positions as float triplets (x, y, z)

        Raises:
            DefinePrimError: If the mesh cannot be defined at the specified path
            ValueError: If array inputs have incorrect types or shapes

        Note:
            - face_vertex_counts must be 1D array of integers
            - face_vertex_indices must be 1D array of integers
            - vertices must be 1D array of floats with length divisible by 3 (x,y,z triplets)
            - Creates a UsdGeomMesh prim with the specified topology and vertex positions
            - Vertex positions are expected as consecutive float triplets representing 3D coordinates
        """
        # Validate face_vertex_counts
        if not isinstance(face_vertex_counts, np.ndarray) or face_vertex_counts.ndim != 1:
            raise ValueError("face_vertex_counts must be a 1D NumPy array")
        if face_vertex_counts.dtype not in [np.int32, np.int64]:
            face_vertex_counts = face_vertex_counts.astype(np.int32)

        # Validate face_vertex_indices
        if not isinstance(face_vertex_indices, np.ndarray) or face_vertex_indices.ndim != 1:
            raise ValueError("face_vertex_indices must be a 1D NumPy array")
        if face_vertex_indices.dtype not in [np.int32, np.int64]:
            face_vertex_indices = face_vertex_indices.astype(np.int32)

        # Validate vertices
        if (
            not isinstance(vertices, np.ndarray)
            or vertices.dtype not in [np.float32, np.float64]
            or vertices.ndim != 2
            or vertices.shape[1] != 3
        ):
            raise ValueError("vertices must be a (N, 3) float ndarray")

        vertices = vertices.astype(np.float32)

        result = _lib.nusd_mesh_define(
            self._stage,
            mesh_path.encode("ascii"),
            face_vertex_counts.ctypes.data_as(POINTER(c_int)),
            len(face_vertex_counts),
            face_vertex_indices.ctypes.data_as(POINTER(c_int)),
            len(face_vertex_indices),
            vertices.ctypes.data_as(POINTER(c_float)),
            len(vertices),
        )
        if result != _lib.NUSD_RESULT_OK:
            raise DefinePrimError(
                f'failed to define mesh at "{mesh_path}": {result}'
            )

    def mesh_set_normals(
        self,
        mesh_path: str,
        normals: np.ndarray,
        interpolation,
    ):
        """Set vertex normals for an existing mesh with specified interpolation mode.

        Args:
            mesh_path: USD path to an existing mesh prim
            normals: Array of normal vectors as float triplets (x, y, z)
            interpolation: Interpolation mode for the normals (default: "vertex")

        Raises:
            SetPropertyError: If mesh_path is invalid or normals cannot be set
            ValueError: If normals array has incorrect type or shape

        Note:
            - normals must be 1D array of floats with length divisible by 3 (x,y,z triplets)
            - Normal vectors should be unit length for proper shading results
            - Common interpolation modes:
              * "vertex": One normal per vertex
              * "faceVarying": One normal per face-vertex (allows discontinuities)
              * "uniform": One normal per face
              * "constant": One normal for entire mesh
            - The mesh prim must already exist before calling this function
        """
        # Validate normals
        if (
            not isinstance(normals, np.ndarray)
            or normals.dtype not in [np.float32, np.float64]
            or normals.ndim != 2
            or normals.shape[1] != 3
        ):
            raise ValueError(f"normals must be an (N, 3) float ndarray")

        normals = normals.astype(np.float32)

        result = _lib.nusd_mesh_set_normals(
            self._stage,
            mesh_path.encode("ascii"),
            normals.ctypes.data_as(POINTER(c_float)),
            len(normals),
            interpolation,
        )
        if result == _lib.NUSD_RESULT_INVALID_PRIM_PATH:
            raise SetPropertyError(f'mesh not found at "{mesh_path}"')
        elif result != _lib.NUSD_RESULT_OK:
            raise SetPropertyError(
                f'failed to set normals for mesh "{mesh_path}": {result}'
            )
