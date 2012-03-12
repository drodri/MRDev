#SOURCES SELECTION


    
SET(curdir ${CMAKE_CURRENT_SOURCE_DIR})

##
### Iterate over children, creating LIBRARIES
##

FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
FOREACH(child ${children})
IF(IS_DIRECTORY ${curdir}/${child})
    ADD_SUBDIRECTORY( ${child} )
ENDIF()
ENDFOREACH()


