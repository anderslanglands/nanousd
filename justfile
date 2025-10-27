configure:
    cmake -B build -G Ninja -DCMAKE_PREFIX_PATH=/home/anders/packages/usd/25.08/_v/a

build:
    cmake --build build

test:
    ctest --test-dir build --output-on-failure

bind:
    cd python && uv run ctypesgen -L../build $PWD/../nanousd.h -lnanousd -o nanousd/ffi.py; cd - 

pytest:
    cd python && uv run pytest -s; cd -

pyexample:
    cd python && uv run example01.py; cd -