
ADD_DEFINITIONS(-DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS)
ADD_EXECUTABLE(simulator simulator.cpp glutapp.cpp)
ADD_EXECUTABLE(teleop teleop.cpp glutapp.cpp)

IF(WIN32)
	TARGET_LINK_LIBRARIES(simulator debug mrcore_d freeglut_static)
	TARGET_LINK_LIBRARIES(teleop debug mrcore_d freeglut_static)
	TARGET_LINK_LIBRARIES(simulator optimized mrcore freeglut_static)
	TARGET_LINK_LIBRARIES(teleop optimized mrcore freeglut_static)
ELSE(WIN32) #LINUX	
	TARGET_LINK_LIBRARIES(simulator mrcore ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
ENDIF(WIN32)
		
##################################
##   INSTALL MY APPS
##################################
INSTALL(TARGETS simulator teleop DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)



