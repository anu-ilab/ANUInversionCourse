from anu_inversion_course._rjmcmc import (
    dataset1d_t,
    dataset1d_load_known,
    dataset1d_load_fixed,
    dataset1d_create_from_array,
    resultset1d_t,
    py_resultset1d_get_propose,
    py_resultset1d_get_accept,
    py_resultset1d_get_partitions,
    py_resultset1d_get_order,
    py_resultset1d_get_partition_hist,
    py_resultset1d_get_partition_x_histogram,
    py_resultset1d_get_mean,
    py_resultset1d_get_median,
    py_resultset1d_get_mode,
    py_resultset1d_get_credible_min,
    py_resultset1d_get_credible_max,
    py_resultset1d_get_misfit,
    py_resultset1d_get_lambda,
    py_resultset1d_get_histogram,
    resultset1dfm_t,
    resultset1dfm_get_global_parameter,
    py_regression_single1d,
    py_regression_single1d_sampled,
    py_regression_part1d_zero,
    py_regression_part1d_natural,
    py_regression_part1d,
    py_regression_part1d_sampled,
)

import collections
import numpy as np


class dataset1d:
    def __init__(self, *args):
        if len(args) == 1:
            filename = args[0]
            self.d = dataset1d_load_known(filename)
        elif len(args) == 2:
            filename = args[0]
            n = args[1]
            self.d = dataset1d_load_fixed(filename, n)
        elif len(args) == 3:
            x = args[0]
            y = args[1]
            n = args[2]
            # ####### INPUT VALIDATION #######
            if not check_list_like(x) or not check_list_like(y) or not check_list_like(n):
                raise ValueError("Parameter must be a list of floating point values")
            x = np.asanyarray(x, dtype=np.float64)
            y = np.asanyarray(y, dtype=np.float64)
            n = np.asanyarray(n, dtype=np.float64)
            if x.shape[0] != y.shape[0] or x.shape[0] != n.shape[0]:
                raise ValueError("Parameters must have the same length")
            if np.any(n<0):
                raise ValueError("All values in the n array must be greater than zero")
            # ####### END VALIDATION #######
            self.d = dataset1d_create_from_array(x, y, n)
        else:
            raise ValueError("Please provide either file name or x,y,n when initialising dataset1d")

    def set_xrange(self, xmin, xmax):
        self.d.xmin = xmin
        self.d.xmax = xmax

    def get_xmin(self):
        return self.d.xmin

    def get_xmax(self):
        return self.d.xmax

    def set_yrange(self, ymin, ymax):
        self.d.ymin = ymin
        self.d.ymax = ymax

    def get_ymin(self):
        return self.d.ymin

    def get_ymax(self):
        return self.d.ymax

    def set_lambda_std(self, std):
        self.d.lambdastd = std
    
    def get_lambda_std(self):
        return self.d.lambdastd

    def set_lambda_range(self, lambdamin, lambdamax):
        self.d.lambdamin = lambdamin
        self.d.lambdamax = lambdamax

    def get_lambda_min(self):
        return self.d.lambdamin

    def get_lambda_max(self):
        return self.d.lambdamax

