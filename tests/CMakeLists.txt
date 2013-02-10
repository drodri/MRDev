IF(WIN32)	
ADD_DEFINITIONS(-DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS)
ENDIF(WIN32)

#ADD_EXECUTABLE(worldTest worldTest.cpp worlds/euitiworld.cpp worlds/building.cpp worlds/disamworld.cpp worlds/feria.cpp)
ADD_EXECUTABLE(worldTest worldTest.cpp worlds/euitiworld.cpp worlds/building.cpp worlds/disamworld.cpp worlds/feria.cpp)
ADD_EXECUTABLE(mainPlanner main_planner.cpp)

IF(WIN32)	
	TARGET_LINK_LIBRARIES(worldTest debug mrcore_d  freeglut_static)
	TARGET_LINK_LIBRARIES(worldTest optimized mrcore freeglut_static)
	TARGET_LINK_LIBRARIES(mainPlanner debug mrcore_d freeglut_static)
	TARGET_LINK_LIBRARIES(mainPlanner mrcore freeglut_static)
ELSE(WIN32) #LINUX		
	#TARGET_LINK_LIBRARIES(localizerTest mrcore localizer glut GL GLU )
	TARGET_LINK_LIBRARIES(worldTest mrcore glut GL GLU )
	TARGET_LINK_LIBRARIES(mainPlanner mrcore glut GL GLU)
ENDIF(WIN32)
		
	

