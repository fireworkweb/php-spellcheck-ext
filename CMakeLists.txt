CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
PROJECT(hunspell-ext)

INCLUDE(GNUInstallDirs)

SET(CMAKE_CXX_STANDARD 11)

OPTION(
    INSTALL_INI
    "Decides if this should install the extension .ini file while installing this extension."
    ON
)

IF(INSTALL_INI)
    SET(INI_FILE "hunspell-ext.ini")
    SET(
        INI_DIR
        "/etc/php/7.0/mods-available"
        CACHE
        STRING
        "Folder where PHP modules .ini files are store (check you PHP version)."
    )

    MESSAGE("-- INI_DIR set to ${INI_DIR}")
ELSE()
    MESSAGE("-- INSTALL_INI is set to OFF, this will not install this extesion .ini file.")
ENDIF()


EXECUTE_PROCESS(
    COMMAND 
    php-config --extension-dir
    OUTPUT_VARIABLE EXTENSION_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

FILE(
    GLOB
    SOURCES
    "src/*.cpp"
)

FILE(
    GLOB
    HEADERS
    "include/*.hpp"
)

INCLUDE_DIRECTORIES("include")

ADD_LIBRARY(
    hunspell-ext
    SHARED
    "${SOURCES}"
)

TARGET_COMPILE_OPTIONS(
    hunspell-ext
    PRIVATE
    -Wall -O2 -fpic
)

TARGET_LINK_LIBRARIES(
    hunspell-ext
    PRIVATE
    phpcpp
    hunspell-1.6
)

SET_TARGET_PROPERTIES(
    hunspell-ext
    PROPERTIES
    PREFIX ""
)

TARGET_INCLUDE_DIRECTORIES(
    hunspell-ext 
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

INSTALL(
    TARGETS
    hunspell-ext
    LIBRARY
    DESTINATION "${EXTENSION_DIR}"
)

IF(INSTALL_INI)
    INSTALL(
        FILES
        "${INI_FILE}"
        DESTINATION "${INI_DIR}"
    )
ENDIF()

INSTALL(
    DIRECTORY "include/"
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)