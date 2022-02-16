from anu_inversion_course._rjmcmc import (
    dataset1d_t,
    dataset1d_load_known,
    dataset1d_load_fixed,
    dataset1d_create,
)

import collections
import numpy as np


class dataset1d():
    def __init__(self, filename=None, n=None, x=None, y=None):
        if filename is not None and n is None:
            self.d = dataset1d_load_known(filename)
        elif filename is not None and n is not None:
            self.d = dataset1d_load_fixed(filename, n)
        elif x is not None and y is not None and n is not None:
            if not check_list_like(x) or not check_list_like(y) or not check_list_like(n):
                raise ValueError("Parameter must be a list of floating point values")
            x = np.asanyarray(x, dtype=np.float64)
            y = np.asanyarray(y, dtype=np.float64)
            n = np.asanyarray(n, dtype=np.float64)
            if x.shape[0] != y.shape[0] or x.shape[0] != n.shape[0]:
                raise ValueError("Parameters must have the same length")
            self.d = dataset1d_create(x.shape[0])
            self.x = x

def check_list_like(x):
    return isinstance(x, collections.abc.Iterable) and not isinstance(x, (str, bytes))
