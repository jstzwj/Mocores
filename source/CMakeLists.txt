# contrib folders

# octoon folder
INCLUDE_DIRECTORIES(${OCTOON_PATH_INCLUDE})

# lib folder for link
LINK_DIRECTORIES(${OCTOON_LIBRARY_OUTPUT_PATH})

# runtime libraries
# ADD_SUBDIRECTORY(octoon-math)


# framework
ADD_SUBDIRECTORY(mocores-common)