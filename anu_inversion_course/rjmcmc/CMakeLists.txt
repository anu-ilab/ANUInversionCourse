################## Compiling C rjmcmc library #####################################
set(pybind11_module_name_rjmcmc "_rjmcmc")
file(GLOB rjmcmc_src
    "_rjmcmc.cpp"
    "python/swig/rjmcmc_helper.c"
    "src/*.c"
)
pybind11_add_module(${pybind11_module_name_rjmcmc} SHARED ${rjmcmc_src})
target_include_directories(${pybind11_module_name_rjmcmc} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS ${pybind11_module_name_rjmcmc} LIBRARY DESTINATION anu_inversion_course)
