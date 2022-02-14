#!/usr/bin/env python3
#-*- coding:utf-8 -*-
#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import random

def f(x):

    a = 0.00015
    b = -0.005
    c = -0.550
    d = 3.50

    return a*x*x*x + b*x*x + c*x + d

def linspace(minv, maxv, n):
    return [float(x)/float(n - 1) * (maxv - minv) + minv for x in range(n)]

if __name__ == '__main__':

    xmin = 0.0
    xmax = 100.0
    noise = 10.0
    npoints = 100

    x = linspace(xmin, xmax, npoints);
    y = list(map(f, x))
    yn = [random.normalvariate(x, noise) for x in y]
    n = [noise] * len(yn)

    f = open('data.txt', 'w')
    f.write('\n'.join([' '.join(map(str, x)) for x in zip(x, yn, n)]))
    f.close()

