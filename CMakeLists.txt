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


####################################################################################################
#
#	Each library must handle its owns includes to other libraries in this MRDev, as well
#	as defining which headers to install.
#
####################################################################################################
ADD_SUBDIRECTORY(libraries)

####################################################################################################
#
#	It is normal than APPs and TESTS in this MRDev use the libraries in this MRDev, so we set
#	the include directories by default for all libraries
#
####################################################################################################
SET(curdir ${CMAKE_CURRENT_SOURCE_DIR}/libraries)
FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
FOREACH(child ${children})
IF(IS_DIRECTORY ${curdir}/${child})
    INCLUDE_DIRECTORIES( ${curdir}/${child} )
    INCLUDE_DIRECTORIES( ${curdir}/${child}/include )
ENDIF()
ENDFOREACH()

ADD_SUBDIRECTORY(apps)
ADD_SUBDIRECTORY(tests) #somthing to play, but not to install for everybody

####################################################################################################
#
#			INSTALL (TODO: Data)
#
####################################################################################################

FILE(GLOB datafiles "${CMAKE_CURRENT_SOURCE_DIR}/data/*")
INSTALL(FILES ${datafiles} DESTINATION "${CMAKE_INSTALL_PREFIX}/data")






