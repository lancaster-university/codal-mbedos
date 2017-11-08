project(codal-mbedos)

include("${CODAL_UTILS_LOCATION}")

# find sources and headers
RECURSIVE_FIND_DIR(TOP_LEVEL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" "*.h")
RECURSIVE_FIND_DIR(INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/${CODAL_OUTPUT_NAME}/inc" "*.h")

RECURSIVE_FIND_FILE(TOP_LEVEL_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/source" "*.c??")
RECURSIVE_FIND_FILE(OBJECT_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${CODAL_OUTPUT_NAME}/lib" "*.o")
RECURSIVE_FIND_FILE(ARCHIVE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${CODAL_OUTPUT_NAME}/lib" "*.a")

# add them
include_directories(${TOP_LEVEL_INCLUDE_DIRS} ${INCLUDE_DIRS})

# create our target
add_library(codal-mbedos ${TOP_LEVEL_SOURCE})

target_link_libraries(codal-mbedos codal-core ${OBJECT_FILES} ${ARCHIVE_FILES})

#set_target_properties(codal-mbedos PROPERTIES LINKER_LANGUAGE CXX)

# expose it to parent cmake.
target_include_directories(codal-mbedos PUBLIC ${TOP_LEVEL_INCLUDE_DIRS} ${INCLUDE_DIRS})
