cmake_minimum_required( VERSION 3.7 )

project( SuperHeroesGame )

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

# On MacOS clang complains if this is not set
set (CMAKE_CXX_STANDARD 11)

add_subdirectory(src)
add_subdirectory(headers)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})