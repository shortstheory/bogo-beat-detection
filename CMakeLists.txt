cmake_minimum_required(VERSION 3.5)
project(fft-visualiser)
set(CMAKE_BUILD_TYPE Release)

# Define sources and executable
set(EXECUTABLE_NAME "visualiser")
add_executable(${EXECUTABLE_NAME} visualiser.cpp)
target_compile_features(visualiser PRIVATE cxx_auto_type)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.0 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# next target
#set(EXECUTABLE_NAME "fft")
#add_executable(${EXECUTABLE_NAME} fft.cpp)
#find_package(fftw3)
#target_link_libraries(${EXECUTABLE_NAME} )
# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
