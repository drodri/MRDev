

IF(WIN32)
	INCLUDE_DIRECTORIES(C:/usr/include/mrcore) 
	LINK_DIRECTORIES(C:/usr/lib)
ELSE(WIN32)
	INCLUDE_DIRECTORIES(/usr/local/include/mrcore )
	LINK_DIRECTORIES(/usr/local/lib)
ENDIF(WIN32)

ADD_EXECUTABLE(voicetts voicetts.cpp)
ADD_EXECUTABLE(voiceclient voiceclient.cpp)

IF(WIN32)
	TARGET_LINK_LIBRARIES(voicetts espeak)
ELSE(WIN32)
	#TARGET_LINK_LIBRARIES(ariaRobotServer mrcore Aria pthread rt)
	TARGET_LINK_LIBRARIES(voicetts espeak mrcore)
	TARGET_LINK_LIBRARIES(voiceclient mrcore)
ENDIF(WIN32)
