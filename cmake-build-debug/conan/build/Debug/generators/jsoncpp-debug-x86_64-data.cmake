########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(jsoncpp_COMPONENT_NAMES "")
if(DEFINED jsoncpp_FIND_DEPENDENCY_NAMES)
  list(APPEND jsoncpp_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES jsoncpp_FIND_DEPENDENCY_NAMES)
else()
  set(jsoncpp_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(jsoncpp_PACKAGE_FOLDER_DEBUG "/home/marcato/.conan2/p/b/jsoncb4ef9394e2de5/p")
set(jsoncpp_BUILD_MODULES_PATHS_DEBUG )


set(jsoncpp_INCLUDE_DIRS_DEBUG "${jsoncpp_PACKAGE_FOLDER_DEBUG}/include")
set(jsoncpp_RES_DIRS_DEBUG )
set(jsoncpp_DEFINITIONS_DEBUG )
set(jsoncpp_SHARED_LINK_FLAGS_DEBUG )
set(jsoncpp_EXE_LINK_FLAGS_DEBUG )
set(jsoncpp_OBJECTS_DEBUG )
set(jsoncpp_COMPILE_DEFINITIONS_DEBUG )
set(jsoncpp_COMPILE_OPTIONS_C_DEBUG )
set(jsoncpp_COMPILE_OPTIONS_CXX_DEBUG )
set(jsoncpp_LIB_DIRS_DEBUG "${jsoncpp_PACKAGE_FOLDER_DEBUG}/lib")
set(jsoncpp_BIN_DIRS_DEBUG )
set(jsoncpp_LIBRARY_TYPE_DEBUG STATIC)
set(jsoncpp_IS_HOST_WINDOWS_DEBUG 0)
set(jsoncpp_LIBS_DEBUG jsoncpp)
set(jsoncpp_SYSTEM_LIBS_DEBUG m)
set(jsoncpp_FRAMEWORK_DIRS_DEBUG )
set(jsoncpp_FRAMEWORKS_DEBUG )
set(jsoncpp_BUILD_DIRS_DEBUG )
set(jsoncpp_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(jsoncpp_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${jsoncpp_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${jsoncpp_COMPILE_OPTIONS_C_DEBUG}>")
set(jsoncpp_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${jsoncpp_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${jsoncpp_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${jsoncpp_EXE_LINK_FLAGS_DEBUG}>")


set(jsoncpp_COMPONENTS_DEBUG )