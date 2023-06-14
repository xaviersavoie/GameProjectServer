project(GameProjectServer LANGUAGES CXX)

if(${CMAKE_VERSION} VERSION_GREATER_EQUAL "3.11.0")
    file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)
    #file(GLOB_RECURSE INCLUDE_FILES CONFIGURE_DEPENDS src/include/*.h src/include/*.hpp)
    #file(GLOB_RECURSE LIBRARY_FILES CONFIGURE_DEPENDS src/libs/*.cpp)
else()
    file(GLOB SOURCE_FILES src/*.cpp src/*.hpp)
    #file(GLOB INCLUDE_FILES src/include/*.h src/include/*.hpp)
    #file(GLOB LIBRARY_FILES src/libs/*.cpp)
endif()

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)

add_definitions(-D BOOST_ASIO_HAS_STD_CHRONO)

message(${CMAKE_CURRENT_SOURCE_DIR})


SET(Boost_INCLUDE_DIR /home/runner/work/GameProjectServer/GameProjectServer/boost/boost/include/)

find_package(Boost COMPONENTS chrono json system thread REQUIRED)


# Typically you don't care so much for a third party library's tests to be
# run from your own project's code.
set(JSON_BuildTests OFF CACHE INTERNAL "")

# If you only include this third party in PRIVATE source files, you do not
# need to install it when your main project gets installed.
# set(JSON_Install OFF CACHE INTERNAL "")

# Don't use include(nlohmann_json/CMakeLists.txt) since that carries with it
# unintended consequences that will break the build.  It's generally
# discouraged (although not necessarily well documented as such) to use
# include(...) for pulling in other CMake projects anyways.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/nlohmann_json)


find_library(yajl_LIBRARIES yajl)
message(STATUS "yajl:" ${yajl_LIBRARIES})

find_path(yajl_INCLUDE_DIR
  NAMES yajl/yajl_common.h
)
message(STATUS "yajl include dir:" ${yajl_INCLUDE_DIR})

add_executable(Main ${SOURCE_FILES} ${LIBRARY_FILES} )

set_property(TARGET Main PROPERTY CXX_STANDARD 17)

target_include_directories(Main PUBLIC ${Boost_INCLUDE_DIR})
target_include_directories(Main PRIVATE ${Boost_LIB_DIR})

target_include_directories(Main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/libs)

target_include_directories(Main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_include_directories(Main PUBLIC ${yajl_INCLUDE_DIR})

target_link_libraries(Main Boost::json Boost::system Boost::thread Boost::chrono)
target_link_libraries(Main ${yajl_LIBRARIES})

target_link_libraries(Main PRIVATE nlohmann_json::nlohmann_json)
