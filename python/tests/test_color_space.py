import pytest
import nanousd as nusd


def test_attribute_set_color_space_basic():
    stage = nusd.Stage.create_in_memory("test_color_space")
    stage.define_prim("/World", "Mesh")
    stage.prim_create_property("/World", "displayColor", nusd.COLOR3F)

    # Set color space
    stage.attribute_set_color_space("/World.displayColor", "sRGB")

    # Get color space
    color_space = stage.attribute_get_color_space("/World.displayColor")
    assert color_space == "sRGB"


def test_attribute_color_space_different_values():
    stage = nusd.Stage.create_in_memory("test_color_space_values")
    stage.define_prim("/World", "Mesh")
    stage.prim_create_property("/World", "displayColor", nusd.COLOR3F)

    test_color_spaces = ["linear", "rec709", "acescg", "prophoto"]
    
    for color_space in test_color_spaces:
        stage.attribute_set_color_space("/World.displayColor", color_space)
        retrieved_color_space = stage.attribute_get_color_space("/World.displayColor")
        assert retrieved_color_space == color_space


def test_attribute_color_space_empty_string():
    stage = nusd.Stage.create_in_memory("test_color_space_empty")
    stage.define_prim("/World", "Mesh")
    stage.prim_create_property("/World", "displayColor", nusd.COLOR3F)

    # Set empty color space
    stage.attribute_set_color_space("/World.displayColor", "")

    # Get color space - should return empty string
    color_space = stage.attribute_get_color_space("/World.displayColor")
    assert color_space == ""


def test_attribute_set_color_space_invalid_attribute_path():
    stage = nusd.Stage.create_in_memory("test_color_space_invalid")
    stage.define_prim("/World", "Mesh")

    # Test invalid attribute path
    with pytest.raises(nusd.SetPropertyError):
        stage.attribute_set_color_space("/World.nonexistent", "sRGB")

    with pytest.raises(nusd.SetPropertyError):
        stage.attribute_set_color_space("/NonExistent.displayColor", "sRGB")


def test_attribute_get_color_space_invalid_attribute_path():
    stage = nusd.Stage.create_in_memory("test_color_space_invalid")
    stage.define_prim("/World", "Mesh")

    # Test invalid attribute path
    with pytest.raises(nusd.GetPropertyError):
        stage.attribute_get_color_space("/World.nonexistent")

    with pytest.raises(nusd.GetPropertyError):
        stage.attribute_get_color_space("/NonExistent.displayColor")


def test_attribute_set_color_space_none_parameters():
    stage = nusd.Stage.create_in_memory("test_color_space_none")
    stage.define_prim("/World", "Mesh")
    stage.prim_create_property("/World", "displayColor", nusd.COLOR3F)

    # Test None parameters
    with pytest.raises(ValueError):
        stage.attribute_set_color_space(None, "sRGB")

    with pytest.raises(ValueError):
        stage.attribute_set_color_space("/World.displayColor", None)


def test_attribute_get_color_space_none_parameters():
    stage = nusd.Stage.create_in_memory("test_color_space_none")
    stage.define_prim("/World", "Mesh")
    stage.prim_create_property("/World", "displayColor", nusd.COLOR3F)

    # Test None parameter
    with pytest.raises(ValueError):
        stage.attribute_get_color_space(None)


def test_attribute_color_space_round_trip():
    """Test that we can set and get various color spaces correctly."""
    stage = nusd.Stage.create_in_memory("test_color_space_round_trip")
    stage.define_prim("/World", "Mesh")
    stage.prim_create_property("/World", "displayColor", nusd.COLOR3F)

    test_cases = [
        "sRGB",
        "linear", 
        "rec709",
        "acescg",
        "prophoto",
        "xyz",
        "",  # empty string
        "custom_color_space_name"
    ]

    for expected_color_space in test_cases:
        stage.attribute_set_color_space("/World.displayColor", expected_color_space)
        actual_color_space = stage.attribute_get_color_space("/World.displayColor")
        assert actual_color_space == expected_color_space, f"Expected '{expected_color_space}', got '{actual_color_space}'"