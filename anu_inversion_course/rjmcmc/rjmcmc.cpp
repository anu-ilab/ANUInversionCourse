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

PYBIND11_MODULE(rjmcmc, m) {
    m.doc() = "rjmcmc";
    m.def("hello", &hello, "Prints \"Hello, world!\"");
    // py::class_<Pet>(m, "Pet")
    //         .def(py::init<const std::string &>())
    //         .def("setName", &Pet::setName)
    //         .def("getName", &Pet::getName)
    //         .def("bdata", [](Pet &m) -> py::array {
    //                 py::buffer_info buff_info(py::buffer_info(
    //                         m.bdata.data(),                               /* Pointer to buffer */
    //                         sizeof(float),                          /* Size of one scalar */
    //                         py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
    //                         m.bdata.size()                                      /* Number of dimensions */
    //                 ));
    //                 return py::array(buff_info);
    //         });
    m.def("regression_single1d", &regression_single1d, "Performs single");
}
