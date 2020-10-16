
if(DEFINED GANDIVA_FOUND)
    return()
endif()

set(find_package_arguments)
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION)
    list(APPEND find_package_arguments "${${CMAKE_FIND_PACKAGE_NAME}_FIND_VERSION}")
endif()
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_REQUIRED)
    list(APPEND find_package_arguments REQUIRED)
endif()
if(${CMAKE_FIND_PACKAGE_NAME}_FIND_QUIETLY)
    list(APPEND find_package_arguments QUIET)
endif()
find_package(Arrow ${find_package_arguments})

if(ARROW_FOUND)
    arrow_find_package(GANDIVA
            "${ARROW_HOME}"
            gandiva
            gandiva/arrow.h
            Gandiva
            gandiva)
    if(NOT GANDIVA_VERSION)
        set(GANDIVA_VERSION "${ARROW_VERSION}")
    endif()
    set(GANDIVA_ABI_VERSION "${ARROW_ABI_VERSION}")
    set(GANDIVA_SO_VERSION "${ARROW_SO_VERSION}")
endif()

if("${GANDIVA_VERSION}" VERSION_EQUAL "${ARROW_VERSION}")
    set(GANDIVA_VERSION_MATCH TRUE)
else()
    set(GANDIVA_VERSION_MATCH FALSE)
endif()

mark_as_advanced(GANDIVA_ABI_VERSION
        GANDIVA_IMPORT_LIB
        GANDIVA_INCLUDE_DIR
        GANDIVA_LIBS
        GANDIVA_LIB_DIR
        GANDIVA_SHARED_IMP_LIB
        GANDIVA_SHARED_LIB
        GANDIVA_SO_VERSION
        GANDIVA_STATIC_LIB
        GANDIVA_VERSION
        GANDIVA_VERSION_MATCH)

find_package_handle_standard_args(Gandiva
        REQUIRED_VARS
        GANDIVA_INCLUDE_DIR
        GANDIVA_LIB_DIR
        GANDIVA_SO_VERSION
        GANDIVA_VERSION_MATCH
        VERSION_VAR
        GANDIVA_VERSION)
set(GANDIVA_FOUND ${Gandiva_FOUND})

if(Gandiva_FOUND AND NOT Gandiva_FIND_QUIETLY)
    message(STATUS "Found the Gandiva by ${GANDIVA_FIND_APPROACH}")
    message(STATUS "Found the Gandiva shared library: ${GANDIVA_SHARED_LIB}")
    message(STATUS "Found the Gandiva import library: ${GANDIVA_IMPORT_LIB}")
    message(STATUS "Found the Gandiva static library: ${GANDIVA_STATIC_LIB}")
endif()