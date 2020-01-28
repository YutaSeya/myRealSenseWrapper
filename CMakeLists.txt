# cmake needs this line
cmake_minimum_required(VERSION 3.1.0)

project(my_realsense_wrapper)

# set flag
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Winit-self -Wno-missing-field-initializers -o1")

# Create Main project
# Create Main project
set(SOURCES
    main.cpp
    realSensseWrapper.cpp
)

set(HEADERS
    # main.h
    realSensseWrapper.h
)

add_executable(Main
    ${SOURCES}
    ${HEADERS}
)


# For OpenCV
find_package(OpenCV REQUIRED)
# For Realsense
find_package(realsense2 REQUIRED)

# make project
if(OpenCV_FOUND)
    target_include_directories(Main PUBLIC 
                              ${OpenCV_INCLUDE_DIRS}
                              ${realsense2_INCLUDE_DIR})
    target_link_libraries(Main 
                          ${OpenCV_LIBS}
                          ${realsense2_LIBRARY})
endif(OpenCV_FOUND)