from anu_inversion_course._rjmcmc import (
    dataset1d_t,
    dataset1d_load_known,
    dataset1d_load_fixed,
    dataset1d_create,
    resultset1d_t,
    py_resultset1d_get_histogram,
    # resultset1dfm_t,
    resultset1dfm_get_global_parameter,
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
            self.d = dataset1d_create(x.shape[0])
            for i in range(x.shape[0]):
                print(type(x[i]))
                print(type(self.d.points))
                print(type(self.d.points[i]))
                print(type(self.d.points[i].x))
                self.d.points[i].x = x[i]
                self.d.points[i].y = y[i]
                self.d.points[i].n = n[i]
            self.d.xmin = np.min(x)
            self.d.xmax = np.max(x)
            self.d.ymin = np.min(y)
            self.d.ymax = np.max(y)
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
        return self.r.propose
            
    def acceptance(self):
        return self.r.accept

    def partitions(self):
        return self.r.partitions

    def order_histogram(self):
        return self.r.order

    def partition_histogram(self):
        return self.r.partitions

    def partition_location_histogram(self):
        return self.r.partition_x_hist

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

    def lambda_history(self):
        return self.r.getattr("lambda")

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


def check_list_like(x):
    return isinstance(x, collections.abc.Iterable) and not isinstance(x, (str, bytes))
