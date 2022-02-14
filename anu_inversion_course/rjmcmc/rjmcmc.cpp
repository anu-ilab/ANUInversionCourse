#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


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
}
