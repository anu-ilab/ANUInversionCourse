from anu_inversion_course._rjmcmc import (
    dataset1d_t,
    dataset1d_load_known
)

class dataset1d():
    def __init__(self, filename=None, x=None, y=None, n=None):
        if filename is not None:
            self.d = dataset1d_load_known("data.txt")
            print(self.d.xmin)
            # self.d = _dataset1d()
