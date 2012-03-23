ADD_LIBRARY(localizer STATIC  particle.cpp
			      localizer.cpp
				gaussian.cpp
				)



##################################
##   INSTALL LOCALIZER
##################################
FILE(GLOB files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
INSTALL(FILES ${files} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/localizer)
INSTALL(TARGETS localizer DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)			
		




