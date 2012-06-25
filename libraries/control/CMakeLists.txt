ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ADD_LIBRARY(control STATIC  controlmanager.cpp
				controlreactive.cpp
				controltrajectory.cpp
				)



##################################
##   INSTALL LOCALIZER
##################################
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/control)
INSTALL(TARGETS control DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)			
		




