# ANU Inversion Course Package

[![Build](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml/badge.svg?branch=main)](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml)
[![PyPI version](https://badge.fury.io/py/ANU-inversion-course.svg)](https://badge.fury.io/py/ANU-inversion-course)

This package contains resources to be used in the [inversion course practicals](https://github.com/anu-ilab/JupyterPracticals).

## Installation

(optional) It's recommended to use a virtual environment (using `conda` or `venv`, etc.) so that it doesn't conflict with your other Python projects. Create a new environment with `conda create -n inversion_course python=3.10 jupyter-lab pip` and enter that environment with `conda activate inversion_course`.

### Dependency
A *Fortran compiler* is needed for Apple Silicon M1, and Fortran libraries (`libgfortran11`) is also needed for other operating systems. So remember to have `gfortran` installed before installing this package. Check [this page](https://fortran-lang.org/learn/os_setup/install_gfortran) for instructions on how to download it.

### Install
Type the following in your terminal:

```bash
pip install anu-inversion-course
```
### Check
And when you run `jupyter-lab` to do the practicals, make sure you are in the same environment as where your `anu-inversion-course` was installed. You can try to test this by checking if the following commands give you similar result:

```bash
$ which pip
<some-path>/bin/pip
$ which jupyter-lab
<same-path>/bin/jupyter-lab
$ pip list | grep anu-inversion-course
anu-inversion-course               0.1.0
```