class resultset1d:
    def __init__(self, resultset1d_t):
        self.r = resultset1d_t

    def proposed(self):
        return py_resultset1d_get_propose(self.r)
            
    def acceptance(self):
        return py_resultset1d_get_accept(self.r)

    def partitions(self):
        return py_resultset1d_get_partitions(self.r)

    def order_histogram(self):
        return py_resultset1d_get_order(self.r)

    def partition_histogram(self):
        return py_resultset1d_get_partition_hist(self.r)

    def partition_location_histogram(self):
        return py_resultset1d_get_partition_x_histogram(self.r)

    def x(self):
        n_xsamples = self.r.xsamples
        xmin = self.r.xmin
        xmax = self.r.xmax
        x_vector = [xmin+(xmax-xmin)*(i+0.5)/n_xsamples for i in range(n_xsamples)]
        return x_vector

    def y(self):
        n_ysamples = self.r.ysamples
        ymin = self.r.ymin
        ymax = self.r.ymax
        y_vector = [ymin+(ymax-ymin)*(i+0.5)/n_ysamples for i in range(n_ysamples)]
        return y_vector

    def mean(self):
        return py_resultset1d_get_mean(self.r)

    def median(self):
        return py_resultset1d_get_median(self.r)

    def mode(self):
        return py_resultset1d_get_mode(self.r)

    def credible_min(self):
        return py_resultset1d_get_credible_min(self.r)

    def credible_max(self):
        return py_resultset1d_get_credible_max(self.r)

    def misfit(self):
        return py_resultset1d_get_misfit(self.r)

    def lambda_history(self):
        return py_resultset1d_get_lambda(self.r)

    def histogram(self):
        return py_resultset1d_get_histogram(self.r)


class resultset1dfm:
    def __init__(self, resultset1dfm_t):
        self.r = resultset1dfm_t

    def proposed(self):
        return self.r.propose
            
    def acceptance(self):
        return self.r.accept

    def partitions(self):
        return self.r.partitions

    def partition_histogram(self):
        return self.r.partitions

    def partition_location_histogram(self):
        return self.r.partition_x_hist

    def x(self):
        return self.r.xsamples

    def y(self):
        return self.r.ysamples

    def mean(self):
        return self.r.mean

    def median(self):
        return self.r.median

    def mode(self):
        return self.r.mode

    def credible_min(self):
        return self.r.conf_min

    def credible_max(self):
        return self.r.conf_max

    def misfit(self):
        return self.r.misfit 
    
    def global_parameter(self, gi):
        return resultset1dfm_get_global_parameter(self.r, gi)


def regression_single1d(dataset, burnin=10000, total=50000, max_order=5, xsamples=100, ysamples=100, credible_interval=0.95):
    res = py_regression_single1d(dataset.d, burnin, total, max_order, xsamples, ysamples, credible_interval)
    return resultset1d(res.r)

def regression_single1d_sampled(dataset, callback, burnin=10000, total=50000, max_order=5, xsamples=100, ysamples=100, credible_interval=0.95):
    res = py_regression_single1d_sampled(dataset.d, callback, burnin, total, max_order, xsamples, ysamples, credible_interval)
    return resultset1d(res.r)

def regression_part1d_zero(dataset, pd, burnin=10000, total=50000, max_partitions=20, xsamples=100, ysamples=100, credible_interval=0.95):
    res = py_regression_part1d_zero(dataset.d, pd, burnin, total, max_partitions, xsamples, ysamples, credible_interval)
    return resultset1d(res.r)

def regression_part1d_natural(dataset, pv, pd, burnin=10000, total=50000, max_partitions=20, xsamples=100, ysamples=100, credible_interval=0.95):
    res = py_regression_part1d_natural(dataset.d, pv, pd, burnin, total, max_partitions, xsamples, ysamples, credible_interval)
    return resultset1d(res.r)

def regression_part1d(dataset, pd, burnin=10000, total=50000, max_partitions=20, max_order=5, xsamples=100, ysamples=100, credible_interval=0.95):
    res = py_regression_part1d(dataset.d, pd, burnin, total, max_partitions, max_order, xsamples, ysamples, credible_interval)
    return resultset1d(res.r)

def regression_part1d_sampled(dataset, callback, pd, burnin=10000, total=50000, max_partitions=20, max_order=5, xsamples=100, ysamples=100, credible_interval=0.95):
    res = py_regression_part1d_sampled(dataset.d, callback, pd, burnin, total, max_partitions, max_order, xsamples, ysamples, credible_interval)
    return resultset1d(res.r)

def check_list_like(x):
    return isinstance(x, collections.abc.Iterable) and not isinstance(x, (str, bytes))
