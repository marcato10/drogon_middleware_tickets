set(PACKAGE_VERSION "2.39.2")

if(PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)
    set(PACKAGE_VERSION_COMPATIBLE FALSE)
else()
    if("2.39.2" MATCHES "^([0-9]+)\\.")
        set(CVF_VERSION_MAJOR ${CMAKE_MATCH_1})
    else()
        set(CVF_VERSION_MAJOR "2.39.2")
    endif()

    if(PACKAGE_FIND_VERSION_MAJOR STREQUAL CVF_VERSION_MAJOR)
        set(PACKAGE_VERSION_COMPATIBLE TRUE)
    else()
        set(PACKAGE_VERSION_COMPATIBLE FALSE)
    endif()

    if(PACKAGE_FIND_VERSION STREQUAL PACKAGE_VERSION)
        set(PACKAGE_VERSION_EXACT TRUE)
    endif()
endif()