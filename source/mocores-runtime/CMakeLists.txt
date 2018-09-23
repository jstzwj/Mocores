SET(LIB_NAME runtime)
SET(LIB_OUTNAME mocores-${LIB_NAME})

SET(HEADER_PATH ${MOCORES_PATH_HEADER}/${LIB_NAME})
SET(SOURCE_PATH ${MOCORES_PATH_SOURCE}/${LIB_OUTNAME})

SET(MOCORES_LIST
	${HEADER_PATH}/scheduler/worker_pool.h
	${HEADER_PATH}/scheduler/worker.h
	${SOURCE_PATH}/scheduler/worker.cpp
	${HEADER_PATH}/scheduler/actor.h
	${SOURCE_PATH}/scheduler/actor.cpp
	${HEADER_PATH}/scheduler/task_scheduler.h
	${HEADER_PATH}/scheduler/work_item.h
	${SOURCE_PATH}/scheduler/work_item.cpp
	${HEADER_PATH}/config/config.h
	${HEADER_PATH}/config/config_node.h
	${HEADER_PATH}/config/config_client.h
	${HEADER_PATH}/util/platform_info.h
	${HEADER_PATH}/id/node_id.h
	${SOURCE_PATH}/id/node_id.cpp
	${HEADER_PATH}/platform.h
)
# SOURCE_GROUP("system\\runtime" FILES ${MOCORES_LIST})

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

IF(MOCORES_BUILD_SHARED_DLL)
	ADD_DEFINITIONS(-DMOCORES_BUILD_DLL_EXPORT)
	ADD_LIBRARY(${LIB_OUTNAME} SHARED 
		${MOCORES_LIST} 
	)
ELSE()
	ADD_DEFINITIONS(-DMOCORES_STATIC)
	ADD_LIBRARY(${LIB_OUTNAME} 
		${MOCORES_LIST}
	)
ENDIF()

# TARGET_LINK_LIBRARIES(${LIB_NAME} PUBLIC octoon-math)