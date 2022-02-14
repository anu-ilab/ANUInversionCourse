#!/usr/bin/env python3
#-*- coding:utf-8 -*-
#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import random

xmin = 0.0
xmax = 100.0

def f(x):
    global xmin, xmax

    cx1 = xmin + (xmax - xmin)/3.0
    cx2 = xmin + 2.0*(xmax - xmin)/3.0
    if (x < cx1):
        return 0.0
    elif (x < cx2):
        b = 10.0
        return 10.0
    else:
        return -15.0

def linspace(minv, maxv, n):
    return [float(x)/float(n-1) * (maxv - minv) + minv for x in range(n)]

if __name__ == '__main__':
    
    npoints = 100
    noise = 5.0

    x = linspace(xmin, xmax, npoints);
    y = list(map(f, x))
    yn = [random.normalvariate(x, noise) for x in y]
    n = [noise] * len(yn)

    f = open('data.txt', 'w')
    f.write('\n'.join([' '.join(map(str, x)) for x in zip(x, yn, n)]))
    f.close()

