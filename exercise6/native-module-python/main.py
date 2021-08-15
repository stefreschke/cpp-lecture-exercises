
from cffi import FFI
ffibuilder = FFI()
ffibuilder.cdef("int process(int n);")
ffibuilder.set_source("_process",
                      '#include "process.h"',
                      sources=['process.c'],
                      libraries=["m"])

if __name__ == "__main__":
    ffibuilder.compile(verbose=False)
    from _process.lib import process
    for i in range(1, 101):
        print("Call with", i, "results in", process(i))
