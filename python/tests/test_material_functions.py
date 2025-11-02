import pytest
import nanousd as nusd


def test_material_create_input():
    """Test creating material inputs"""
    stage = nusd.Stage.create_in_memory("test_material_create_input")
    stage.define_prim("/World", "Xform")
    
    # Create material
    stage.material_define("/World/Materials/Mat")
    
    # Create material input
    stage.material_create_input("/World/Materials/Mat", "surface", nusd.TOKEN)
    
    # Verify input was created by getting its property (should not raise error)
    # Note: We can't easily verify the input exists without additional USD introspection
    # But if no exception is raised, the input was successfully created


def test_material_create_output():
    """Test creating material outputs"""
    stage = nusd.Stage.create_in_memory("test_material_create_output")
    stage.define_prim("/World", "Xform")
    
    # Create material
    stage.material_define("/World/Materials/Mat")
    
    # Create material output
    stage.material_create_output("/World/Materials/Mat", "surface", nusd.TOKEN)
    
    # Verify output was created by getting its property (should not raise error)
    # Note: We can't easily verify the output exists without additional USD introspection
    # But if no exception is raised, the output was successfully created


def test_material_create_input_with_value():
    """Test creating material input with initial value"""
    stage = nusd.Stage.create_in_memory("test_material_create_input_value")
    stage.define_prim("/World", "Xform")
    
    # Create material
    stage.material_define("/World/Materials/Mat")
    
    # Create material input with value
    stage.material_create_input("/World/Materials/Mat", "diffuseColor", nusd.COLOR3F, [1.0, 0.5, 0.0])
    
    # Verify the value was set
    value = stage.get_property("/World/Materials/Mat.inputs:diffuseColor")
    assert len(value) == 3
    assert value[0] == pytest.approx(1.0)
    assert value[1] == pytest.approx(0.5)
    assert value[2] == pytest.approx(0.0)


def test_material_create_output_with_value():
    """Test creating material output with initial value"""
    stage = nusd.Stage.create_in_memory("test_material_create_output_value")
    stage.define_prim("/World", "Xform")
    
    # Create material
    stage.material_define("/World/Materials/Mat")
    
    # Create material output with value
    stage.material_create_output("/World/Materials/Mat", "result", nusd.COLOR3F, [0.8, 0.9, 1.0])
    
    # Verify the value was set
    value = stage.get_property("/World/Materials/Mat.outputs:result")
    assert len(value) == 3
    assert value[0] == pytest.approx(0.8)
    assert value[1] == pytest.approx(0.9)
    assert value[2] == pytest.approx(1.0)


def test_material_create_input_invalid_material():
    """Test creating input on non-existent material fails"""
    stage = nusd.Stage.create_in_memory("test_material_input_invalid")
    
    with pytest.raises(nusd.CreatePropertyError, match='failed to create material input'):
        stage.material_create_input("/NonExistent/Material", "surface", nusd.TOKEN)


def test_material_create_output_invalid_material():
    """Test creating output on non-existent material fails"""
    stage = nusd.Stage.create_in_memory("test_material_output_invalid")
    
    with pytest.raises(nusd.CreatePropertyError, match='failed to create material output'):
        stage.material_create_output("/NonExistent/Material", "surface", nusd.TOKEN)


def test_material_create_input_relationship_type():
    """Test that RELATIONSHIP type is not supported for material inputs"""
    stage = nusd.Stage.create_in_memory("test_material_input_relationship")
    stage.define_prim("/World", "Xform")
    
    # Create material
    stage.material_define("/World/Materials/Mat")
    
    # Try to create input with RELATIONSHIP type - should fail
    with pytest.raises(nusd.SetPropertyError, match='RELATIONSHIP type not supported'):
        stage.material_create_input("/World/Materials/Mat", "connection", nusd.RELATIONSHIP)


def test_material_create_output_relationship_type():
    """Test that RELATIONSHIP type is not supported for material outputs"""
    stage = nusd.Stage.create_in_memory("test_material_output_relationship")
    stage.define_prim("/World", "Xform")
    
    # Create material
    stage.material_define("/World/Materials/Mat")
    
    # Try to create output with RELATIONSHIP type - should fail
    with pytest.raises(nusd.SetPropertyError, match='RELATIONSHIP type not supported'):
        stage.material_create_output("/World/Materials/Mat", "connection", nusd.RELATIONSHIP)


