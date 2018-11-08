include(FindBoost)
find_package(Boost 1.61.0 REQUIRED)

FetchContent_Declare(fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_SHALLOW True)

FetchContent_GetProperties(fmt)
if(NOT fmt_POPULATED)
    find_package(fmt 5.1.0 QUIET)
    if(NOT fmt_FOUND)
        FetchContent_Populate(fmt)
        add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
    endif()
endif()
