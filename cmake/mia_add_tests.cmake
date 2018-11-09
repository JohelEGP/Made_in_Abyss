if(NOT BUILD_TESTING)
    return()
endif()

include(mia_find_tests_dependencies)

# ```
# mia_add_test(<name>
#   [SOURCE source]
#   [COMPILE_OPTIONS options...]
#   [LINK_LIBRARIES libraries...])
# ```
# Adds the executable test target `mia_test_${name}`.
# `SOURCE` specifies the its source file in `test/`. Defaults to `${name}.cpp`.
# `COMPILE_OPTIONS` specifies its `PRIVATE` compile options.
# `LINK_LIBRARIES` specifies its `PRIVATE` link libraries besides `mia::mia`.
function(mia_add_test name)
    cmake_parse_arguments(PARSE_ARGV 0 ADD_TEST
        "" "SOURCE" "COMPILE_OPTIONS;LINK_LIBRARIES")

    list(APPEND ADD_TEST_SOURCE ${name}.cpp)
    list(GET ADD_TEST_SOURCE 0 source)

    add_executable(mia_test_${name} test/${source})
    target_compile_options(mia_test_${name} PRIVATE ${ADD_TEST_COMPILE_OPTIONS})
    target_link_libraries(mia_test_${name}
        PRIVATE ${ADD_TEST_LINK_LIBRARIES} mia::mia)
    add_test(mia_test_${name} mia_test_${name})
endfunction()

macro(mia_add_concepts_test step)
    mia_add_test(concepts${step}
        SOURCE concepts.cpp
        COMPILE_OPTIONS -DMIA_TEST_STEP=${step}
        LINK_LIBRARIES Boost::boost units)
endmacro()

mia_add_test(include_ext_std_chrono)
mia_add_test(include_concepts)
mia_add_test(include_units)
mia_add_test(all_includes)
mia_add_concepts_test(0)
mia_add_concepts_test(1)
mia_add_concepts_test(2)
mia_add_concepts_test(3)
mia_add_test(units LINK_LIBRARIES range-v3 fmt::fmt-header-only units)
