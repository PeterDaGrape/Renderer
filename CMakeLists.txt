cmake_minimum_required(VERSION 3.5)
project(Renderer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")
set(CMAKE_OSX_ARCHITECTURES "arm64")
set(CMAKE_CXX_STANDARD 17)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -gdwarf-2")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -g")

find_program(DSYMUTIL_PROGRAM dsymutil)
if (DSYMUTIL_PROGRAM)
  foreach(lang C CXX)
    foreach(var LINK_EXECUTABLE CREATE_SHARED_LIBRARY)
      set(CMAKE_${lang}_${var} "${CMAKE_${lang}_${var}}" "${DSYMUTIL_PROGRAM} <TARGET>")
    endforeach()
  endforeach()
endif()



# packages used
find_package(SDL2 REQUIRED)

find_program(XXD xxd)
include(metal)

add_subdirectory(external/metal-cpp)
add_subdirectory(external/sdl2gui)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")
#add_compiled_metal_sources()

add_executable(Renderer 
    src/main.cpp
    ${SOURCES}
)

#add_executable(Tests tests/test_maths.cpp external/catch_amalgamated.cpp ${SOURCES})

set_target_properties(Renderer PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "@loader_path/../Frameworks;/Library/Frameworks"
)


#set_target_properties(Tests PROPERTIES
#    BUILD_WITH_INSTALL_RPATH TRUE
#    INSTALL_RPATH "@loader_path/../Frameworks;/Library/Frameworks"
#)


set(PROJECT_INCLUDE_DIRS
    "${CMAKE_CURRENT_BINARY_DIR}"
    "${SDL2_INCLUDE_DIRS}"
    "${CMAKE_SOURCE_DIR}/external"
    "${CMAKE_SOURCE_DIR}/external/sdl2gui"
    "${CMAKE_SOURCE_DIR}/external/metal-cpp"
    "${INCLUDE_DIR}"
    "${INCLUDE_DIR}/scene"
    "${INCLUDE_DIR}/engine"
    "${INCLUDE_DIR}/engine/backend"
    "${INCLUDE_DIR}/engine/backend/cpu"
)
target_include_directories(
    Renderer
    PRIVATE 
    ${PROJECT_INCLUDE_DIRS}
)

#target_include_directories(
#    Tests 
#    PRIVATE 
#    ${PROJECT_INCLUDE_DIRS})


#target_link_libraries(
#    Tests
#    PRIVATE "${SDL2_LIBRARIES}" 
#)

target_link_libraries(
    Renderer
    PRIVATE "${SDL2_LIBRARIES}" 
    MetalCPP 
    imgui
    "-framework Metal" 
    "-framework QuartzCore" 
    "-framework Foundation"
)

