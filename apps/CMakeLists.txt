

ADD_EXECUTABLE(simulator simulator.cpp glutapp.cpp)
ADD_EXECUTABLE(teleop teleop.cpp glutapp.cpp)

IF(WIN32)
	TARGET_LINK_LIBRARIES(simulator debug mrcore_d freeglut)
	TARGET_LINK_LIBRARIES(teleop debug mrcore_d freeglut)
	TARGET_LINK_LIBRARIES(simulator optimized mrcore freeglut)
	TARGET_LINK_LIBRARIES(teleop optimized mrcore freeglut)
ELSE(WIN32) #LINUX	
	TARGET_LINK_LIBRARIES(simulator mrcore ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
ENDIF(WIN32)
		




