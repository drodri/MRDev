PROJECT(ariaServer)

IF(WIN32)
	INCLUDE_DIRECTORIES(C:/usr/include/mrcore) 
	LINK_DIRECTORIES(C:/usr/lib)
ELSE(WIN32)
	INCLUDE_DIRECTORIES(/usr/local/mrcore/include /usr/local/mrcore/include/mrcore /usr/local/Aria/include)
	LINK_DIRECTORIES(/usr/local/mrcore/lib /usr/local/Aria/lib)
ENDIF(WIN32)

ADD_EXECUTABLE(ariaRobotServer ariarobotserver.cpp ariabase.cpp )

### AT THE END, ONLY THE FOLLOWING SHOULD REMAIN
#MR_ADD_EXECUTABLE(ariaRobotServer AUTO)

### Diego dice:
### NO, DE ESO NADA. Esto tiene una dependencia explicita a Aria, que casi nadie va a tener.
### Este proyecto se compila a parte, como cada uno de los HWServers, no estan pensados para ser compilados
### Con todo el MRDev, y por tanto las Macros como MR_ADD_EXECUTABLE no son deseables

IF(WIN32)
	TARGET_LINK_LIBRARIES(ariaRobotServer mrcore Aria)
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(ariaRobotServer mrcore Aria pthread rt GL GLU)

ENDIF(WIN32)

		


