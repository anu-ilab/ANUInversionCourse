# Developer Notes

Here are some notes that might be useful for future contributors.

## Contents
1. [Getting started](NOTES.md#getting-started)
2. [Knowledge base](NOTES.md#knowledge-base)
3. [Publish your changes](NOTES.md#publish-your-changes)

## Getting started

To clone this repository:
```bash
$ cd <path-to-parent-folder>
$ git clone https://github.com/anu-ilab/ANUInversionCourse.git
```

To install the package in developer mode:
```bash
# recommended environment set up (optional)
$ conda create -n inversion_course_dev pip -y
$ conda activate inversion_course_dev
$ conda install -c conda-forge gfortran

# begin installation
$ cd <path-to-parent-folder>/ANUInversionCourse
$ pip install -e .
```

Now you can test that it has been installed successfully using Python's interactive mode:
```bash
$ python
>>> from anu_inversion_course import rjmcmc
>>> exit()
```

If the first line runs without any error (so you see the second line `>>>`), then it works. So feel free to type `exit()` to quit the interactive mode session.

The `-e` option in the `pip install` command means "developer mode", so that you won't have to install the whole package again whenever you make a change to the source code. However, you do need to run `pip install -e .` if you'd like to test your change in any compiled language (e.g. in your C/C++/Fortran code).

## Knowledge base
<details>
  <summary>Click to expand!</summary>
  
### 1. Package metadata
`setup.py`, `setup.cfg` & `pyproject.toml`

### 2. What is a Python wheel
https://packaging.python.org/en/latest/specifications/binary-distribution-format/

### 3. Where to specify dependencies

> Note that the `install-requires` list in `setup.py`/`setup.cfg` is different from the `requires` under `build-system` in file `pyproject.toml`, in that the latter refers to what packages are required when building this package (e.g. generating wheels).
</details>

## Publish your changes

### Build the wheels

### upload to PyPI

