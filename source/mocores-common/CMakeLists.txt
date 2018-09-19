SET(LIB_NAME mocores-common)

SET(HEADER_PATH ${MOCORES_PATH_HEADER})
SET(SOURCE_PATH ${MOCORES_PATH_SOURCE}/${LIB_NAME})

SET(MOCORES_LIST
	${SOURCE_PATH}/game_app.cpp
	${HEADER_PATH}/game_app.h
	${SOURCE_PATH}/game_listener.cpp
	${HEADER_PATH}/game_listener.h
	${SOURCE_PATH}/game_object.cpp
	${HEADER_PATH}/game_object.h
	${SOURCE_PATH}/game_object_manager.cpp
	${HEADER_PATH}/game_object_manager.h
	${SOURCE_PATH}/game_component.cpp
	${HEADER_PATH}/game_component.h
	${SOURCE_PATH}/game_feature.cpp
	${HEADER_PATH}/game_feature.h
	${SOURCE_PATH}/game_server.cpp
	${HEADER_PATH}/game_server.h
	${SOURCE_PATH}/game_scene.cpp
	${HEADER_PATH}/game_scene.h
	${SOURCE_PATH}/game_scene_manager.cpp
	${HEADER_PATH}/game_scene_manager.h
	${HEADER_PATH}/game_types.h
)
SOURCE_GROUP("system\\common" FILES ${MOCORES_LIST})

IF(MOCORES_BUILD_SHARED_DLL)
	ADD_DEFINITIONS(-DMOCORES_BUILD_DLL_EXPORT)
	ADD_LIBRARY(${LIB_NAME} SHARED 
		${MOCORES_LIST} 
	)
ELSE()
	ADD_DEFINITIONS(-DMOCORES_STATIC)
	ADD_LIBRARY(${LIB_NAME} 
		${MOCORES_LIST}
	)
ENDIF()

#TARGET_LINK_LIBRARIES(${LIB_NAME} PUBLIC octoon-math)

SET_TARGET_ATTRIBUTE(${LIB_NAME} "mocores")