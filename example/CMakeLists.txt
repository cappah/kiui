project(toyui_example)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../src/toyui/Context/Glfw/*.cpp"
                       example.cpp 
                       UiExample.cpp)
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/../src/toyui/Context/Glfw/*.h"
                       UiExampleConfig.h
                       UiExample.h)

add_definitions("-DUIEXAMPLE_EXPORT")
    
if (WIN32)
    add_definitions(-DTOYUI_EXAMPLE_RESOURCE_PATH="${CMAKE_INSTALL_PREFIX}/data/")
else ()
    add_definitions(-DTOYUI_EXAMPLE_RESOURCE_PATH="${CMAKE_INSTALL_PREFIX}/kiui/data/")
endif ()


option(TOYUI_EXAMPLE_LIB "Build toyui example as shared library" ${TOYUI_FORCE_EXAMPLE_LIB})
if (TOYUI_EXAMPLE_LIB)
    add_library(toyui_example SHARED ${SOURCE_FILES} ${HEADER_FILES})
else ()
    add_executable(toyui_example ${SOURCE_FILES} ${HEADER_FILES})
endif ()

include_directories(${TOYOBJ_INCLUDE_DIR})
include_directories(${TOYUI_INCLUDE_DIR})
include_directories(${GLFW_INCLUDE_DIR})

target_link_libraries(toyui_example toyui)
target_link_libraries(toyui_example ${GLFW_LIBRARIES})


set(${PROJECT_NAME_UPPER}_INCLUDE_DIR ${PROJECT_SOURCE_DIR}
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)
    
if (WIN32)
    install(TARGETS toyui_example INCLUDES DESTINATION include ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
else ()
    install(TARGETS toyui_example LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)
endif ()
