#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <iostream>


void hello() {
    std::cout << "Hello, world!" << std::endl;
}

extern "C" {
    #include "include/rjmcmc/dataset1d.h"
    // dataset1d_t *dataset1d_load_known(const char*);
}

// int main() {
//     dataset1d_load_known("../data.txt");
//     std::cout << "yeah" << std::endl;
// }


// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(_rjmcmc, m) {
    m.doc() = "Reversible Jump McMC";
    m.def("hello", &hello, "Prints \"Hello, world!\"");
    py::class_<dataset1d_t>(m, "dataset1d_t")
        .def(py::init<>())
        .def_readwrite("xmin", &dataset1d_t::xmin)
        .def_readwrite("xmax", &dataset1d_t::xmax)
        .def_readwrite("ymin", &dataset1d_t::ymin)
        .def_readwrite("ymax", &dataset1d_t::ymax)
        .def_readwrite("points", &dataset1d_t::points)
        .def_readwrite("npoints", &dataset1d_t::npoints)
        .def_readwrite("lambdamin", &dataset1d_t::lambdamin)
        .def_readwrite("lambdamax", &dataset1d_t::lambdamax)
        .def_readwrite("lambdastd", &dataset1d_t::lambdastd)
        .def("get_xmin", [](dataset1d_t &d) {
            return d.xmin;
        });
    m.def("dataset1d_load_known", &dataset1d_load_known, "Load a 1D dataset from given file name");

    // m.def("regression_single1d", &regression_single1d, "Performs single");
}
