file(GLOB rjmcmc_src
    "rjmcmc.cpp"
    "python/swig/rjmcmc_helper.h"
    "python/swig/rjmcmc_helper.c"
    "include/*.h"
    "src/*.c"
)
message(${rjmcmc_src})
pybind11_add_module(rjmcmc ${rjmcmc_src})
target_include_directories(rjmcmc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
install(TARGETS rjmcmc LIBRARY DESTINATION anu_inversion_course)
