configure:
    cmake -B build -G Ninja -DCMAKE_PREFIX_PATH=/home/anders/packages/usd/25.08/_v/a

build:
    cmake --build build

test:
    ctest --test-dir build --output-on-failure

bind:
    cd python && uv run ctypesgen -L../build  -lnanousd -o nanousd/ffi.py \
        $PWD/../nanousd.h \
        $PWD/../nanousd-types.h \
        $PWD/../nanousd-arrays.h \
        $PWD/../nanousd-iterators.h \
        $PWD/../nanousd-properties.h \
        $PWD/../nanousd-cameras.h \
        ; cd - 

pytest:
    cd python && uv run pytest -s; cd -

pyexample:
    cd python && uv run example01.py; cd -

docs:
    cmake --build build --target docs