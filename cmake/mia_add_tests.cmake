if(NOT BUILD_TESTING)
    return()
endif()

include(mia_find_tests_dependencies)

# ```
# mia_add_test(<name>
#   [COMPILE_OPTIONS options...]
#   [LINK_LIBRARIES libraries...])
# ```
# Adds the executable test target `mia_test_${name}`.
# `COMPILE_OPTIONS` specifies its `PRIVATE` compile options.
# `LINK_LIBRARIES` specifies its `PRIVATE` link libraries besides `mia::mia`.
function(mia_add_test name)
    cmake_parse_arguments(PARSE_ARGV 0 ADD_TEST
        "" "" "COMPILE_OPTIONS;LINK_LIBRARIES")

    add_executable(mia_test_${name} test/${name}.cpp)
    target_compile_options(mia_test_${name} PRIVATE ${ADD_TEST_COMPILE_OPTIONS})
    target_link_libraries(mia_test_${name}
        PRIVATE ${ADD_TEST_LINK_LIBRARIES} mia::mia)
    add_test(mia_test_${name} mia_test_${name})
endfunction()

mia_add_test(include_ext_std_chrono)
mia_add_test(include_concepts)
mia_add_test(include_units)
mia_add_test(all_includes)
mia_add_test(concepts LINK_LIBRARIES Boost::boost units)
mia_add_test(units LINK_LIBRARIES range-v3 fmt::fmt-header-only units)
