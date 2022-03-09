# ANU Inversion Course Package

[![Build](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml/badge.svg?branch=main)](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml)
[![PyPI version](https://badge.fury.io/py/ANU-inversion-course.svg)](https://badge.fury.io/py/ANU-inversion-course)

This package contains resources to be used in the [inversion course practicals](https://github.com/anu-ilab/JupyterPracticals).

## Getting started

### 1. Set up virtual environment
(optional) It's recommended to use a virtual environment (using `conda` or `venv`, etc.) so that it doesn't conflict with your other Python projects. Create a new environment with 
```console
conda create -n inversion_course python=3.10 jupyterlab
``` 
and enter that environment with 
```console
conda activate inversion_course
```

### 2. Dependency

This package requires you to have `gfortran` installed. Check [this page](https://fortran-lang.org/learn/os_setup/install_gfortran) (and notes below for MacOS) for instructions on how to install `gfortran`.

<details>
  <summary>Notes for installing `gfortran` on MacOS</summary>

  Make sure you have `xcode` installed (from App Store), and then the command line tools installed by opening terminal and typing in:
  ```console
  xcode-select --install
  ```

  *For M1 chip*: if you've set up a conda environment, then another option is to install `gfortran` using `conda`:
  ```console
  conda install -c conda-forge gfortran
  ```
  The `gfortran` version is updated (`gfortran-11`) for M1 chip but not for the Intel one (as per [this](https://anaconda.org/conda-forge/gfortran))

</details>

<details>
  <summary>Reasons for why we need `gfortran`</summary>

- A *Fortran compiler* is needed for MacOS to build C/Fortran libraries from source, as [wheels](https://packaging.python.org/en/latest/glossary/#term-Wheel) are not provided for MacOS due to a problem described [here](https://github.com/lanl/ExactPack/issues/2). 
- Fortran libraries (`libgfortran.5.dylib`) is also needed for other operating systems. Otherwise `anu_inversion_course.rf` will fail to import.
  
</details>

### 3. Installation
Type the following in your terminal:

```bash
pip install anu-inversion-course
```
### 4. Check
And when you run `jupyter-lab` to do the practicals, make sure you are in the same environment as where your `anu-inversion-course` was installed. You can try to test this by checking if the following commands give you similar result:

```console
$ which pip
<some-path>/bin/pip
$ which jupyter-lab
<same-path>/bin/jupyter-lab
$ pip list | grep ANU-inversion-course
ANU-inversion-course               0.1.0
```

## Troubleshooting

If you find problems importing `anu_inversion_course.rf`, try to search the error message you get. And here is how to locate `libgfortran`:
```console
gfortran --print-file-name libgfortran.5.dylib
```

