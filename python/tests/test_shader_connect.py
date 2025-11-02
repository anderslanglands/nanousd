import pytest
import nanousd as nusd


def test_shader_connect_success():
    """Test successful shader connection"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_success")
    stage.define_prim("/World", "Xform")
    
    # Create material and shaders
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create inputs and outputs
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.FLOAT3)
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.FLOAT3)
    
    # Connect should succeed
    stage.shader_connect(
        "/World/Materials/Mat/Texture.outputs:rgb",
        "/World/Materials/Mat/Surface.inputs:diffuseColor"
    )


def test_shader_connect_invalid_attribute_path():
    """Test GetPropertyError for invalid attribute paths"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_invalid_attr")
    stage.define_prim("/World", "Xform")
    
    # Test non-existent source
    with pytest.raises(nusd.GetPropertyError, match='cannot find source output'):
        stage.shader_connect(
            "/NonExistent/Shader.outputs:rgb",
            "/World/Materials/Mat/Surface.inputs:diffuseColor"
        )
    
    # Test non-existent destination  
    with pytest.raises(nusd.GetPropertyError, match='cannot find source output'):
        stage.shader_connect(
            "/World/Materials/Mat/Texture.outputs:rgb",
            "/NonExistent/Shader.inputs:diffuseColor"
        )


def test_shader_connect_invalid_shader_output():
    """Test ShaderConnectError for invalid shader output"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_invalid_output")
    stage.define_prim("/World", "Xform")
    
    # Create material and shaders
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create a regular attribute (not a shader output)
    stage.prim_create_property("/World/Materials/Mat/Texture", "regularAttr", nusd.FLOAT3)
    
    # Create valid input
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.FLOAT3)
    
    # Try to connect from regular attribute - should raise ShaderConnectError
    with pytest.raises(nusd.ShaderConnectError, match='source attribute.*is not a valid shader output'):
        stage.shader_connect(
            "/World/Materials/Mat/Texture.regularAttr",
            "/World/Materials/Mat/Surface.inputs:diffuseColor"
        )


def test_shader_connect_invalid_shader_input():
    """Test ShaderConnectError for invalid shader input"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_invalid_input")
    stage.define_prim("/World", "Xform")
    
    # Create material and shaders
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create valid output
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.FLOAT3)
    
    # Create another shader output (not an input)
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN)
    
    # Try to connect to shader output - should raise ShaderConnectError
    with pytest.raises(nusd.ShaderConnectError, match='destination attribute.*is not a valid shader input'):
        stage.shader_connect(
            "/World/Materials/Mat/Texture.outputs:rgb",
            "/World/Materials/Mat/Surface.outputs:surface"
        )


def test_shader_connect_error_is_runtime_error():
    """Test that ShaderConnectError is a subclass of RuntimeError"""
    assert issubclass(nusd.ShaderConnectError, RuntimeError)


def test_shader_connect_multiple_error_scenarios():
    """Test multiple shader connection error scenarios in sequence"""
    stage = nusd.Stage.create_in_memory("test_shader_connect_multiple_errors")
    stage.define_prim("/World", "Xform")
    
    # Create material and shaders
    stage.material_define("/World/Materials/Mat")
    stage.shader_define("/World/Materials/Mat/Surface", "UsdPreviewSurface")
    stage.shader_define("/World/Materials/Mat/Texture", "UsdUVTexture")
    
    # Create regular attributes and shader inputs/outputs
    stage.prim_create_property("/World/Materials/Mat/Texture", "regularAttr", nusd.FLOAT3)
    stage.shader_create_input("/World/Materials/Mat/Surface", "diffuseColor", nusd.FLOAT3)
    stage.shader_create_output("/World/Materials/Mat/Texture", "rgb", nusd.FLOAT3)
    stage.shader_create_output("/World/Materials/Mat/Surface", "surface", nusd.TOKEN)
    
    # Test 1: Invalid shader output
    with pytest.raises(nusd.ShaderConnectError, match='source attribute.*is not a valid shader output'):
        stage.shader_connect(
            "/World/Materials/Mat/Texture.regularAttr",
            "/World/Materials/Mat/Surface.inputs:diffuseColor"
        )
    
    # Test 2: Invalid shader input (connecting to output)
    with pytest.raises(nusd.ShaderConnectError, match='destination attribute.*is not a valid shader input'):
        stage.shader_connect(
            "/World/Materials/Mat/Texture.outputs:rgb",
            "/World/Materials/Mat/Surface.outputs:surface"
        )
    
    # Test 3: Valid connection should still work
    stage.shader_connect(
        "/World/Materials/Mat/Texture.outputs:rgb",
        "/World/Materials/Mat/Surface.inputs:diffuseColor"
    )