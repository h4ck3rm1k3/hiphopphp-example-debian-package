#
#   +----------------------------------------------------------------------+
#   | HipHop for PHP                                                       |
#   +----------------------------------------------------------------------+
#   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
#   | Copyright (c) 1997-2010 The PHP Group                                |
#   +----------------------------------------------------------------------+
#   | This source file is subject to version 3.01 of the PHP license,      |
#   | that is bundled with this package in the file LICENSE, and is        |
#   | available through the world-wide-web at the following url:           |
#   | http://www.php.net/license/3_01.txt                                  |
#   | If you did not receive a copy of the PHP license and are unable to   |
#   | obtain it through the world-wide-web, please send a note to          |
#   | license@php.net so we can mail you a copy immediately.               |
#   +----------------------------------------------------------------------+
#

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4 FATAL_ERROR)
PROJECT(hphp C CXX)

SET(ENV{HPHP_HOME} "/usr/src/hiphop-php-0.1/")
IF("$ENV{HPHP_HOME}" STREQUAL "")
        message(FATAL_ERROR "You should set the HPHP_HOME environmental")
ENDIF()

file(TO_CMAKE_PATH "$ENV{HPHP_HOME}" HPHP_HOME)

IF(NOT IS_DIRECTORY ${HPHP_HOME})
	message(FATAL_ERROR "The value of HPHP_HOME does not exist")
ENDIF()

IF(NOT EXISTS "${HPHP_HOME}/LICENSE.PHP")
	message(FATAL_ERROR "The value of HPHP_HOME in incorrect")
ENDIF()

SET(CMAKE_MODULE_PATH "${HPHP_HOME}/CMake" ${CMAKE_MODULE_PATH})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# the hphp includes from the debian packaging
include_directories("/usr/include/hphp")
include_directories("/usr/include/hphp/system/gen")


include(HPHPFunctions)
include(CheckFunctionExists)
include(HPHPSetup)

if ("${PROGRAM_NAME}" STREQUAL "")
	set(PROGRAM_NAME helloworld-hphp)
endif()

auto_sources(SOURCES "*.cpp" "RECURSE" "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${PROGRAM_NAME} ${SOURCES})

foreach (SOURCE_FILE ${SOURCES})
	if(${SOURCE_FILE} MATCHES ".no.cpp$")
		SET_SOURCE_FILES_PROPERTIES(
			${SOURCE_FILE}
			PROPERTIES
			COMPILE_FLAGS -O0
		)
	endif()
endforeach()

add_library(libhphp_runtime STATIC IMPORTED)
SET_PROPERTY(TARGET libhphp_runtime PROPERTY IMPORTED_LOCATION "${HPHP_HOME}/bin/libhphp_runtime.a")

add_library(timelib STATIC IMPORTED)
SET_PROPERTY(TARGET timelib PROPERTY IMPORTED_LOCATION "${HPHP_HOME}/bin/libtimelib.a")

add_library(sqlite3 STATIC IMPORTED)
SET_PROPERTY(TARGET sqlite3 PROPERTY IMPORTED_LOCATION "${HPHP_HOME}/bin/libsqlite3.a")

if (NOT SKIP_BUNDLED_XHP)
	add_library(xhp STATIC IMPORTED)
	SET_PROPERTY(TARGET xhp PROPERTY IMPORTED_LOCATION "${HPHP_HOME}/bin/libxhp.a")
endif()

add_library(afdt STATIC IMPORTED)
SET_PROPERTY(TARGET afdt PROPERTY IMPORTED_LOCATION "${HPHP_HOME}/bin/libafdt.a")

add_library(mbfl STATIC IMPORTED)
SET_PROPERTY(TARGET mbfl PROPERTY IMPORTED_LOCATION "${HPHP_HOME}/bin/libmbfl.a")

target_link_libraries(${PROGRAM_NAME} libhphp_runtime)

hphp_link(${PROGRAM_NAME})

#CMAKE_INSTALL_PREFIX
SET(CMAKE_INSTALL_PREFIX "/usr/")

INSTALL(TARGETS ${PROGRAM_NAME}
        RUNTIME
        DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
