CMAKE_MINIMUM_REQUIRED(VERSION 3.1.0)
PROJECT(php-spellcheck-ext)

INCLUDE(GNUInstallDirs)

SET(CMAKE_CXX_STANDARD 11)

OPTION(
    INSTALL_INI
    "Decides if this should install the extension .ini file while installing this extension."
    ON
)

OPTION(
    ENABLE_HUNSPELL
    "Decides if libhunspell should be used as a backend."
    ON
)

OPTION(
    ENABLE_VOIKKO
    "Decides if libvoikko (Finnish) should be used as a backend."
    OFF
)

IF(INSTALL_INI)
    SET(INI_FILE "php-spellcheck-ext.ini")
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
    "src/php-spellcheck-ext/*.cpp"
    "src/module.cpp"
)

FILE(
    GLOB
    HEADERS
    "include/php-spellcheck-ext/*.hpp"
)

INCLUDE_DIRECTORIES("include")

ADD_LIBRARY(
    php-spellcheck-ext
    SHARED
    "${SOURCES}"
)

TARGET_COMPILE_OPTIONS(
    php-spellcheck-ext
    PRIVATE
    -Wall -O2 -fpic
)

TARGET_LINK_LIBRARIES(
    php-spellcheck-ext
    PRIVATE
    phpcpp
)

IF(ENABLE_HUNSPELL)
    MESSAGE("-- libhunpell will be enabled.")

    ADD_DEFINITIONS(-DENABLE_HUNSPELL)

    TARGET_LINK_LIBRARIES(
        php-spellcheck-ext
        PRIVATE
        hunspell-1.7
    )
ENDIF()

IF(ENABLE_VOIKKO)
    MESSAGE("-- libvoikko will be enabled.")

    ADD_DEFINITIONS(-DENABLE_VOIKKO)

    TARGET_LINK_LIBRARIES(
        php-spellcheck-ext
        PRIVATE
        voikko
    )
ENDIF()

SET_TARGET_PROPERTIES(
    php-spellcheck-ext
    PROPERTIES
    PREFIX ""
)

INSTALL(
    TARGETS
    php-spellcheck-ext
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