def test_shader_connect_outputs():
    """Test connecting shader output to material output"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_outputs")
    stage.define_prim("/World", "Xform")
    
    # Create material and shader
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create shader output
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN)
    
    # Create material output
    stage.material_create_output("/World/Materials/Mat", "surface", nusd.TOKEN)
    
    # Connect shader output to material output
    stage.shader_connect_outputs(
        "/World/Materials/Mat/Surface.outputs:surface",
        "/World/Materials/Mat.outputs:surface"
    )


def test_shader_connect_outputs_invalid_paths():
    """Test shader_connect_outputs with invalid paths"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_outputs_invalid")
    
    # Test with non-existent source
    with pytest.raises(nusd.GetPropertyError, match='cannot find source output'):
        stage.shader_connect_outputs(
            "/NonExistent/Shader.outputs:surface",
            "/World/Materials/Mat.outputs:surface"
        )


def test_shader_connect_outputs_invalid_shader_output():
    """Test shader_connect_outputs with invalid shader output"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_outputs_invalid_output")
    stage.define_prim("/World", "Xform")
    
    # Create material and shader
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create a regular attribute (not a shader output)
    stage.prim_create_property("/World/Materials/Mat/Surface", "regularAttr", nusd.TOKEN)
    
    # Create valid material output
    stage.material_create_output("/World/Materials/Mat", "surface", nusd.TOKEN)
    
    # Try to connect from regular attribute - should raise ShaderConnectError
    with pytest.raises(nusd.ShaderConnectError, match='is not a valid shader output'):
        stage.shader_connect_outputs(
            "/World/Materials/Mat/Surface.regularAttr",
            "/World/Materials/Mat.outputs:surface"
        )


def test_shader_connect_outputs_multiple_scenarios():
    """Test multiple shader connection scenarios in sequence"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_outputs_multiple")
    stage.define_prim("/World", "Xform")
    
    # Create material and multiple shaders
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    
    # Create shader outputs
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.COLOR3F)
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN)
    
    # Create material outputs
    stage.material_create_output("/World/Materials/Mat", "surface", nusd.TOKEN)
    stage.material_create_output("/World/Materials/Mat", "displacement", nusd.TOKEN)
    
    # Test multiple connections
    stage.shader_connect_outputs(
        "/World/Materials/Mat/Surface.outputs:surface",
        "/World/Materials/Mat.outputs:surface"
    )
    
    stage.shader_connect_outputs(
        "/World/Materials/Mat/Surface.outputs:surface",
        "/World/Materials/Mat.outputs:displacement"
    )


def test_shader_connect_outputs_error_inheritance():
    """Test that ShaderConnectError is a subclass of RuntimeError"""
    assert issubclass(nusd.ShaderConnectError, RuntimeError)


def test_material_bind_basic():
    """Test basic material binding functionality"""
    stage = nusd.Stage.create_in_memory("test_material_bind_basic")
    stage.define_prim("/World", "Xform")
    
    # Create a material and a geometry prim
    stage.material_define("/World/Materials/Mat")
    stage.define_prim("/World/Geometry", "Xform")
    stage.define_prim("/World/Geometry/Mesh", "Mesh")
    
    # Bind the material to the mesh
    stage.material_bind("/World/Geometry/Mesh", "/World/Materials/Mat")
    
    # If no exception is raised, the binding was successful


def test_material_bind_error_scenarios():
    """Test various error scenarios for material binding"""
    stage = nusd.Stage.create_in_memory("test_material_bind_errors")
    stage.define_prim("/World", "Xform")
    
    # Create a material and a geometry prim
    stage.material_define("/World/Materials/Mat")
    stage.define_prim("/World/Geometry", "Xform")
    stage.define_prim("/World/Geometry/Mesh", "Mesh")
    
    # Test binding to non-existent prim
    with pytest.raises(nusd.MaterialBindError, match='does not exist'):
        stage.material_bind("/NonExistent/Prim", "/World/Materials/Mat")
    
    # Test binding non-existent material
    with pytest.raises(nusd.MaterialBindError, match='does not exist'):
        stage.material_bind("/World/Geometry/Mesh", "/NonExistent/Material")
    
    # Test that MaterialBindError is a subclass of RuntimeError
    assert issubclass(nusd.MaterialBindError, RuntimeError)
    
    # Test successful binding after error scenarios
    stage.material_bind("/World/Geometry/Mesh", "/World/Materials/Mat")