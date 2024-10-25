########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(libuuid_FIND_QUIETLY)
    set(libuuid_MESSAGE_MODE VERBOSE)
else()
    set(libuuid_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/libuuidTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${util-linux-libuuid_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(libuuid_VERSION_STRING "2.39.2")
set(libuuid_INCLUDE_DIRS ${util-linux-libuuid_INCLUDE_DIRS_RELEASE} )
set(libuuid_INCLUDE_DIR ${util-linux-libuuid_INCLUDE_DIRS_RELEASE} )
set(libuuid_LIBRARIES ${util-linux-libuuid_LIBRARIES_RELEASE} )
set(libuuid_DEFINITIONS ${util-linux-libuuid_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${util-linux-libuuid_BUILD_MODULES_PATHS_RELEASE} )
    message(${libuuid_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


