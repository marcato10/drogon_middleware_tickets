# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(jsoncpp_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(jsoncpp_FRAMEWORKS_FOUND_DEBUG "${jsoncpp_FRAMEWORKS_DEBUG}" "${jsoncpp_FRAMEWORK_DIRS_DEBUG}")

set(jsoncpp_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET jsoncpp_DEPS_TARGET)
    add_library(jsoncpp_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET jsoncpp_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${jsoncpp_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${jsoncpp_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### jsoncpp_DEPS_TARGET to all of them
conan_package_library_targets("${jsoncpp_LIBS_DEBUG}"    # libraries
                              "${jsoncpp_LIB_DIRS_DEBUG}" # package_libdir
                              "${jsoncpp_BIN_DIRS_DEBUG}" # package_bindir
                              "${jsoncpp_LIBRARY_TYPE_DEBUG}"
                              "${jsoncpp_IS_HOST_WINDOWS_DEBUG}"
                              jsoncpp_DEPS_TARGET
                              jsoncpp_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "jsoncpp"    # package_name
                              "${jsoncpp_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${jsoncpp_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET JsonCpp::JsonCpp
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${jsoncpp_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${jsoncpp_LIBRARIES_TARGETS}>
                 )

    if("${jsoncpp_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET JsonCpp::JsonCpp
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     jsoncpp_DEPS_TARGET)
    endif()

    set_property(TARGET JsonCpp::JsonCpp
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${jsoncpp_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET JsonCpp::JsonCpp
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${jsoncpp_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET JsonCpp::JsonCpp
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${jsoncpp_LIB_DIRS_DEBUG}>)
    set_property(TARGET JsonCpp::JsonCpp
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${jsoncpp_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET JsonCpp::JsonCpp
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${jsoncpp_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(jsoncpp_LIBRARIES_DEBUG JsonCpp::JsonCpp)