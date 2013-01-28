
ADD_DEFINITIONS(-DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS)
ADD_EXECUTABLE(simulator simulator.cpp mrcoreglutapp.cpp glutapp.cpp)
ADD_EXECUTABLE(robapp	 robotmanagerapp.cpp mrcoreglutapp.cpp glutapp.cpp mobilerobotmanager.cpp)

IF(WIN32)
	TARGET_LINK_LIBRARIES(simulator debug mrcore_d freeglut_static)
	TARGET_LINK_LIBRARIES(simulator optimized mrcore freeglut_static)
	TARGET_LINK_LIBRARIES(robapp debug 	mrcore_d 	localizer 	control		freeglut_static)
	TARGET_LINK_LIBRARIES(robapp optimized 	mrcore 		localizer 	control		freeglut_static)
ELSE(WIN32) #LINUX	
	TARGET_LINK_LIBRARIES(simulator mrcore glut GL GLU )
ENDIF(WIN32)
		
##################################
##   INSTALL MY APPS
##################################
INSTALL(TARGETS simulator robapp DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)



