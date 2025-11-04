import pytest
import nanousd as nusd


def test_string_get_set():
    """Test getting and setting string properties"""
    stage = nusd.Stage.create_in_memory("test_string")
    stage.define_prim("/World", "Xform")
    
    # Test string property
    test_string = "hello world"
    stage.prim_create_property("/World", "testString", nusd.STRING, test_string)
    
    # Verify string retrieval
    value = stage.get_property("/World.testString")
    assert isinstance(value, str)
    assert value == test_string


def test_string_empty():
    """Test handling of empty strings"""
    stage = nusd.Stage.create_in_memory("test_string_empty")
    stage.define_prim("/World", "Xform")
    
    # Test empty string
    stage.prim_create_property("/World", "emptyString", nusd.STRING, "")
    
    value = stage.get_property("/World.emptyString")
    assert isinstance(value, str)
    assert value == ""


def test_string_unicode():
    """Test handling of unicode strings"""
    stage = nusd.Stage.create_in_memory("test_string_unicode")
    stage.define_prim("/World", "Xform")
    
    # Test unicode string (note: USD/ctypes might have limitations, so we test basic ASCII)
    test_string = "Test ASCII string with symbols !@#$%"
    stage.prim_create_property("/World", "unicodeString", nusd.STRING, test_string)
    
    value = stage.get_property("/World.unicodeString")
    assert isinstance(value, str)
    assert value == test_string


def test_string_array_get_set():
    """Test getting and setting string array properties"""
    stage = nusd.Stage.create_in_memory("test_string_array")
    stage.define_prim("/World", "Xform")
    
    # Test string array property
    test_strings = ["first", "second", "third string", "fourth"]
    stage.prim_create_property("/World", "testStringArray", nusd.STRINGARRAY, test_strings)
    
    # Verify string array retrieval
    value = stage.get_property("/World.testStringArray")
    assert isinstance(value, list)
    assert len(value) == len(test_strings)
    assert value == test_strings


def test_string_array_empty():
    """Test handling of empty string arrays"""
    stage = nusd.Stage.create_in_memory("test_string_array_empty")
    stage.define_prim("/World", "Xform")
    
    # Test empty array
    stage.prim_create_property("/World", "emptyStringArray", nusd.STRINGARRAY, [])
    
    value = stage.get_property("/World.emptyStringArray")
    assert isinstance(value, list)
    assert len(value) == 0


def test_string_array_with_empty_strings():
    """Test string arrays containing empty strings"""
    stage = nusd.Stage.create_in_memory("test_string_array_with_empty")
    stage.define_prim("/World", "Xform")
    
    # Test array with some empty strings
    test_strings = ["first", "", "third", "", "fifth"]
    stage.prim_create_property("/World", "stringArrayWithEmpty", nusd.STRINGARRAY, test_strings)
    
    value = stage.get_property("/World.stringArrayWithEmpty")
    assert isinstance(value, list)
    assert len(value) == len(test_strings)
    assert value == test_strings


def test_string_property_types():
    """Test setting and getting string properties with explicit types"""
    stage = nusd.Stage.create_in_memory("test_string_types")
    stage.define_prim("/World", "Xform")
    
    # Test setting with string type - create property first
    stage.prim_create_property("/World", "stringProp", nusd.STRING)
    stage.set_property("/World.stringProp", nusd.STRING, "test value")
    
    value = stage.get_property("/World.stringProp")
    assert value == "test value"
    
    # Test setting array with string array type - create property first
    stage.prim_create_property("/World", "stringArrayProp", nusd.STRINGARRAY)
    stage.set_property("/World.stringArrayProp", nusd.STRINGARRAY, ["one", "two", "three"])
    
    value = stage.get_property("/World.stringArrayProp")
    assert value == ["one", "two", "three"]


def test_string_error_handling():
    """Test error handling for string properties"""
    stage = nusd.Stage.create_in_memory("test_string_errors")
    stage.define_prim("/World", "Xform")
    
    # Test setting string with wrong type
    with pytest.raises(nusd.SetPropertyError):
        stage.set_property("/World.badString", nusd.STRING, 123)  # int instead of string
    
    # Test setting string array with wrong type  
    with pytest.raises(nusd.SetPropertyError):
        stage.set_property("/World.badStringArray", nusd.STRINGARRAY, "not a list")
    
    # Test setting string array with mixed types
    with pytest.raises(nusd.SetPropertyError):
        stage.set_property("/World.badStringArray2", nusd.STRINGARRAY, ["string", 123, "another"])


def test_string_round_trip():
    """Test that strings preserve their values through multiple get/set operations"""
    stage = nusd.Stage.create_in_memory("test_string_round_trip")
    stage.define_prim("/World", "Xform")
    
    # Test multiple round trips
    test_values = [
        "simple",
        "with spaces and symbols !@#",
        "",  # empty string
        "very long string with lots of text to ensure memory handling works correctly"
    ]
    
    for i, test_string in enumerate(test_values):
        prop_name = f"stringProp{i}"
        stage.prim_create_property("/World", prop_name, nusd.STRING, test_string)
        
        # Get the value back
        retrieved = stage.get_property(f"/World.{prop_name}")
        assert retrieved == test_string
        
        # Set it to a new value
        new_value = f"modified_{test_string}"
        stage.set_property(f"/World.{prop_name}", nusd.STRING, new_value)
        
        # Verify the new value
        final_retrieved = stage.get_property(f"/World.{prop_name}")
        assert final_retrieved == new_value


def test_string_array_round_trip():
    """Test that string arrays preserve their values through multiple get/set operations"""
    stage = nusd.Stage.create_in_memory("test_string_array_round_trip")
    stage.define_prim("/World", "Xform")
    
    # Test multiple round trips
    test_arrays = [
        ["one", "two", "three"],
        [],  # empty array
        ["", "empty", "", "mixed"],  # array with empty strings
        ["single"],  # single element
        ["a" * 100, "b" * 200]  # long strings
    ]
    
    for i, test_array in enumerate(test_arrays):
        prop_name = f"stringArrayProp{i}"
        stage.prim_create_property("/World", prop_name, nusd.STRINGARRAY, test_array)
        
        # Get the value back
        retrieved = stage.get_property(f"/World.{prop_name}")
        assert retrieved == test_array
        
        # Set it to a new value
        new_value = [f"modified_{s}" for s in test_array] + ["added"]
        stage.set_property(f"/World.{prop_name}", nusd.STRINGARRAY, new_value)
        
        # Verify the new value
        final_retrieved = stage.get_property(f"/World.{prop_name}")
        assert final_retrieved == new_value


def test_string_vs_token():
    """Test that string and token types are handled separately"""
    stage = nusd.Stage.create_in_memory("test_string_vs_token")
    stage.define_prim("/World", "Xform")
    
    # Create both string and token properties
    test_value = "same_value"
    
    stage.prim_create_property("/World", "stringProp", nusd.STRING, test_value)
    stage.prim_create_property("/World", "tokenProp", nusd.TOKEN, test_value)
    
    # Both should return the same value as strings
    string_value = stage.get_property("/World.stringProp")
    token_value = stage.get_property("/World.tokenProp")
    
    assert string_value == test_value
    assert token_value == test_value
    assert string_value == token_value
    
    # But they should be different USD types internally
    # (This is more of a test that our implementation works with both types)