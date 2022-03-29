# ANU Inversion Course Package

[![Build](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml/badge.svg?branch=main)](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml)
[![PyPI version](https://badge.fury.io/py/ANU-inversion-course.svg)](https://badge.fury.io/py/ANU-inversion-course)

This package contains resources to be used in the [inversion course practicals](https://github.com/anu-ilab/JupyterPracticals).

## Table of contents
- [Getting started](README.md#getting-started)
  - [Set up virtual environment](README.md#1-set-up-virtual-environment)
  - [Dependency](README.md#2-dependency)
  - [Installation](README.md#3-installation)
  - [Check](README.md#4-check)
- [Troubleshooting](README.md#troubleshooting)
- [Developer notes](README.md#developer-notes)

## Getting started

### 1. Set up virtual environment
(optional) It's recommended to use a virtual environment (using `conda` or `venv`, etc.) so that it doesn't conflict with your other Python projects. Create a new environment with 
```console
conda create -n inversion_course python=3.10 scipy
``` 
and enter that environment with 
```console
conda activate inversion_course
```
and if you are on MacOS M1 chip:
```console
conda install -c conda-forge gfortran
```

### 2. Dependency

> If you are on Linux/Windows and have followed above step to install `scipy` using `conda`, then feel free to skip this step.

This package requires you to have `gfortran` (or at least `libgfortran` on Linux/Windows) installed. Check [this page](https://fortran-lang.org/learn/os_setup/install_gfortran) (and notes below for MacOS) for instructions on how to install `gfortran`.

#### Notes for installing `gfortran` on MacOS
1. Install `XCode` (from App Store)
2. Install command line tools `xcode-select --install`
3. *For M1 chip*: if you've set up a conda environment, then `conda install -c conda-forge gfortran` will work
4. *If step 3 doesn't suit you*: follow the instructions in [this page](https://fortran-lang.org/learn/os_setup/install_gfortran) about how to install `gfortran`

<details>
  <summary>Reasons for why we need `gfortran` (only) on MacOS</summary>

- A *Fortran compiler* is needed for MacOS to build C/Fortran libraries from source, as [wheels](https://packaging.python.org/en/latest/glossary/#term-Wheel) are not provided for MacOS due to a problem described [here](https://github.com/lanl/ExactPack/issues/2). 
- Fortran libraries (`libgfortran.5.dylib`) is also needed for other operating systems. Otherwise `anu_inversion_course.rf` will fail to import. If you've followed step one above to install `scipy` via `conda`, then `libgfortran5` is downloaded so no further action is needed.
- The issue on MacOS is possible to fix, but with some effort of uploading the package to `conda`, so this will be in future work
  
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

If you find problems *importing* `anu_inversion_course.rf`, try to search the error message you get. [Here](https://stackoverflow.com/questions/58793399/importerror-library-not-loaded-for-f2py) contains a nice explanation for the possible cause. And here is how to locate `libgfortran`:
```console
gfortran --print-file-name libgfortran.5.dylib
```

## Developer Notes

Check out [NOTES.md](NOTES.md) if you'd like to contribute to this package.

1. [Getting started](NOTES.md#getting-started)
2. [Cheatsheet](NOTES.md#cheatsheet)
   1. [conda environment](NOTES.md#conda-environment)
   2. [git operations](NOTES.md#git-operations)
   3. [package development](NOTES.md#package-development)
   4. [package metadata](NOTES.md#package-metadata)
   5. [package building test & release](NOTES.md#package-building-test--release)
3. [Adding C/C++ extensions](NOTES.md#adding-cc-extensions)
4. [Adding Fortran extensions](NOTES.md#adding-fortran-extensions)
5. [More references](NOTES.md#more-references)
6. [Appendix - semantic versioning](NOTES.md#appendix-i---sementic-versioning)
