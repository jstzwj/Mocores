# contrib folders

# mocores folder
INCLUDE_DIRECTORIES(${MOCORES_PATH_INCLUDE})

# lib folder for link
LINK_DIRECTORIES(${MOCORES_LIBRARY_OUTPUT_PATH})

# runtime libraries
# ADD_SUBDIRECTORY(mocores-math)


# framework
ADD_SUBDIRECTORY(mocores-common)
ADD_SUBDIRECTORY(mocores-cluster)
ADD_SUBDIRECTORY(mocores-client)
ADD_SUBDIRECTORY(mocores-net)