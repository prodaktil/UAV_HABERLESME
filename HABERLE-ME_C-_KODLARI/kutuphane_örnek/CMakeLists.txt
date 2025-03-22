# CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(myproject)

# Kütüphane dizini
set(LIBRARY_DIR ${CMAKE_SOURCE_DIR}/mylibrary)

# Kütüphane dosyalarını ekleyin
add_library(mylibrary STATIC ${LIBRARY_DIR}/mylibrary.cpp)

# Include dizinlerini belirleyin
target_include_directories(mylibrary PUBLIC ${LIBRARY_DIR})

# Kullanılacak hedefleri ekleyin ve kütüphane bağımlılığını belirtin
add_executable(myexecutable main.cpp)
target_link_libraries(myexecutable PRIVATE mylibrary)

