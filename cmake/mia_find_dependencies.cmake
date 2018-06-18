include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY https://github.com/Microsoft/GSL.git
    GIT_SHALLOW True)
FetchContent_Declare(range-v3
    GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
    GIT_SHALLOW True)
FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_SHALLOW True)
FetchContent_Declare(units
    GIT_REPOSITORY https://github.com/johelegp/units.git
    GIT_TAG sfinae
    GIT_SHALLOW True)

FetchContent_GetProperties(GSL)
if(NOT gsl_POPULATED)
    FetchContent_Populate(GSL)
    add_subdirectory(${gsl_SOURCE_DIR} ${gsl_BINARY_DIR})
endif()

find_package(range-v3 0.3.6 QUIET)
if(NOT range-v3_FOUND)
    FetchContent_GetProperties(range-v3)
    if(NOT range-v3_POPULATED)
        FetchContent_Populate(range-v3)
        add_subdirectory(${range-v3_SOURCE_DIR} ${range-v3_BINARY_DIR})
    endif()
endif()

find_package(fmt 5.1.0 QUIET)
if(NOT fmt_FOUND)
    FetchContent_GetProperties(fmt)
    if(NOT fmt_POPULATED)
        FetchContent_Populate(fmt)
        add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
    endif()
endif()

FetchContent_GetProperties(units)
if(NOT units_POPULATED)
    FetchContent_Populate(units)
    add_subdirectory(${units_SOURCE_DIR} ${units_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
