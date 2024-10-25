########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(util-linux-libuuid_COMPONENT_NAMES "")
if(DEFINED util-linux-libuuid_FIND_DEPENDENCY_NAMES)
  list(APPEND util-linux-libuuid_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES util-linux-libuuid_FIND_DEPENDENCY_NAMES)
else()
  set(util-linux-libuuid_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(util-linux-libuuid_PACKAGE_FOLDER_RELEASE "/home/marcato/.conan2/p/b/util-24c0cf7ecb80e/p")
set(util-linux-libuuid_BUILD_MODULES_PATHS_RELEASE )


set(util-linux-libuuid_INCLUDE_DIRS_RELEASE )
set(util-linux-libuuid_RES_DIRS_RELEASE )
set(util-linux-libuuid_DEFINITIONS_RELEASE )
set(util-linux-libuuid_SHARED_LINK_FLAGS_RELEASE )
set(util-linux-libuuid_EXE_LINK_FLAGS_RELEASE )
set(util-linux-libuuid_OBJECTS_RELEASE )
set(util-linux-libuuid_COMPILE_DEFINITIONS_RELEASE )
set(util-linux-libuuid_COMPILE_OPTIONS_C_RELEASE )
set(util-linux-libuuid_COMPILE_OPTIONS_CXX_RELEASE )
set(util-linux-libuuid_LIB_DIRS_RELEASE "${util-linux-libuuid_PACKAGE_FOLDER_RELEASE}/lib")
set(util-linux-libuuid_BIN_DIRS_RELEASE )
set(util-linux-libuuid_LIBRARY_TYPE_RELEASE STATIC)
set(util-linux-libuuid_IS_HOST_WINDOWS_RELEASE 0)
set(util-linux-libuuid_LIBS_RELEASE uuid)
set(util-linux-libuuid_SYSTEM_LIBS_RELEASE )
set(util-linux-libuuid_FRAMEWORK_DIRS_RELEASE )
set(util-linux-libuuid_FRAMEWORKS_RELEASE )
set(util-linux-libuuid_BUILD_DIRS_RELEASE )
set(util-linux-libuuid_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(util-linux-libuuid_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${util-linux-libuuid_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${util-linux-libuuid_COMPILE_OPTIONS_C_RELEASE}>")
set(util-linux-libuuid_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${util-linux-libuuid_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${util-linux-libuuid_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${util-linux-libuuid_EXE_LINK_FLAGS_RELEASE}>")


set(util-linux-libuuid_COMPONENTS_RELEASE )