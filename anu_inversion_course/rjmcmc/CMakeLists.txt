################## Compiling C rjmcmc library #####################################
# set up swig
include(${SWIG_USE_FILE})
set(CMAKE_SWIG_FLAGS "")

# include python
find_package(PythonLibs)

# metadata
set(swig_module_name_rjmcmc "_rjmcmc")
set(swig_python_setup_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/setup.py")
set(swig_interface_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc.i")
set(swig_helper_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc_helper.c")
set(swig_wrap_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc_wrap.c")
set(swig_python_file_rjmcmc "${CMAKE_CURRENT_SOURCE_DIR}/python/swig/rjmcmc.py")
file(GLOB rjmcmc_src
    "python/swig/rjmcmc_helper.h"
    "python/swig/rjmcmc_helper.c"
    "python/swig/rjmcmc_wrap.c"
    "include/*.h"
    "src/*.c"
)

set_source_files_properties(${swig_interface_file_rjmcmc} PROPERTIES SWIG_FLAGS "-includeall")
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rjmcmc/rjmcmc_config.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/rjmcmc/rjmcmc_config.h
    @ONLY
)
add_custom_command(
    OUTPUT ${swig_wrap_file_rjmcmc} ${swig_python_file_rjmcmc}
    COMMAND ${SWIG_EXECUTABLE} -python ${swig_interface_file_rjmcmc}
)
add_library(${swig_module_name_rjmcmc} MODULE ${rjmcmc_src})
target_include_directories(${swig_module_name_rjmcmc} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${swig_module_name_rjmcmc} PRIVATE ${PYTHON_INCLUDE_PATH})
target_link_libraries(${swig_module_name_rjmcmc} ${PYTHON_LIBRARIES})
python_extension_module(${swig_module_name_rjmcmc})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpython")
install(TARGETS ${swig_module_name_rjmcmc} LIBRARY DESTINATION anu_inversion_course/rjmcmc/python/swig)

# $ swig -python example.i
# $ gcc -O2 -fPIC -c example.c
# $ gcc -O2 -fPIC -c example_wrap.c -I/usr/local/include/python2.5
# $ gcc -shared example.o example_wrap.o -o _example.so
