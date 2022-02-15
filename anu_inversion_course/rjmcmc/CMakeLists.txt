################## Compiling C rjmcmc library #####################################
# set up swig
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

# include python
find_package(PythonLibs)
include_directories(${PYTHON_INCLUDE_PATH})

# metadata
set(swig_module_name_rjmcmc "rjmcmc")
set(swig_python_setup_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/setup.py")
set(swig_interface_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc.i")
set(swig_helper_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc_helper.c")
set(swig_wrap_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc_wrap.c")
file(GLOB rjmcmc_src
    "python/swig/rjmcmc_helper.h"
    "python/swig/rjmcmc_helper.c"
    "include/*.h"
    "src/*.c"
)

set_source_files_properties(${swig_interface_file_rjmcmc} PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${swig_interface_file_rjmcmc} PROPERTIES SWIG_FLAGS "-includeall")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rjmcmc/rjmcmc_config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rjmcmc/rjmcmc_config.h
    @ONLY
)
add_custom_command(
    OUTPUT ${swig_wrap_file_rjmcmc}
    COMMAND ${SWIG_EXECUTABLE} -python ${swig_interface_file_rjmcmc}
)
add_library(${swig_module_name_rjmcmc} MODULE ${rjmcmc_src})
target_include_directories(${swig_module_name_rjmcmc} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS ${swig_module_name_rjmcmc} LIBRARY DESTINATION anu_inversion_course)


# file(GLOB rjmcmc_src
#     "rjmcmc.cpp"
#     "python/swig/rjmcmc_helper.h"
#     "python/swig/rjmcmc_helper.c"
#     "include/*.h"
#     "src/*.c"
# )
# message(${rjmcmc_src})
# pybind11_add_module(rjmcmc ${rjmcmc_src})
# target_include_directories(rjmcmc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# install(TARGETS rjmcmc LIBRARY DESTINATION anu_inversion_course)

# set(generated_module_file_rjmcmc ${CMAKE_CURRENT_BINARY_DIR}/${swig_module_name_rjmcmc}${PYTHON_EXTENSION_MODULE_SUFFIX})
# add_custom_target(${swig_module_name_rjmcmc} ALL DEPENDS ${generated_module_file_rjmcmc})
# add_custom_command(
#     OUTPUT ${generated_module_file_rjmcmc}
#     COMMAND ${PYTHON_EXECUTABLE}
#         ${swig_python_setup_rjmcmc}
# )
# install(FILES ${generated_module_file_rjmcmc} DESTINATION anu_inversion_course)

# $ swig -python example.i
# $ gcc -O2 -fPIC -c example.c
# $ gcc -O2 -fPIC -c example_wrap.c -I/usr/local/include/python2.5
# $ gcc -shared example.o example_wrap.o -o _example.so

# include_directories(python/swig)
# include_directories(include)
# include_directories(src)

# swig_add_library(rjmcmc TYPE MODULE LANGUAGE python SOURCES python/swig/rjmcmc.i)
# python_extension_module(rjmcmc)
# # swig_link_libraries(rjmcmc ${PYTHON_LIBRARIES})
# install(TARGETS rjmcmc DESTINATION anu_inversion_course)
