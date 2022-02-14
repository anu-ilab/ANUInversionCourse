#!/usr/bin/env python3
#-*- coding:utf-8 -*-
#!/usr/bin/env python3
#-*- coding:utf-8 -*-

import os
import sys

import matplotlib
import matplotlib.pyplot

if __name__ == '__main__':

    f = open('regression.misfit', 'r')
    misfit = list(map(float, f.readlines()))
    f.close()
    
    fig = matplotlib.pyplot.figure(1)

    a = fig.add_subplot(111)

    a.plot(misfit)
    a.set_title('Misfit History')
    a.set_xlabel('Iteration')
    a.set_ylabel('Misfit')
                
    matplotlib.pyplot.show()
        
