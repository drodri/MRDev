#SOURCES SELECTION
PROJECT(MRDev)
cmake_minimum_required(VERSION 2.8)

########### Find MRCore
IF (WIN32)
	SET(CMAKE_INSTALL_PREFIX "C:/mrcore" CACHE PATH "FOO install prefix" FORCE)
ELSE(WIN32)
	SET(CMAKE_INSTALL_PREFIX /usr/local/mrcore) 
ENDIF(WIN32)
MESSAGE(STATUS "Default install directory is: " ${CMAKE_INSTALL_PREFIX}) 


find_path(	MRCORE_DIR include/mrcore/mrcore.h
				${CMAKE_INSTALL_PREFIX}
				)

ADD_SUBDIRECTORY(libraries)
ADD_SUBDIRECTORY(apps)

	
####################################################################################################
#
#			INSTALL
#
####################################################################################################








