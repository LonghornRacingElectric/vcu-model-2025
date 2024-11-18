//
// Created by Dhairya Gupta on 11/18/24.
//

#include <pybind11/pybind11.h>
#include <stdio.h>

namespace py = pybind11;

void eval() { printf("evaluating in the main loop rn lol\n"); }

PYBIND11_MODULE(vcu, module_handle) {
    module_handle.doc() =
        "Evaluation method, defined in the vcu-model library. Check source for "
        "parameters.";
    module_handle.def("eval", &eval);
}