#!/usr/bin/env python3
#-*- coding:utf-8 -*-
#!/usr/bin/env python3
#-*- coding:utf-8 -*-
import random

xmin = 0.0
xmax = 100.0

def f(x):
    global xmin, xmax

    cx = (xmax + xmin)/2.0
    if (x < cx):
        aa = 0.5
        ab = -0.5

        return aa*x + ab
    else:
        ba = -0.5
        bb = 8.5
        
        return ba*x + bb

def linspace(minv, maxv, n):
    return [float(x)/float(n-1) * (maxv - minv) + minv for x in range(n)]

if __name__ == '__main__':
    
    npoints = 100
    noise = 5.0

    x = linspace(xmin, xmax, npoints);
    y = list(map(f, x))
    yn = [random.normalvariate(x, noise) for x in y]

    f = open('data.txt', 'w')
    f.write('\n'.join([' '.join(map(str, x)) for x in zip(x, yn)]))
    f.close()

