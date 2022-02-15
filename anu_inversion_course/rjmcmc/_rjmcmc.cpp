#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// #include "python/swig/rjmcmc.i"
#include "python/swig/rjmcmc_helper.h"


void hello() {
    std::cout << "Hello, world!" << std::endl;
}


// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(_rjmcmc, m) {
    m.doc() = "Reversible Jump McMC";
    m.def("hello", &hello, "Prints \"Hello, world!\"");
    py::class_<_dataset1d>(m, "_dataset1d")
        .def_readwrite("xmin", &_dataset1d::xmin)
        .def_readwrite("xmax", &_dataset1d::xmax)
        .def_readwrite("ymin", &_dataset1d::ymin)
        .def_readwrite("ymax", &_dataset1d::ymax)
        .def_readwrite("points", &_dataset1d::points)
        .def_readwrite("npoints", &_dataset1d::npoints)
        .def_readwrite("lambdamin", &_dataset1d::lambdamin)
        .def_readwrite("lambdamax", &_dataset1d::lambdamax)
        .def_readwrite("lambdastd", &_dataset1d::lambdastd)
        .def("get_xmin", [](_dataset1d &d) {
            return d.xmin;
        });

    // m.def("regression_single1d", &regression_single1d, "Performs single");
}


// class Example {
// private:
//     Example(int); // private constructor
// public:
//     // Factory function - returned by value:
//     static Example create(int a) { return Example(a); }

//     // These constructors are publicly callable:
//     Example(double);
//     Example(int, int);
//     Example(std::string);
// };

// py::class_<Example>(m, "Example")
//     // Bind the factory function as a constructor:
//     .def(py::init(&Example::create))
//     // Bind a lambda function returning a pointer wrapped in a holder:
//     .def(py::init([](std::string arg) {
//         return std::unique_ptr<Example>(new Example(arg));
//     }))
//     // Return a raw pointer:
//     .def(py::init([](int a, int b) { return new Example(a, b); }))
//     // You can mix the above with regular C++ constructor bindings as well:
//     .def(py::init<double>())
//     ;