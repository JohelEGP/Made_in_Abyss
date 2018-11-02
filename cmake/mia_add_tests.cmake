if(NOT BUILD_TESTING)
    return()
endif()

function(mia_add_test name)
    add_executable(mia_test_${name} test/${name}.cpp)
    target_compile_options(mia_test_${name} PRIVATE ${ARGN})
    target_link_libraries(mia_test_${name} PRIVATE mia)
    add_test(mia_test_${name} mia_test_${name})
endfunction()

mia_add_test(include_ext_std_chrono)
mia_add_test(include_concepts)
mia_add_test(include_units)
mia_add_test(all_includes)
mia_add_test(concepts)
mia_add_test(units)
