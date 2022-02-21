# ANU Inversion Course Package

[![Build](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml/badge.svg?branch=main)](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml)

This package contains resources to be used in the [inversion course practicals](https://github.com/anu-ilab/JupyterPracticals).

## Installation (experimental stage)

```bash
pip install --index-url https://test.pypi.org/simple/ --extra-index-url https://pypi.org/simple anu-inversion-course
```

## Installation

(optional) It's recommended to use a virtual environment (using `conda` or `venv`, etc.) so that it doesn't conflict with your other Python projects. 

Type the following in your terminal:

```bash
pip install anu-inversion-course
```

And when you run `jupyter-lab` to do the practicals, make sure you are in the same environment as where your `anu-inversion-course` was installed. You can try to test this by checking if the following commands give you similar result:

```bash
$ which pip
<some-path>/bin/pip
$ which jupyter-lab
<same-path>/bin/jupyter-lab
$ pip list | grep anu-inversion-course
anu-inversion-course               0.1.0
```



