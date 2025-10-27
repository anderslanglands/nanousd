import nanousd as nusd
import numpy as np

stage = nusd.Stage.open("../test01.usda")
# for prim in stage:
#     print(prim)
#     for prop in stage.prim_get_properties(prim):
#         name = nusd.path_get_name(prop)
#         print(f"    {name}")

#         if name in ["testFloat", "testFloatArray"]:
#             value = stage.get_property(prop)
#             print(f"   {value}")

arr = stage.get_property("/World.testFloatArray")
print(arr * 2.0)

flt2 = stage.get_property("/World.testFloat2")
print(flt2)

flt2_arr = stage.get_property("/World.testFloat2Array")
print(flt2_arr * 2)

flt3 = stage.get_property("/World.testFloat3")
print(flt3)

flt3_arr = stage.get_property("/World.testFloat3Array")
print(flt3_arr * 3)

flt4 = stage.get_property("/World.testFloat4")
print(flt4)

flt4_arr = stage.get_property("/World.testFloat4Array")
print(flt4_arr * 4)

dbl2 = stage.get_property("/World.testDouble2")
print(dbl2)

dbl2_arr = stage.get_property("/World.testDouble2Array")
print(dbl2_arr * 2)

dbl3 = stage.get_property("/World.testDouble3")
print(dbl3)

dbl3_arr = stage.get_property("/World.testDouble3Array")
print(dbl3_arr * 3)

dbl4 = stage.get_property("/World.testDouble4")
print(dbl4)

dbl4_arr = stage.get_property("/World.testDouble4Array")
print(dbl4_arr * 4)
