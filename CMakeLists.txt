##---------------------------------------------------------------------------
## Author:      nohal aka. Pavel Kalian
## Copyright:   
## License:     GPL License
##---------------------------------------------------------------------------
 
# define minimum cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.2)
# This should be 2.8.0 to have FindGTK2 module
IF (COMMAND cmake_policy)
  CMAKE_POLICY(SET CMP0003 OLD)
  CMAKE_POLICY(SET CMP0005 OLD)
  CMAKE_POLICY(SET CMP0011 OLD)
ENDIF (COMMAND cmake_policy)

PROJECT(wlev2harmonic)

#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(PACKAGE_NAME wlev2harmonic)

INCLUDE( ${CMAKE_SOURCE_DIR}/VERSION.cmake )
SET(PACKAGE_VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" )

#Red Hat:   /etc/redhat-release
#Slackware: /etc/slackware-version
#Slamd64:   /etc/slamd64-version
#Gentoo: /etc/gentoo-release
#Ubuntu: /etc/debian_version

# TODO: Should PREFIX be set as well?
# Based on code from nohal
IF (NOT WIN32)
  # default
  SET (ARCH "i386")
  SET (LIB_INSTALL_DIR "lib")
  IF (EXISTS /etc/debian_version)
    SET (PACKAGE_FORMAT "DEB")
    SET (PACKAGE_DEPS "libwxgtk2.8-0 (>= 2.8.7.1)")
    SET (LIB_INSTALL_DIR "lib")
    IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET (ARCH "amd64")
#      SET (LIB_INSTALL_DIR "lib64")
    ELSE (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET (ARCH "i386")
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")
  ENDIF (EXISTS /etc/debian_version)
  IF (EXISTS /etc/redhat-release)
    SET (PACKAGE_FORMAT "RPM")
    SET (PACKAGE_DEPS  "wxGTK gettext")
    IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET (ARCH "x86_64")
      SET (LIB_INSTALL_DIR "lib64")
    ELSE (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET (ARCH "i386")
      SET (LIB_INSTALL_DIR "lib")
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")
  ENDIF (EXISTS /etc/redhat-release)
  IF (EXISTS /etc/suse-release OR EXISTS /etc/SuSE-release)
    SET (PACKAGE_FORMAT "RPM")
    SET (PACKAGE_DEPS  "wxWidgets-wxcontainer")
    IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET (ARCH "x86_64")
      SET (LIB_INSTALL_DIR "lib64")
    ELSE (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET (ARCH "i386")
      SET (LIB_INSTALL_DIR "lib")
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")
  ENDIF (EXISTS /etc/suse-release OR EXISTS /etc/SuSE-release)
  IF(APPLE)
    IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
      SET(ARCH "x86_64")
    ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")
  ENDIF()
ELSE (NOT WIN32)
  # On WIN32 probably CMAKE_SIZEOF_VOID_P EQUAL 8, but we don't use it at all now...
  SET (ARCH "i386")
ENDIF (NOT WIN32)

IF (CMAKE_SYSTEM_PROCESSOR MATCHES "arm*")
  SET (ARCH "armel")
ENDIF (CMAKE_SYSTEM_PROCESSOR MATCHES "arm*")
MESSAGE (${ARCH})
SET(PACKAGE_RELEASE "1" CACHE STRING "Package release number")

MESSAGE (STATUS "*** Staging to build ${PACKAGE_NAME} ${PACKAGE_VERSION} ***")

SET(wxWidgets_USE_LIBS base core adv)

# Find wxWidgets here, and the setting get inherited by all plugins.
# These options can be used to set the linux widgets build type
SET( wxWidgets_USE_DEBUG OFF)
SET( wxWidgets_USE_UNICODE ON)
SET( wxWidgets_USE_UNIVERSAL OFF)
SET( wxWidgets_USE_STATIC OFF)

FIND_PACKAGE(wxWidgets REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

#  Search for wxWidgets 2.9
STRING(REGEX MATCHALL "2.9" wx_Version "${wxWidgets_INCLUDE_DIRS}")


MESSAGE (STATUS "")
MESSAGE (STATUS "*** Staging to build ${PACKAGE_NAME}  ***")

IF (PREFIX)
	SET(CMAKE_INSTALL_PREFIX ${PREFIX})
ENDIF (PREFIX)
SET(PREFIX_BIN bin)
SET(PREFIX_INCLUDE include)
SET(PREFIX_DATA share)
SET(PREFIX_PKGDATA ${PREFIX_DATA}/${PACKAGE_NAME})
SET(PREFIX_LIB "${CMAKE_INSTALL_PREFIX}/${LIB_INSTALL_DIR}")

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# require proper c++
#ADD_DEFINITIONS( "-Wall -ansi -pedantic -Wno-variadic-macros" )
#TODO: Should we use  -fno-stack-protector
#  IF NOT DEBUGGING CFLAGS="-O2 -march=native"
IF(NOT WIN32)
  ADD_DEFINITIONS( "-Wall -Wno-unused -fexceptions -rdynamic" )
  ADD_DEFINITIONS( " -g -fno-strict-aliasing")
ENDIF(NOT WIN32)

# Add some definitions to satisfy MS
IF(WIN32)
    ADD_DEFINITIONS(-D__MSVC__)
    ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_DEPRECATE)
    ADD_DEFINITIONS(-DPSAPI_VERSION=1)
ENDIF(WIN32)

# Add a definition to fix some 64 bit linux system builds, avoiding Apple builds
IF (NOT WIN32 AND NOT APPLE)
      IF (CMAKE_SIZEOF_VOID_P MATCHES "8")
            ADD_DEFINITIONS("`pkg-config --cflags --libs gtk+-2.0`")
      ENDIF (CMAKE_SIZEOF_VOID_P MATCHES "8")
ENDIF (NOT WIN32 AND NOT APPLE)


# Location where cmake first looks for cmake modules.
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/build)

# Let cmake find additional modules private to wlev2harmonic
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/")

FIND_PACKAGE(GTK2 2.6)
IF (GTK2_FOUND)
    MESSAGE (STATUS "Found GTK2")
    INCLUDE_DIRECTORIES(${GTK2_INCLUDE_DIRS})
    ADD_DEFINITIONS(-DocpnUSE_GTK_OPTIMIZE)
    SET(EXTRA_LIBS ${EXTRA_LIBS} ${GTK2_LIBRARIES})
ELSE(GTK2_FOUND)
    MESSAGE (STATUS "GTK2 Not found...")
ENDIF (GTK2_FOUND)

FIND_PACKAGE(Gettext REQUIRED)

# For convenience we define the sources as a variable. You can add 
# header files and cpp/c files and CMake will sort them out

SET(HDRS
                include/wlev2harmonic.h
)

SET(SRCS 
		src/wlev2harmonic.cpp
    )

SET(PACKAGE_HEADERS ""
)

# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
IF(WIN32)
  SET(SRCS ${SRCS} src/wlev2harmonic.rc)
ENDIF(WIN32)

IF(WIN32)
    IF(MSVC)
        SET(CMAKE_C_FLAGS_DEBUG               "/MDd /Ob0 /Od  /D_DEBUG  /Zi /RTC1" )
        SET(CMAKE_C_FLAGS_MINSIZEREL          "/MD  /O1  /Ob1 /D NDEBUG")
        SET(CMAKE_C_FLAGS_RELEASE             "/MD  /O2  /Ob2 /D NDEBUG")
        SET(CMAKE_C_FLAGS_RELWITHDEBINFO      "/MD  /O2  /Ob1 /D NDEBUG /Zi")
        SET(CMAKE_CXX_FLAGS_DEBUG             "/MDd /Ob0 /Od  /D_DEBUG  /Zi /RTC1")
        SET(CMAKE_CXX_FLAGS_MINSIZEREL        "/MD  /O1  /Ob1 /D NDEBUG")
        SET(CMAKE_CXX_FLAGS_RELEASE           "/MD  /O2  /Ob2 /D NDEBUG")
        SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO    "/MD  /O2  /Ob1 /D NDEBUG" /Zi )
    ENDIF(MSVC)
#    SET_TARGET_PROPERTIES(${PACKAGE_NAME} PROPERTIES COMPILE_FLAGS /Zp44)
#    SET_TARGET_PROPERTIES(${PACKAGE_NAME} PROPERTIES LINK_FLAGS /MANIFEST:NO)
ADD_EXECUTABLE(${PACKAGE_NAME} WIN32 ${HDRS} ${SRCS})
ENDIF(WIN32)

IF(UNIX AND NOT APPLE)
ADD_EXECUTABLE(${PACKAGE_NAME} ${HDRS} ${SRCS})
ENDIF(UNIX AND NOT APPLE)

If(NOT APPLE)
TARGET_LINK_LIBRARIES(${PACKAGE_NAME}
      ${wxWidgets_LIBRARIES}
      ${EXTRA_LIBS}
      )
ENDIF(NOT APPLE)

IF(WIN32)
TARGET_LINK_LIBRARIES(${PACKAGE_NAME}
	setupapi.lib
	gdiplus.lib
        Psapi.lib
)
ENDIF(WIN32)

IF(UNIX)
TARGET_LINK_LIBRARIES(${PACKAGE_NAME}
      ${GETTEXT_LIBRARY}
      )
ENDIF(UNIX)

#   Certain older Cmake FindGTK2 modules ( e.g. cmake-2.8.0-2) do not yield all of the required link libraries
#   So, add them manually.
IF(UNIX AND NOT APPLE)
TARGET_LINK_LIBRARIES(${PACKAGE_NAME}
      dl
      gobject-2.0
)
ENDIF(UNIX AND NOT APPLE)

IF(NOT APPLE)

IF(WIN32)
INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME DESTINATION ".")
ENDIF(WIN32)

IF(UNIX AND NOT APPLE)
INSTALL(TARGETS ${PACKAGE_NAME} RUNTIME DESTINATION ${PREFIX_BIN})
ENDIF(UNIX AND NOT APPLE)

IF(WIN32)
SET(PREFIX_PKGDATA ".")
ENDIF(WIN32)


IF(UNIX)
  INSTALL(FILES data/wlev2harmonic.png DESTINATION ${PREFIX_DATA}/icons/hicolor/48x48/apps )
  INSTALL(FILES src/bitmaps/other_svg_src/wlev2harmonic.svg DESTINATION ${PREFIX_DATA}/icons/hicolor/scalable/apps )
  INSTALL(FILES data/wlev2harmonic.desktop DESTINATION ${PREFIX_DATA}/applications )
ENDIF(UNIX)

ENDIF(NOT APPLE)

FIND_PROGRAM(GETTEXT_XGETTEXT_EXECUTABLE xgettext)
IF (GETTEXT_XGETTEXT_EXECUTABLE)

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot.dummy
   COMMAND ${GETTEXT_XGETTEXT_EXECUTABLE} --force-po --package-name=${PACKAGE_NAME} --package-version="${PACKAGE_VERSION}" --output=${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot  --keyword=_ --width=80 --files-from=${CMAKE_SOURCE_DIR}/po/POTFILES.in 
   DEPENDS ${CMAKE_SOURCE_DIR}/po/POTFILES.in ${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot
   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
   COMMENT "pot-update [${PACKAGE_NAME}]: Generated pot file."
)
ADD_CUSTOM_TARGET(pot-update COMMENT "pot-update: Done." DEPENDS ${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot.dummy)

ENDIF(GETTEXT_XGETTEXT_EXECUTABLE )

MACRO(GETTEXT_UPDATE_PO _potFile)
   SET(_poFiles ${_potFile})
   GET_FILENAME_COMPONENT(_absPotFile ${_potFile} ABSOLUTE)

   FOREACH (_currentPoFile ${ARGN})
      GET_FILENAME_COMPONENT(_absFile ${_currentPoFile} ABSOLUTE)
      GET_FILENAME_COMPONENT(_poBasename ${_absFile} NAME_WE)

      ADD_CUSTOM_COMMAND(
         OUTPUT ${_absFile}.dummy
         COMMAND ${GETTEXT_MSGMERGE_EXECUTABLE} --width=80 --strict --quiet --update --backup=none --no-location -s ${_absFile} ${_absPotFile}
         DEPENDS ${_absPotFile} ${_absFile}
         COMMENT "po-update [${_poBasename}]: Updated po file."
      )

      SET(_poFiles ${_poFiles} ${_absFile}.dummy)

   ENDFOREACH (_currentPoFile )

   ADD_CUSTOM_TARGET(po-update COMMENT "po-update: Done." DEPENDS ${_poFiles})
ENDMACRO(GETTEXT_UPDATE_PO)

IF (GETTEXT_MSGMERGE_EXECUTABLE)
FILE(GLOB PACKAGE_PO_FILES ${CMAKE_SOURCE_DIR}/po/*.po)
GETTEXT_UPDATE_PO(${CMAKE_SOURCE_DIR}/po/${PACKAGE_NAME}.pot ${PACKAGE_PO_FILES})
ENDIF(GETTEXT_MSGMERGE_EXECUTABLE)

SET(_gmoFiles)
MACRO(GETTEXT_BUILD_MO _poFile _lang)

   GET_FILENAME_COMPONENT(_absFile ${_poFile} ABSOLUTE)
   GET_FILENAME_COMPONENT(_poBasename ${_absFile} NAME_WE)
   SET(_gmoFile ${CMAKE_CURRENT_BINARY_DIR}/${_poBasename}.mo)

   ADD_CUSTOM_COMMAND(
      OUTPUT ${_gmoFile}
      COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} --check -o ${_gmoFile} ${_absFile}
      DEPENDS ${_absFile}
      COMMENT "i18n [${_poBasename}]: Created mo file."
   )
   INSTALL(FILES ${_gmoFile} DESTINATION ${PREFIX_DATA}/locale/${_lang}/LC_MESSAGES RENAME ${PACKAGE_NAME}.mo )

   SET(_gmoFiles ${_gmoFiles} ${_gmoFile})
ENDMACRO(GETTEXT_BUILD_MO)

if(GETTEXT_MSGFMT_EXECUTABLE)
GETTEXT_BUILD_MO(po/wlev2harmonic_cs_CZ.po cs)
ADD_CUSTOM_TARGET(i18n COMMENT "i18n: Done." DEPENDS ${_gmoFiles})
ADD_DEPENDENCIES(${PACKAGE_NAME} i18n)
ENDIF(GETTEXT_MSGFMT_EXECUTABLE)

# On Windows builds, copy the wxWidgets dlls and  to the executable directory
IF(WIN32 AND NOT UNIX)
INSTALL(DIRECTORY wxWidgets/ DESTINATION "." )
INSTALL(DIRECTORY buildwin/vc10/ DESTINATION ".\\\\vc10" )
ENDIF(WIN32 AND NOT UNIX)

MESSAGE (STATUS "")

# build a CPack driven installer package
#include (InstallRequiredSystemLibraries)
SET(CPACK_PACKAGE_NAME "wlev2harmonic")
SET(CPACK_PACKAGE_VENDOR "github.com/nohal/wlev2harmonic")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "wlev2harmonic ${PACKAGE_VERSION}")
SET(CPACK_PACKAGE_VERSION ${PACKAGE_VERSION})
SET(CPACK_PACKAGE_VERSION_MAJOR ${VERSION_MAJOR})
SET(CPACK_PACKAGE_VERSION_MINOR ${VERSION_MINOR})
SET(CPACK_PACKAGE_VERSION_PATCH ${VERSION_PATCH})
SET(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_CURRENT_BINARY_DIR};${PACKAGE_NAME};ALL;/")
SET(CPACK_PACKAGE_EXECUTABLES ${PACKAGE_NAME} "wlev2harmonic")



IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.

  SET(CPACK_NSIS_INSTALLED_ICON_NAME "wlev2harmonic.exe")
  SET(CPACK_NSIS_PACKAGE_NAME_LC "wlev2harmonic")

#  These lines set the name of the Windows Start Menu shortcut and the icon that goes with it
##  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_NAME} ${PACKAGE_VERSION}")
  SET(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/src/bitmaps\\\\wlev2harmonic.ico")

  SET(CPACK_PACKAGE_FILE_NAME "${PACKAGE_NAME}_${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}_setup" )
  
  SET(CPACK_BUILDWIN_DIR "${CMAKE_SOURCE_DIR}/buildwin")  #Gunther
  
# Install the VC100 Redistributable
  SET(vc10_redist "vcredist_x86.exe")

    STRING( REPLACE "/" "\\\\" Temp_vc10_redist ${vc10_redist} )
    GET_FILENAME_COMPONENT( VC10_FILE_NAME ${vc10_redist} NAME )
    SET( CPACK_NSIS_EXTRA_INSTALL_COMMANDS ${CPACK_NSIS_EXTRA_INSTALL_COMMANDS}
      "ExecWait '\\\"$INSTDIR\\\\vc10\\\\${VC10_FILE_NAME}\\\" /q /norestart' $0\\n"
      " Remove folder\\n  RMDir /r \\\"$INSTDIR\\\\vc10\\\"\\n\\n" )


ELSE(WIN32 AND NOT UNIX)
  SET(CPACK_PACKAGE_INSTALL_DIRECTORY ${PACKAGE_NAME})
  SET(CPACK_STRIP_FILES "wlev2harmonic.exe")
  SET(CPACK_SOURCE_STRIP_FILES "")
  SET(CPACK_PACKAGE_FILE_NAME "${PACKAGE_NAME}_${PACKAGE_VERSION}-${PACKAGE_RELEASE}_${ARCH}" )

ENDIF(WIN32 AND NOT UNIX)

SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/data/license.txt")
IF (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/README")
    SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README")
    SET(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README")
ENDIF ()
SET(CPACK_SOURCE_GENERATOR "TGZ")

# The following components are regex's to match anywhere (unless anchored)
# in absolute path + filename to find files or directories to be excluded
# from source tarball.
set(CPACK_SOURCE_IGNORE_FILES
"\\\\.cvsignore$"
"^${CMAKE_CURRENT_SOURCE_DIR}.*/CVS/"
"^${CMAKE_CURRENT_SOURCE_DIR}/build*"
"^${CPACK_PACKAGE_INSTALL_DIRECTORY}/*"
)

IF(UNIX AND NOT APPLE)
    SET(CPACK_GENERATOR ${PACKAGE_FORMAT})
    SET(CPACK_PACKAGE_CONTACT "Pavel Kalian <pavel@kalian.cz>")
    SET(CPACK_DEBIAN_PACKAGE_DEPENDS ${PACKAGE_DEPS})
    SET(CPACK_DEBIAN_PACKAGE_RECOMMENDS ${PACKAGE_RECS})
    SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE ${ARCH})
    SET(CPACK_DEBIAN_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}")
    SET(CPACK_DEBIAN_PACKAGE_SECTION "Miscellaneous")
    SET(CPACK_RPM_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}")
    SET(CPACK_RPM_PACKAGE_ARCHITECTURE  ${ARCH})
    SET(CPACK_RPM_PACKAGE_REQUIRES  ${PACKAGE_DEPS})
    SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Utility to help creating the harmonic constats file")
    SET(CPACK_PACKAGE_DESCRIPTION "wlev2harmonic is a utility to help creating the harmonic constats file.")
    SET(CPACK_SET_DESTDIR ON)
    SET(CPACK_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

ENDIF(UNIX AND NOT APPLE)

IF(WIN32 AND NOT UNIX)
 configure_file(${CMAKE_SOURCE_DIR}/src/wlev2harmonic.rc.in ${CMAKE_SOURCE_DIR}/src/wlev2harmonic.rc)
ENDIF(WIN32 AND NOT UNIX)

configure_file(version.h.in ${CMAKE_SOURCE_DIR}/include/version.h) #Gunther

# this dummy target is necessary to make sure the ADDITIONAL_MAKE_CLEAN_FILES directive is executed.
# apparently, the base CMakeLists.txt file must have "some" target to activate all the clean steps.
ADD_CUSTOM_TARGET(dummy COMMENT "dummy: Done." DEPENDS ${PACKAGE_NAME})

SET_DIRECTORY_PROPERTIES(dummy ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_SOURCE_DIR}/include/version.h)

INCLUDE(CPack)

MESSAGE(STATUS "Writing spec file...") 	  	 
