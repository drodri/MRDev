PROJECT(MRDev)
cmake_minimum_required(VERSION 2.8)

########### Find MRCore
IF (WIN32)
	SET(CMAKE_INSTALL_PREFIX "C:/mrcore" CACHE PATH "FOO install prefix" FORCE)
ELSE(WIN32)
	SET(CMAKE_INSTALL_PREFIX /usr/local/mrcore) 
ENDIF(WIN32)
MESSAGE(STATUS "Default install directory is: " ${CMAKE_INSTALL_PREFIX}) 

find_path(	MRCORE_DIR include/mrcore/mrcore.h  ${CMAKE_INSTALL_PREFIX} )

INCLUDE_DIRECTORIES(${MRCORE_DIR}/include)
LINK_DIRECTORIES(${MRCORE_DIR}/lib)

ADD_SUBDIRECTORY(libraries)

####################################################################
#	SET INCLUDES FOR APPS AND TESTS
####################################################################
SET(curdir ${CMAKE_CURRENT_SOURCE_DIR}/libraries)
FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
FOREACH(child ${children})
IF(IS_DIRECTORY ${curdir}/${child})
    INCLUDE_DIRECTORIES( ${curdir}/${child} )
ENDIF()
ENDFOREACH()

ADD_SUBDIRECTORY(apps)
ADD_SUBDIRECTORY(tests) #somthing to play, but not to install for everybody

####################################################################################################
#
#			INSTALL
#
####################################################################################################








