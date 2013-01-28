

IF(WIN32)
	INCLUDE_DIRECTORIES(C:/mrcore/include) 
	LINK_DIRECTORIES(C:/mrcore/lib)
ELSE(WIN32)
	INCLUDE_DIRECTORIES(/usr/local/mrcore/include /usr/local/mrcore/include/mrcore /usr/local/Aria/include)
	LINK_DIRECTORIES(/usr/local/mrcore/lib /usr/local/Aria/lib)
ENDIF(WIN32)

ADD_EXECUTABLE(voicetts voicetts.cpp)
ADD_EXECUTABLE(voiceclient voiceclient.cpp)

IF(WIN32)
	TARGET_LINK_LIBRARIES(voicetts espeak)
	TARGET_LINK_LIBRARIES(voiceclient mrcore)
ELSE(WIN32)
	#TARGET_LINK_LIBRARIES(ariaRobotServer mrcore Aria pthread rt)
	TARGET_LINK_LIBRARIES(voicetts espeak mrcore)
	TARGET_LINK_LIBRARIES(voiceclient mrcore)
ENDIF(WIN32)
