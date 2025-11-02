import pytest
import nanousd as nusd
import numpy as np


def test_rect_light_define_basic():
    """Test defining a basic rectangular light"""
    stage = nusd.Stage.create_in_memory("test_rect_light_basic")
    stage.define_prim("/World", "Xform")
    
    # Define a basic white rectangular light
    stage.rect_light_define("/World/RectLight", 2.0, 1.0, 1000.0, [1.0, 1.0, 1.0])
    
    # Verify the light prim was created by trying to get properties from it
    properties = stage.prim_get_properties("/World/RectLight")


def test_rect_light_define_various_parameters():
    """Test rect_light_define with various parameter combinations"""
    stage = nusd.Stage.create_in_memory("test_rect_light_params")
    stage.define_prim("/World", "Xform")
    
    # Small dim light
    stage.rect_light_define("/World/SmallLight", 0.5, 0.25, 50.0, [1.0, 1.0, 1.0])
    
    # Large bright light
    stage.rect_light_define("/World/LargeLight", 10.0, 5.0, 2000.0, [0.9, 0.95, 1.0])
    
    # Square colored light
    stage.rect_light_define("/World/SquareLight", 3.0, 3.0, 750.0, [1.0, 0.8, 0.6])
    
    # Test with different color formats
    color_tuple = (0.7, 0.8, 0.9)
    stage.rect_light_define("/World/TupleLight", 1.0, 1.0, 100.0, color_tuple)
    
    color_array = np.array([0.6, 0.7, 0.8])
    stage.rect_light_define("/World/ArrayLight", 1.0, 1.0, 100.0, color_array)
    
    # Verify all lights were created
    properties_small = stage.prim_get_properties("/World/SmallLight")
    properties_large = stage.prim_get_properties("/World/LargeLight")
    properties_square = stage.prim_get_properties("/World/SquareLight")
    properties_tuple = stage.prim_get_properties("/World/TupleLight")
    properties_array = stage.prim_get_properties("/World/ArrayLight")


def test_rect_light_define_validation_errors():
    """Test validation errors for invalid inputs"""
    stage = nusd.Stage.create_in_memory("test_rect_light_validation")
    stage.define_prim("/World", "Xform")
    
    # Test with wrong number of color components
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.rect_light_define("/World/BadColor1", 1.0, 1.0, 100.0, [1.0, 1.0])  # Only 2 components
    
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.rect_light_define("/World/BadColor2", 1.0, 1.0, 100.0, [1.0, 1.0, 1.0, 1.0])  # 4 components
    
    # Test with non-numeric color values
    with pytest.raises(ValueError, match="color components must be numeric values"):
        stage.rect_light_define("/World/BadColor3", 1.0, 1.0, 100.0, ["red", "green", "blue"])
    
    # Test with non-list color
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.rect_light_define("/World/BadColor4", 1.0, 1.0, 100.0, "rgb")


def test_disk_light_define_basic():
    """Test defining a basic disk light"""
    stage = nusd.Stage.create_in_memory("test_disk_light_basic")
    stage.define_prim("/World", "Xform")
    
    # Define a basic white disk light
    stage.disk_light_define("/World/DiskLight", 1.5, 800.0, [1.0, 1.0, 1.0])
    
    # Verify the light prim was created by trying to get properties from it
    properties = stage.prim_get_properties("/World/DiskLight")


def test_disk_light_define_various_parameters():
    """Test disk_light_define with various parameter combinations"""
    stage = nusd.Stage.create_in_memory("test_disk_light_params")
    stage.define_prim("/World", "Xform")
    
    # Small dim light
    stage.disk_light_define("/World/SmallDisk", 0.5, 100.0, [1.0, 1.0, 1.0])
    
    # Large bright light
    stage.disk_light_define("/World/LargeDisk", 5.0, 2000.0, [0.9, 0.95, 1.0])
    
    # Colored light
    stage.disk_light_define("/World/ColoredDisk", 2.0, 750.0, [1.0, 0.8, 0.6])
    
    # Test with different color formats
    color_tuple = (0.7, 0.8, 0.9)
    stage.disk_light_define("/World/TupleDisk", 1.0, 500.0, color_tuple)
    
    color_array = np.array([0.6, 0.7, 0.8])
    stage.disk_light_define("/World/ArrayDisk", 1.0, 500.0, color_array)
    
    # Verify all lights were created
    properties_small = stage.prim_get_properties("/World/SmallDisk")
    properties_large = stage.prim_get_properties("/World/LargeDisk")
    properties_colored = stage.prim_get_properties("/World/ColoredDisk")
    properties_tuple = stage.prim_get_properties("/World/TupleDisk")
    properties_array = stage.prim_get_properties("/World/ArrayDisk")


