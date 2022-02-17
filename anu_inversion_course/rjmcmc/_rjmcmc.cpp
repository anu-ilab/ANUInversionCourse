#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <Python.h>

#include <iostream>


void hello() {
    std::cout << "Hello, world!" << std::endl;
}

extern "C" {
    #include "python/swig/rjmcmc_helper.h"
}

PyObject *py_resultset1d_get_histogram(resultset1d_t *r) {
    const int **hist = resultset1d_get_histogram(r);
    PyObject *res;
    res = pyrjmcmc_make_int_list_2d(hist, r->xsamples, r->ysamples);
    return res;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(_rjmcmc, m) {
    m.doc() = "Reversible Jump McMC";
    m.def("hello", &hello, "Prints \"Hello, world!\"");
    m.def("rjmcmc_seed", &rjmcmc_seed, "Set random seed given an integer");
    
    // ------------ BEGIN dataset1d_t ---------------------------------
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
    m.def("dataset1d_load_known", &dataset1d_load_known, "Loads a 1D dataset from given file name");
    m.def("dataset1d_load_fixed", &dataset1d_load_fixed, "Loads a 1D dataset from given file name, and applies a fixed noise level to each data point");
    m.def("dataset1d_create", &dataset1d_create, "Create a new empty dataset");

    // ------------ BEGIN point1d_t ---------------------------------
    py::class_<point1d_t>(m, "point1d_t")
        .def_readwrite("x", &point1d_t::x)
        .def_readwrite("y", &point1d_t::y)
        .def_readwrite("n", &point1d_t::n);
   
    // ------------ BEGIN resultset1d_t ---------------------------------
    py::class_<resultset1d_t>(m, "resultset1d_t")
        .def(py::init<>())
        .def_readwrite("results", &resultset1d_t::results)
        .def_readwrite("burnin", &resultset1d_t::burnin)
        .def_readwrite("total", &resultset1d_t::total)
        .def_readwrite("xsamples", &resultset1d_t::xsamples)
        .def_readwrite("ysamples", &resultset1d_t::ysamples)
        .def_readwrite("nprocesses", &resultset1d_t::nprocesses)
        .def_readwrite("maxpartitions", &resultset1d_t::maxpartitions)
        .def_readwrite("maxorder", &resultset1d_t::maxorder)
        .def_readwrite("xmin", &resultset1d_t::xmin)
        .def_readwrite("xmax", &resultset1d_t::xmax)
        .def_readwrite("ymin", &resultset1d_t::ymin)
        .def_readwrite("ymax", &resultset1d_t::ymax)
        .def_readwrite("gradmin", &resultset1d_t::gradmin)
        .def_readwrite("gradmax", &resultset1d_t::gradmax)
        .def_readwrite("propose", &resultset1d_t::propose)
        .def_readwrite("accept", &resultset1d_t::accept)
        .def_readwrite("misfit", &resultset1d_t::misfit)
        .def_readwrite("lambda", &resultset1d_t::lambda)
        .def_readwrite("order", &resultset1d_t::order)
        .def_readwrite("partitions", &resultset1d_t::partitions)
        .def_readwrite("partition_x_hist", &resultset1d_t::partition_x_hist)
        .def_readwrite("mean", &resultset1d_t::mean)
        // .def_readwrite("hist", &resultset1d_t::hist)
        .def_readwrite("mode", &resultset1d_t::mode)
        .def_readwrite("median", &resultset1d_t::median)
        .def_readwrite("conf_interval", &resultset1d_t::conf_interval)
        .def_readwrite("conf_min", &resultset1d_t::conf_min)
        .def_readwrite("conf_max", &resultset1d_t::conf_max)
        .def_readwrite("gradient", &resultset1d_t::gradient)
        // .def_readwrite("gradient_hist", &resultset1d_t::gradient_hist)
        .def_readwrite("gradient_conf_min", &resultset1d_t::gradient_conf_min)
        .def_readwrite("gradient_conf_max", &resultset1d_t::gradient_conf_max);
    m.def("py_resultset1d_get_histogram", &py_resultset1d_get_histogram);
    
    // // ------------ BEGIN resultset1dfm_t ---------------------------------
    py::class_<resultset1dfm_t>(m, "resultset1dfm_t")
        .def(py::init<>())
        .def_readwrite("results", &resultset1dfm_t::results)
        .def_readwrite("burnin", &resultset1dfm_t::burnin)
        .def_readwrite("total", &resultset1dfm_t::total)
        .def_readwrite("xsamples", &resultset1dfm_t::xsamples)
        .def_readwrite("ysamples", &resultset1dfm_t::ysamples)
        .def_readwrite("nglobalparameters", &resultset1dfm_t::nglobalparameters)
        .def_readwrite("global_parameters", &resultset1dfm_t::global_parameters)
        .def_readwrite("nlocalparameters", &resultset1dfm_t::nlocalparameters)
        .def_readwrite("local_parameters", &resultset1dfm_t::local_parameters)
        .def_readwrite("maxpartitions", &resultset1dfm_t::maxpartitions)
        .def_readwrite("xmin", &resultset1dfm_t::xmin)
        .def_readwrite("xmax", &resultset1dfm_t::xmax)
        .def_readwrite("nprocesses", &resultset1dfm_t::nprocesses)
        .def_readwrite("propose", &resultset1dfm_t::propose)
        .def_readwrite("accept", &resultset1dfm_t::accept)
        .def_readwrite("propose_local", &resultset1dfm_t::propose_local)
        .def_readwrite("accept_local", &resultset1dfm_t::accept_local)
        .def_readwrite("misfit", &resultset1dfm_t::misfit)
        .def_readwrite("partitions", &resultset1dfm_t::partitions)
        .def_readwrite("partition_x_hist", &resultset1dfm_t::partition_x_hist)
    //     .def_readwrite("global", &resultset1dfm_t::global)
    //     .def_readwrite("local_mean", &resultset1dfm_t::local_mean)
        .def_readwrite("nhierarchical", &resultset1dfm_t::nhierarchical)
    //     .def_readwrite("hierarchical", &resultset1dfm_t::hierarchical)
    //     .def_readwrite("histogram", &resultset1dfm_t::histogram)
    //     .def_readwrite("local_median", &resultset1dfm_t::local_median)
    //     .def_readwrite("local_mode", &resultset1dfm_t::local_mode)
        .def_readwrite("credible_interval", &resultset1dfm_t::credible_interval)
    //     .def_readwrite("local_cred_min", &resultset1dfm_t::local_cred_min)
    //     .def_readwrite("local_cred_max", &resultset1dfm_t::local_cred_max)
    ;
    m.def("resultset1dfm_get_global_parameter", &resultset1dfm_get_global_parameter);
    
    // ------------ BEGIN single partition ---------------------------------
    m.def("regression_single1d", &regression_single1d);
    m.def("regression_single1d_sampled", &regression_single1d_sampled);

    // m.def("add", &add, "A function which adds two numbers",
    //   py::arg("i") = 1, py::arg("j") = 2); 
}
