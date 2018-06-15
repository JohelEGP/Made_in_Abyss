include(FetchContent)

find_package(range-v3 0.3.6 QUIET)
if(NOT range-v3_FOUND)
    FetchContent_Declare(range-v3
        GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
        GIT_SHALLOW True)
    FetchContent_GetProperties(range-v3)
    if(NOT range-v3_POPULATED)
        FetchContent_Populate(range-v3)
        add_subdirectory(${range-v3_SOURCE_DIR} ${range-v3_BINARY_DIR})
    endif()
endif()

FetchContent_Declare(units
    GIT_REPOSITORY https://github.com/johelegp/units.git
    GIT_TAG sfinae
    GIT_SHALLOW True)
FetchContent_GetProperties(units)
if(NOT units_POPULATED)
    FetchContent_Populate(units)
    add_subdirectory(${units_SOURCE_DIR} ${units_BINARY_DIR})
endif()
