
# CMakeLists.txt  22

cmake_minimum_required(VERSION  3.0)
project(iha)

set(CMAKE_CXX_STANDARD   17)

set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(iha_kontrol STATIC  
    ${LIBRARY_DIR}/iha_kontrol.cpp
)

target_include_directories(iha_kontrol PUBLIC ${LIBRARY_DIR})
include_directories(/usr/include/mavsdk)

find_package(MAVSDK REQUIRED)
find_package(Threads REQUIRED) 

add_executable(iha src/iha.cpp)

target_link_libraries(iha_kontrol PUBLIC MAVSDK::mavsdk Threads::Threads  )

target_link_libraries(iha PUBLIC iha_kontrol Threads::Threads ) 


if(NOT MSVC)
    add_compile_options(offboard PRIVATE -Wall -Wextra)
else()
    add_compile_options(offboard PRIVATE -WX -W2)
endif()

if(MINGW OR MSVC)
    # For M_PI
    add_target_definitions(offboard "-D_USE_MATH_DEFINES")
endif()
