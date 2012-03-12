
ADD_EXECUTABLE(worldTest worldtest.cpp)
IF(WIN32)	
	TARGET_LINK_LIBRARIES(worldTest debug mrcore_d freeglut objects)
	TARGET_LINK_LIBRARIES(worldTest optimized mrcore freeglut objects)
ELSE(WIN32) #LINUX		
	TARGET_LINK_LIBRARIES(worldtest mrcore ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
ENDIF(WIN32)
		
	

