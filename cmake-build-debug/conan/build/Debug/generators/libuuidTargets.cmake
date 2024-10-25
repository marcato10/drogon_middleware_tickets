# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/libuuid-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${util-linux-libuuid_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${libuuid_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET libuuid::libuuid)
    add_library(libuuid::libuuid INTERFACE IMPORTED)
    message(${libuuid_MESSAGE_MODE} "Conan: Target declared 'libuuid::libuuid'")
endif()
if(NOT TARGET LibUUID::LibUUID)
    add_library(LibUUID::LibUUID INTERFACE IMPORTED)
    set_property(TARGET LibUUID::LibUUID PROPERTY INTERFACE_LINK_LIBRARIES libuuid::libuuid)
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/libuuid-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()