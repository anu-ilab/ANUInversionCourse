# Developer Notes

Here are some notes that might be useful for future contributors.

## Table of contents
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
7. [Additional Notes about gfortran](NOTES.md#additional-notes-about-gfortran)

## Getting started

**Step 1**. To clone this repository:
```bash
$ cd <path-to-parent-folder>
$ git clone https://github.com/anu-ilab/ANUInversionCourse.git
```

**Step 2**. Install gfortran as per this [instruction](https://fortran-lang.org/learn/os_setup/install_gfortran).

Check that the version is not something as old as 4 or 5:
```bash
$ gfortran --version
```

**Step 3**. To set up environment and install the package (in developer mode):
```bash
# recommended environment set up (optional)
$ conda env create -f environment_dev.yml
$ conda activate inversion_course_dev

# double check that the gfortran installed above is still in the path
$ gfortran --version

# begin installation
$ cd <path-to-parent-folder>/ANUInversionCourse
$ pip install -e .
```

**Step 4**. Now you can test that it has been installed successfully using Python's interactive mode:
```bash
$ python
>>> from anu_inversion_course import rjmcmc
>>> exit()
```

If the first line runs without any error (so you see the second line `>>>`), then it works. So feel free to type `exit()` to quit the interactive mode session.

----
## Cheatsheet
### conda environment
- To **enter** conda virtual environment: `conda activate inversion_course_dev`
- To **exit** conda virtual environment: `conda deactivate`
- To **remove** a conda environment: `conda env remove -n inversion_course_dev`
- To **create** a conda environment from file: `conda env create -f environment_dev.yml`

### git operations
- To **clone** a git repository: `git clone https://github.com/anu-ilab/ANUInversionCourse.git`
- To **prepare** to commit your changes: `git add <file-you-want-to-commit> <maybe-another-file>`
- To **commit** your changes (very much like a "save" operation in the context of git): `git commit -m "put meaningful commit message here so you know what's been changed in this commit in the future"` (e.g. `git commit -m "Updated developer notes"`)
- To **push** your changes: `git push origin main` (where `origin` refers to the remote repository, and `main` refers to the remote branch, for which `main` is the default name)
- To **retrieve** changes from remote into your local clone (maybe after someone else pushed a change): `git pull origin main`

### package development
- To **install** the Python package in your current environment: `pip install -e .`
- To **install** the Python package **again** after you've made changes in C/C++/Fortran or `CMakeLists.txt`: `rm -rf _skbuild; pip uninstall anu-inversion-course -y; pip install -e .`

### package metadata
- To change package **metadata** (like keywords, author, etc): edit the file `setup.cfg`
- To specify/change package **dependency** (other Python packages that you'd like to ensure users have before installing anu-inversion-course): edit the `install_requires` list inside `setup.cfg` as well as `setup.py`

### package building test & release
- To **automatically publish** your changes to Python packaging index: edit `_version.py` with an increased version number and push your change to remote. Check [Appendix](NOTES.md#appendix-i---sementic-versioning) for how to version it.
  - As long as you've made a change in file `_verison.py`, a github action will be triggered to build distributions and upload them to [test-pypi](https://test.pypi.org/project/ANU-inversion-course/) and [pypi](https://pypi.org/project/ANU-inversion-course/).
- To **manually publish** (when the above workflow fails): go to [publish workflow](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/publish_pypi.yml), within the light blue box click "Run workflow" -> "Run workflow" and wait
- To **automatically test building** of the package: as long as you've made changes under the source folder `anu_inversion_course`, then a github action will be triggered to test building this package on *Linux/MacOS/Windows* for Python version *3.8, 3.9 and 3.10*.
- To **manually test building**: go to [test building workflow](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml), within the light blue box click "Run workflow" -> "Run workflow" and wait
- To check **workflow status**: go to [publish workflow](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/publish_pypi.yml) or [test building workflow](https://github.com/anu-ilab/ANUInversionCourse/actions/workflows/build_wheels.yml), click on the top (most recent) workflow run and wait for the page to load

----
## Adding C/C++ extensions
- Step 1: move the source code inside a new folder under `anu_inversion_course`, say `anu_inversion_course/my_cpp_extension`. We assume the source code (in a file named `_my_cpp_extension.cpp`) to be a simple function, for example:
```cpp
#include <iostream>
void hello(String name) {
    std::cout << "Hello " << name;
}
```

- Step 2: use [pybind11](https://pybind11.readthedocs.io/en/stable/) to wrap this function, by adding some extra code:
```cpp
#include <pybind11/pybind11.h>
#include <Python.h>

#include <iostream>
void hello(String name) {
    std::cout << "Hello " << name;
}

namespace py = pybind11;
PYBIND11_MODULE(_my_cpp_extension, m) {
    m.doc() = "My CPP Extension";
    m.def("hello", &hello, "Print hello message given a name");
}
```

- Step 3: add the path to the folder that contains the above file to the root-level `CMakeLists.txt` file. At the bottom of the root-level `CMakeLists.txt` file, add `add_subdirectory(anu_inversion_course/my_cpp_extension)`

- Step 4: create a new file `CMakeLists.txt` under `anu_inversion_course/my_cpp_extension`, with the following lines
```cmake
set(pybind11_module_name_my_cpp_extension "_my_cpp_extension")
pybind11_add_module(${pybind11_module_name_my_cpp_extension} SHARED my_cpp_source.cpp my_cpp_wrapper.cpp)
install(TARGETS ${pybind11_module_name_my_cpp_extensions} LIBRARY DESTINATION anu_inversion_course)
```

- Step 5: compile the extension by calling Python's install `pip install -e .` on the root level, and you will see a compiled extension (ending with `.so` if you are on MacOS) appear under folder `anu_inversion_course`.

> Checkout reversible jump MCMC (rjmcmc) for a more complex example: [cmake file](anu_inversion_course/rjmcmc/CMakeLists.txt), [C++ wrappers](anu_inversion_course/rjmcmc/_rjmcmc.cpp) (on top of source code) and [Python wrapper](anu_inversion_course/rjmcmc.py) (on top of compiled library)

## Adding Fortran extensions

- Step 1: (similarly) move the source code inside a new folder, like `anu_inversion_course/my_f77_extension`. We assume the source code (in a file named `_my_f77_extension.f`) to be a simple function, for example:

```fortran
C file: _my_f77_extension.f
      subroutine add_one(n, res)

      integer n
      integer res
      res = n + 1
      
      end subroutine add_one
C end file _my_f77_extension.f
```

- Step 2: annotate the function signature using [f2py](https://numpy.org/doc/stable/f2py/f2py.getting-started.html) rules:

```fortran
C file: _my_f77_extension.f
      subroutine add_one(n, res)

      integer n
      integer res
Cf2py intent(in) n
Cf2py intent(out) res

      res = n + 1
      
      end subroutine add_one
C end file _my_f77_extension.f
```

- Step 3: add the path to the folder that contains the above file to the root-level `CMakeLists.txt` file. At the bottom of the root-level `CMakeLists.txt` file, add `add_subdirectory(anu_inversion_course/my_f77_extension)`

- Step 4: create a new file `CMakeLists.txt` under `anu_inversion_course/my_f77_extension`, with the following lines
```cmake
set(f2py_module_name_my_f77_extension "_my_f77_extension")
set(fortran_77_src_file "${CMAKE_CURRENT_SOURCE_DIR}/_my_f77_extension.f")
set(generated_module_file_77 ${CMAKE_CURRENT_BINARY_DIR}/${f2py_module_name_my_f77_extension}${PYTHON_EXTENSION_MODULE_SUFFIX})
add_custom_target(${f2py_module_name_my_f77_extension} ALL DEPENDS ${generated_module_file_77})
add_custom_command(
  OUTPUT ${generated_module_file_77}
  COMMAND ${F2PY_EXECUTABLE}
    -m ${f2py_module_name_my_f77_extension}
    -c
    ${fortran_77_src_file}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
install(FILES ${generated_module_file_77} DESTINATION anu_inversion_course)
```

- Step 5: compile the extension by calling Python's install `pip install -e .` on the root level, and you will see a compiled extension (ending with `.so` if you are on MacOS) appear under folder `anu_inversion_course`.

> Checkout receiver function (rfc) for a more complex example: [cmake file](anu_inversion_course/rfc/CMakeLists.txt), [Fortran code with signature annotation](anu_inversion_course/rfc/RF.F90) and [Python wrapper](anu_inversion_course/rf.py) (on top of compiled library)


## More references
- [scikit-build documentation](https://scikit-build.readthedocs.io/en/latest/)
  - you might find the [CMake Modules](https://scikit-build.readthedocs.io/en/latest/) part especially useful
- for Fortran bindings: [f2py](https://numpy.org/doc/stable/f2py/)
  - check the receiver function (rfc) example: [cmake file](anu_inversion_course/rfc/CMakeLists.txt), [Fortran code with signature annotation](anu_inversion_course/rfc/RF.F90) and [Python wrapper](anu_inversion_course/rf.py) (on top of compiled library)
- for C/C++ bindings: [pybind11](https://pybind11.readthedocs.io/en/stable/)
  - check the reversible jump MCMC (rjmcmc) example: [cmake file](anu_inversion_course/rjmcmc/CMakeLists.txt), [C++ wrappers](anu_inversion_course/rjmcmc/_rjmcmc.cpp) (on top of source code) and [Python wrapper](anu_inversion_course/rjmcmc.py) (on top of compiled library)

## Appendix I - sementic versioning

[Here](https://semver.org/) is the full description of semantic versioning. 

TLDR, for a version number `a.b.c`:
  - `a` is the major version, and it's increased only when there's backward incompatible changes
  - `b` is the minor version, and it's increased when there'a backward compatible change
  - `c` is the patch version, and it's increased when there are only bug fixes related change
  - the version `1.0.0` indicates the first official release (that defines the public API)
  - 1.0.0.dev1 < 1.0.0.dev2 < 1.0.0 < 1.0.1

## Additional Notes about gfortran

- A *Fortran compiler* is needed for MacOS to build C/Fortran libraries from source, as [wheels](https://packaging.python.org/en/latest/glossary/#term-Wheel) are not provided for MacOS due to a problem described [here](https://github.com/lanl/ExactPack/issues/2). 
- Fortran libraries (`libgfortran.5.dylib`) is also needed for other operating systems. Otherwise `anu_inversion_course.rf` will fail to import. If you've followed step one above to install `scipy` via `conda`, then `libgfortran5` is downloaded so no further action is needed.
- The issue on MacOS is possible to fix, but with some effort of uploading the package to `conda`, so this will be in future work
