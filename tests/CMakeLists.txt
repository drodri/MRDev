IF(WIN32)	
ADD_DEFINITIONS(-DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

ADD_EXECUTABLE(worldTest worldTest.cpp)
ADD_EXECUTABLE(localizerTest testlocalizer.cpp glutapp.cpp)

IF(WIN32)	
	TARGET_LINK_LIBRARIES(localizerTest debug mrcore_d localizer freeglut_static)
	TARGET_LINK_LIBRARIES(localizerTest optimized mrcore localizer freeglut_static)
	TARGET_LINK_LIBRARIES(worldTest debug mrcore_d objects freeglut_static)
	TARGET_LINK_LIBRARIES(worldTest optimized mrcore objects freeglut_static)
ELSE(WIN32) #LINUX		
	TARGET_LINK_LIBRARIES(localizerTest mrcore localizer ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
	TARGET_LINK_LIBRARIES(worldTest mrcore objects ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} )
ENDIF(WIN32)
		
	

