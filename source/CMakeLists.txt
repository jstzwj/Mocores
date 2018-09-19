# contrib folders
<<<<<<< HEAD
INCLUDE_DIRECTORIES(${MOCORES_PATH_DEPENDENCIES}/zlib)

# mocores folder
INCLUDE_DIRECTORIES(${MOCORES_PATH_INCLUDE})

# lib folder for link
LINK_DIRECTORIES(${MOCORES_LIBRARY_OUTPUT_PATH})

OPTION(MOCORES_FEATURE_BASE_ENABLE "On for enable off for disable" ON)

IF(MOCORES_FEATURE_BASE_ENABLE)
	ADD_DEFINITIONS(-DMOCORES_FEATURE_BASE_ENABLE)
ENDIF()

# framework
ADD_SUBDIRECTORY(mocores-common)
ADD_SUBDIRECTORY(mocores-masternode)
ADD_SUBDIRECTORY(mocores-workernode)
=======

# octoon folder
INCLUDE_DIRECTORIES(${OCTOON_PATH_INCLUDE})

# lib folder for link
LINK_DIRECTORIES(${OCTOON_LIBRARY_OUTPUT_PATH})

# runtime libraries
# ADD_SUBDIRECTORY(octoon-math)


# framework
ADD_SUBDIRECTORY(mocores-common)
>>>>>>> python
