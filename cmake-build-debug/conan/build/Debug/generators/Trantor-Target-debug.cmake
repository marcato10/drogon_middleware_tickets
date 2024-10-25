# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(trantor_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(trantor_FRAMEWORKS_FOUND_DEBUG "${trantor_FRAMEWORKS_DEBUG}" "${trantor_FRAMEWORK_DIRS_DEBUG}")

set(trantor_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET trantor_DEPS_TARGET)
    add_library(trantor_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET trantor_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${trantor_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${trantor_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:c-ares::cares;openssl::openssl>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### trantor_DEPS_TARGET to all of them
conan_package_library_targets("${trantor_LIBS_DEBUG}"    # libraries
                              "${trantor_LIB_DIRS_DEBUG}" # package_libdir
                              "${trantor_BIN_DIRS_DEBUG}" # package_bindir
                              "${trantor_LIBRARY_TYPE_DEBUG}"
                              "${trantor_IS_HOST_WINDOWS_DEBUG}"
                              trantor_DEPS_TARGET
                              trantor_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "trantor"    # package_name
                              "${trantor_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${trantor_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET Trantor::Trantor
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${trantor_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${trantor_LIBRARIES_TARGETS}>
                 )

    if("${trantor_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET Trantor::Trantor
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     trantor_DEPS_TARGET)
    endif()

    set_property(TARGET Trantor::Trantor
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${trantor_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET Trantor::Trantor
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${trantor_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET Trantor::Trantor
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${trantor_LIB_DIRS_DEBUG}>)
    set_property(TARGET Trantor::Trantor
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${trantor_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET Trantor::Trantor
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${trantor_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(trantor_LIBRARIES_DEBUG Trantor::Trantor)
