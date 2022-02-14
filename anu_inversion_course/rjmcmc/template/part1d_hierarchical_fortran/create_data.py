#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import random

def real_function(x):

    if x < 5.0:
        return x
    else:
        return 10.0 - x

xmin = 0.0
xmax = 10.0
npoints = 100
x = [float(x)/float(npoints - 1) * (xmax - xmin) for x in range(npoints)]
y = list(map(real_function, x))

f = open('realdata.txt', 'w')
for (x, y) in zip(x, y):
    f.write('%f %f\n' % (x, y))
f.close()

npoints = 20
xr = [float(x)/float(npoints - 1) * (xmax - xmin) for x in range(npoints)]
yr = list(map(real_function, xr))

sigma = 1.0

y = [x + random.normalvariate(0.0, sigma) for x in yr]

f = open('data.txt', 'w')
for (x, y) in zip(xr, y):
    f.write('%f %f\n' % (x, y))
f.close()



