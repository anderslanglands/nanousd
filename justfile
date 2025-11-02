configure:
    cmake -B build -G Ninja -S libnanousd

build:
    cmake --build build

test:
    ctest --test-dir build --output-on-failure

bind:
    uv run ctypesgen -Lbuild -L../build  -lnanousd -o python/nanousd/ffi.py \
        $PWD/libnanousd/*.h \
        ; cd - 

pytest TARGET="":
    cd python && uv run pytest -s {{TARGET}}; cd -

pyexample:
    cd python && uv run example01.py; cd -

docs:
    cmake --build build --target docs