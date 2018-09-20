SET(LIB_NAME net)
SET(LIB_OUTNAME mocores-${LIB_NAME})

SET(HEADER_PATH ${MOCORES_PATH_HEADER}/${LIB_NAME})
SET(SOURCE_PATH ${MOCORES_PATH_SOURCE}/${LIB_OUTNAME})

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET(MOCORES_LIST
	${HEADER_PATH}/protocol/message.h
	${HEADER_PATH}/protocol/pingpong.h
	${HEADER_PATH}/service_server.h
	${SOURCE_PATH}/service_server.cpp
	${HEADER_PATH}/service_session.h
	${SOURCE_PATH}/service_session.cpp
	${HEADER_PATH}/service_client.h
	${SOURCE_PATH}/service_client.cpp
)
#SOURCE_GROUP("system\\core" FILES ${MOCORES_LIST})

ADD_LIBRARY(${LIB_OUTNAME} ${MOCORES_LIST})

target_link_libraries(${LIB_OUTNAME} ${Boost_LIBRARIES})