def test_disk_light_define_validation_errors():
    """Test validation errors for invalid disk light inputs"""
    stage = nusd.Stage.create_in_memory("test_disk_light_validation")
    stage.define_prim("/World", "Xform")
    
    # Test with wrong number of color components
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.disk_light_define("/World/BadDiskColor1", 1.0, 100.0, [1.0, 1.0])  # Only 2 components
    
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.disk_light_define("/World/BadDiskColor2", 1.0, 100.0, [1.0, 1.0, 1.0, 1.0])  # 4 components
    
    # Test with non-numeric color values
    with pytest.raises(ValueError, match="color components must be numeric values"):
        stage.disk_light_define("/World/BadDiskColor3", 1.0, 100.0, ["red", "green", "blue"])
    
    # Test with non-list color
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.disk_light_define("/World/BadDiskColor4", 1.0, 100.0, "rgb")


def test_sphere_light_define_basic():
    """Test defining a basic sphere light"""
    stage = nusd.Stage.create_in_memory("test_sphere_light_basic")
    stage.define_prim("/World", "Xform")
    
    # Define a basic warm sphere light
    stage.sphere_light_define("/World/SphereLight", 2.0, 1200.0, [0.9, 0.8, 0.7])
    
    # Verify the light prim was created by trying to get properties from it
    properties = stage.prim_get_properties("/World/SphereLight")


def test_sphere_light_define_various_parameters():
    """Test sphere_light_define with various parameter combinations"""
    stage = nusd.Stage.create_in_memory("test_sphere_light_params")
    stage.define_prim("/World", "Xform")
    
    # Small dim light
    stage.sphere_light_define("/World/SmallSphere", 0.3, 50.0, [1.0, 1.0, 1.0])
    
    # Large bright light
    stage.sphere_light_define("/World/LargeSphere", 8.0, 3000.0, [0.9, 0.95, 1.0])
    
    # Colored light
    stage.sphere_light_define("/World/ColoredSphere", 3.0, 1000.0, [1.0, 0.6, 0.4])
    
    # Test with different color formats
    color_tuple = (0.8, 0.9, 1.0)
    stage.sphere_light_define("/World/TupleSphere", 1.5, 600.0, color_tuple)
    
    color_array = np.array([0.7, 0.8, 0.9])
    stage.sphere_light_define("/World/ArraySphere", 1.5, 600.0, color_array)
    
    # Verify all lights were created
    properties_small = stage.prim_get_properties("/World/SmallSphere")
    properties_large = stage.prim_get_properties("/World/LargeSphere")
    properties_colored = stage.prim_get_properties("/World/ColoredSphere")
    properties_tuple = stage.prim_get_properties("/World/TupleSphere")
    properties_array = stage.prim_get_properties("/World/ArraySphere")


def test_sphere_light_define_validation_errors():
    """Test validation errors for invalid sphere light inputs"""
    stage = nusd.Stage.create_in_memory("test_sphere_light_validation")
    stage.define_prim("/World", "Xform")
    
    # Test with wrong number of color components
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.sphere_light_define("/World/BadSphereColor1", 1.0, 100.0, [1.0, 1.0])  # Only 2 components
    
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.sphere_light_define("/World/BadSphereColor2", 1.0, 100.0, [1.0, 1.0, 1.0, 1.0])  # 4 components
    
    # Test with non-numeric color values
    with pytest.raises(ValueError, match="color components must be numeric values"):
        stage.sphere_light_define("/World/BadSphereColor3", 1.0, 100.0, ["red", "green", "blue"])
    
    # Test with non-list color
    with pytest.raises(ValueError, match="color must be a list, tuple, or array of exactly 3 numbers"):
        stage.sphere_light_define("/World/BadSphereColor4", 1.0, 100.0, "rgb")