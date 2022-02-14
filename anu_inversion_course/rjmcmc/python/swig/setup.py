#!/usr/bin/env python3
#-*- coding:utf-8 -*-

from __future__ import print_function
#from __future__ import unicode_literals
#  Commented because calls packages that expect byte strings in python2
#  and utf-8 in python3.

import sys
import subprocess

#from distutils.core import setup, Extension
from setuptools import setup, Extension

def do_pkgconfig(pkgname):

    try:
        args = subprocess.check_output(['pkg-config', '--libs', pkgname]).decode()
    except subprocess.CalledProcessError:
        return None

    libpaths = []
    libs = []
    for arg in args.split():
        if arg[:2] == '-l':
            libs.append(arg[2:])
        elif arg[:2] == '-L':
            libpaths.append(arg[2:])
        else:
            print('warning: unknown lib argument: "{:s}"'.format(arg))

    try:
        args = subprocess.check_output(['pkg-config', '--cflags', pkgname])
    except subprocess.CalledProcessError:
        return None

    incpaths = []
    for arg in args.split():
        if arg[:2] == '-I':
            incpaths.append(arg[2:])

    return (incpaths, libpaths, libs)

libraries = []
include_dirs = []

if sys.platform == 'linux2' or sys.platform == 'cygwin':
    cfg = do_pkgconfig('rjmcmc')
    if cfg == None:
        print(
          'error: Unable to configure package using pkg-config'
          'Try setting PKG_CONFIG_PATH environment variable to the '
          'install location of rjmcmc. eg:'
          '> export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig'
          '> python setup.by build')
        sys.exit(-1)
    
    include_dirs, library_dirs, libraries = cfg

elif sys.platform == 'darwin':
    include_dirs=['../../macosx/pythoninstall/include']
    library_dirs=['../../macosx/pythoninstall/lib']
    libraries=['rjmcmc']
elif sys.platform == 'win32':
    libraries.append('rjmcmc')
    library_dirs=['../../win32/Release']
    include_dirs.extend(['../../include', '../../win32'])
else:
    library_dirs=[]

rjmcmc_module = Extension('_rjmcmc',
                          sources=['rjmcmc.i',
                                   'rjmcmc_helper.c'],
                          swig_opts=['-I../../include'],
                          library_dirs=library_dirs,
                          libraries=libraries,
                          include_dirs=include_dirs
                          )

setup (name = 'rjmcmc',
       version = '0.9.15',
       author      = "Rhys Hawkins <Rhys.Hawkins@anu.edu.au>",
       author_email = 'Rhys.Hawkins@anu.edu.au',
       url = 'http://inverse.anu.edu.au',
       license = 'GPL',
       description = "Python interface to the 1D regression routines of the rjmcmc library",
       ext_modules = [rjmcmc_module],
       py_modules = ["rjmcmc"],
       requires = [],
       provides = [],
       obsoletes = []
       )
