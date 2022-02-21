#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <Python.h>

#include <iostream>


extern "C" {
    #include "python/swig/rjmcmc_helper.h"
}

// ------------ BEGIN dataset1d_t ---------------------------------
dataset1d_t *py_dataset1d_create_from_array(std::vector<double> x, std::vector<double> y, std::vector<double> n) {
    return dataset1d_create_from_array(&x[0], &y[0], &n[0], x.size());
}

// ------------ BEGIN resultset1d_t ---------------------------------
std::vector<int> py_resultset1d_get_propose(resultset1d_t *r) {
    int na;
    const int *a = resultset1d_get_propose(r, &na);
    std::vector<int> res(a, a+na);
    return res;
}
std::vector<int> py_resultset1d_get_accept(resultset1d_t *r) {
    int na;
    const int *a = resultset1d_get_accept(r, &na);
    std::vector<int> res(a, a+na);
    return res;
}
std::vector<int> py_resultset1d_get_partitions(resultset1d_t *r) {
    const int *partitions = resultset1d_get_partitions(r);
    std::vector<int> res(partitions, partitions+resultset1d_get_total(r));
    return res;
}
std::vector<int> py_resultset1d_get_order(resultset1d_t *r) {
    const int *order_hist = resultset1d_get_order(r);
    std::vector<int> res(order_hist, order_hist+resultset1d_get_max_order(r)+1);
    return res;
}
std::vector<int> py_resultset1d_get_partition_hist(resultset1d_t *r) {
    const int *partitions = resultset1d_get_partitions(r);
    int mp = resultset1d_get_max_partitions(r);
    int n = resultset1d_get_total(r);
    std::vector<int> res(mp+1, 0);
    for (int i = 0; i < n; i++) res[partitions[i]]++;
    return res;
}
std::vector<int> py_resultset1d_get_partition_x_histogram(resultset1d_t *r) {
    const int *part_hist = resultset1d_get_partition_x_histogram(r);
    int n = resultset1d_get_xsamples(r);
    std::vector<int> res(part_hist, part_hist+n);
    return res;
}
std::vector<double> py_resultset1d_get_mean(resultset1d_t *r) {
    const double *mean = r->mean;
    std::vector<double> res(mean, mean+r->xsamples);
    return res;
}
std::vector<double> py_resultset1d_get_median(resultset1d_t *r) {
    const double *median = resultset1d_get_median(r);
    std::vector<double> res(median, median+r->xsamples);
    return res;
}
std::vector<double> py_resultset1d_get_mode(resultset1d_t *r) {
    const double *mode = resultset1d_get_mode(r);
    std::vector<double> res(mode, mode+r->xsamples);
    return res;
}
std::vector<double> py_resultset1d_get_credible_min(resultset1d_t *r) {
    const double *credible_min = resultset1d_get_credible_min(r);
    std::vector<double> res(credible_min, credible_min+r->xsamples);
    return res;
}
std::vector<double> py_resultset1d_get_credible_max(resultset1d_t *r) {
    const double *credible_max = resultset1d_get_credible_max(r);
    std::vector<double> res(credible_max, credible_max+r->xsamples);
    return res;
}
std::vector<double> py_resultset1d_get_misfit(resultset1d_t *r) {
    const double *misfit = resultset1d_get_misfit(r);
    std::vector<double> res(misfit, misfit+r->total);
    return res;
}
std::vector<double> py_resultset1d_get_lambda(resultset1d_t *r) {
    const double *lambda = resultset1d_get_lambda(r);
    std::vector<double> res(lambda, lambda+r->total);
    return res;
}
std::vector<std::vector<int>> py_resultset1d_get_histogram(resultset1d_t *r) {
    const int **hist = resultset1d_get_histogram(r);
    std::vector<std::vector<int>> res;
    for (int i = 0; i < r->xsamples; i++) {
        std::vector<int> row;
        for (int j = 0; j < r->ysamples; j++) {
            row.push_back(hist[i][j]);
        }
        res.push_back(row);
    }
    return res;
}

// ------------ BEGIN single partition ---------------------------------
resultset1d *py_regression_single1d(dataset1d_t *dataset,int burnin,int total,int max_order,int xsamples,int ysamples,double credible_interval) {
    dataset1d d;
    d.d = dataset;
    return regression_single1d(&d, burnin, total, max_order, xsamples, ysamples, credible_interval);
}

// ------------ BEGIN part partition ---------------------------------
resultset1d *py_regression_part1d_zero(dataset1d_t *dataset,double pd,int burnin,int total,int max_partitions,int xsamples,int ysamples,double credible_interval) {
    dataset1d d;
    d.d = dataset;
    return regression_part1d_zero(&d, pd, burnin, total, max_partitions, xsamples, ysamples, credible_interval);
}
resultset1d *py_regression_part1d_natural(dataset1d_t *dataset,double pv,double pd,int burnin,int total,int max_partitions,int xsamples,int ysamples,double credible_interval) {
    dataset1d d;
    d.d = dataset;
    return regression_part1d_natural(&d, pv, pd, burnin, total, max_partitions, xsamples, ysamples, credible_interval);
}
resultset1d *py_regression_part1d(dataset1d_t *dataset,double pd,int burnin,int total,int max_partitions,int max_order,int xsamples,int ysamples,double credible_interval) {
    dataset1d d;
    d.d = dataset;
    return regression_part1d(&d, pd, burnin, total, max_partitions, max_order, xsamples, ysamples, credible_interval);
}


// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(_rjmcmc, m) {
    m.doc() = "Reversible Jump McMC";
    m.def("rjmcmc_seed", &rjmcmc_seed, "Set random seed given an integer");
    
    // ------------ BEGIN dataset1d_t ---------------------------------
    py::class_<dataset1d_t>(m, "dataset1d_t")
        .def(py::init<>())
        .def_readwrite("xmin", &dataset1d_t::xmin)
        .def_readwrite("xmax", &dataset1d_t::xmax)
        .def_readwrite("ymin", &dataset1d_t::ymin)
        .def_readwrite("ymax", &dataset1d_t::ymax)
        .def_readwrite("npoints", &dataset1d_t::npoints)
        .def_readwrite("lambdamin", &dataset1d_t::lambdamin)
        .def_readwrite("lambdamax", &dataset1d_t::lambdamax)
        .def_readwrite("lambdastd", &dataset1d_t::lambdastd)
        ;
    m.def("dataset1d_load_known", &dataset1d_load_known, "Loads a 1D dataset from given file name");
    m.def("dataset1d_load_fixed", &dataset1d_load_fixed, "Loads a 1D dataset from given file name, and applies a fixed noise level to each data point");
    m.def("dataset1d_create_from_array", &py_dataset1d_create_from_array, "Create a new empty dataset given x, y and n");

    // ------------ BEGIN point1d_t ---------------------------------
    py::class_<point1d_t>(m, "point1d_t")
        .def_readwrite("x", &point1d_t::x)
        .def_readwrite("y", &point1d_t::y)
        .def_readwrite("n", &point1d_t::n);

    // ------------ BEGIN resultset1d ---------------------------------
    py::class_<resultset1d>(m, "c_resultset1d")
        .def_readwrite("r", &resultset1d::r);
   
    // ------------ BEGIN resultset1d_t ---------------------------------
    py::class_<resultset1d_t>(m, "resultset1d_t")
        .def(py::init<>())
        .def_readwrite("xsamples", &resultset1d_t::xsamples)
        .def_readwrite("ysamples", &resultset1d_t::ysamples)
        .def_readwrite("xmin", &resultset1d_t::xmin)
        .def_readwrite("xmax", &resultset1d_t::xmax)
        .def_readwrite("ymin", &resultset1d_t::ymin)
        .def_readwrite("ymax", &resultset1d_t::ymax)
        ;
    m.def("py_resultset1d_get_propose", &py_resultset1d_get_propose);
    m.def("py_resultset1d_get_accept", &py_resultset1d_get_accept);
    m.def("py_resultset1d_get_partitions", &py_resultset1d_get_partitions);
    m.def("py_resultset1d_get_order", &py_resultset1d_get_order);
    m.def("py_resultset1d_get_partition_hist", &py_resultset1d_get_partition_hist);
    m.def("py_resultset1d_get_partition_x_histogram", &py_resultset1d_get_partition_x_histogram);
    m.def("py_resultset1d_get_mean", &py_resultset1d_get_mean);
    m.def("py_resultset1d_get_median", &py_resultset1d_get_median);
    m.def("py_resultset1d_get_mode", &py_resultset1d_get_mode);
    m.def("py_resultset1d_get_credible_min", &py_resultset1d_get_credible_min);
    m.def("py_resultset1d_get_credible_max", &py_resultset1d_get_credible_max);
    m.def("py_resultset1d_get_misfit", &py_resultset1d_get_misfit);
    m.def("py_resultset1d_get_lambda", &py_resultset1d_get_lambda);
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
    m.def("py_regression_single1d", &py_regression_single1d);
    m.def("py_regression_single1d_sampled", [](dataset1d_t *dataset,const py::object &callback,int burnin,int total,int max_order,int xsamples,int ysamples,double credible_interval) { 
        dataset1d d;
        d.d = dataset;
        PyObject *callback_obj = callback.ptr();
        return regression_single1d_sampled(&d, callback_obj, burnin, total, max_order, xsamples, ysamples, credible_interval);
    });

    // ------------ BEGIN part partition ---------------------------------
    m.def("py_regression_part1d_zero", &py_regression_part1d_zero);
    m.def("py_regression_part1d_natural", &py_regression_part1d_natural);
    m.def("py_regression_part1d", &py_regression_part1d);
    m.def("py_regression_part1d_sampled", [](dataset1d_t *dataset,const py::object &callback,double pd,int burnin,int total,int max_partitions,int max_order,int xsamples,int ysamples,double credible_interval){
        dataset1d d;
        d.d = dataset;
        PyObject *callback_obj = callback.ptr();
        return regression_part1d_sampled(&d, callback_obj, pd, burnin, total, max_partitions, max_order, xsamples, ysamples, credible_interval);
    });
}
