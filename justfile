configure *ARGS:
    cmake -B build -G Ninja -S libnanousd {{ARGS}}

build *ARGS:
    cmake --build build {{ARGS}}

test *ARGS:
    ctest --test-dir build --output-on-failure {{ARGS}}

bind:
    uv run ctypesgen -Lbuild -L../build  -lnanousd -o python/nanousd/ffi.py \
        $PWD/libnanousd/*.h \
        ; cd - 

pytest *ARGS:
    cd python && uv run pytest -s {{ARGS}}; cd -

pyexample:
    cd python && uv run example01.py; cd -

docs:
    cmake --build build --target docs