set(BINARY vcu_model)
add_subdirectory(pybind11)
pybind11_add_module(vcu main.cpp)
