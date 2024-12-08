//
// Created by Dhairya Gupta on 11/18/24.
//

#include <pybind11/pybind11.h>
#include <stdio.h>

namespace py = pybind11;

void eval() { printf("evaluating in the main loop rn lol\n"); }

int benchmark_lol() {
    for (int i = 0; i < 1000000000; i++) {
        i = i;
    }

    return 1;
}

PYBIND11_MODULE(vcu, module_handle) {
    module_handle.doc() =
        "Evaluation method, defined in the vcu-model library. Check source for "
        "parameters.";
    module_handle.def("eval", &eval);

    module_handle.def("benchmark_lol", &benchmark_lol);
}