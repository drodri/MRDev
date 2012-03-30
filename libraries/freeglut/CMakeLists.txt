IF (WIN32)	
AUX_SOURCE_DIRECTORY( src freeglut_sources ) 
 
ADD_DEFINITIONS(-DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS)
INCLUDE_DIRECTORIES(include)
ADD_LIBRARY(freeglut_static STATIC  ${freeglut_sources})

##################################
##   INSTALL FREEGLUT
##################################

FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/include/GL/*.h")
INSTALL(FILES ${files} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/GL)
INSTALL(TARGETS freeglut_static DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)		

ENDIF(WIN32)	
		




