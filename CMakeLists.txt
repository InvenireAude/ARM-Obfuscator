cmake_minimum_required(VERSION 3.10)

project(armob VERSION 2.0)

configure_file(src/armob/config.h.in src/armob/config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CMakeLists.ARMOB-Asm.files.txt)
include(CMakeLists.ARMOB-Armob.files.txt)
include(CMakeLists.ARMOB-Elf.files.txt)
include(CMakeLists.ARMOB-Tools.files.txt)

add_executable(armob src/main.cpp)
add_executable(armob_mutate src/main_mutate.cpp)
add_executable(armob_elf_inspector src/main_elf_inspector.cpp)

target_link_libraries(armob PRIVATE ARMOB-Armob ARMOB-Asm ARMOB-Elf ARMOB-Tools)
target_link_libraries(armob_mutate PRIVATE ARMOB-Armob ARMOB-Asm ARMOB-Elf ARMOB-Tools)
target_link_libraries(armob_elf_inspector PRIVATE ARMOB-Elf ARMOB-Tools)

#target_link_libraries(armob)

target_include_directories(ARMOB-Armob PRIVATE src)
target_include_directories(ARMOB-Armob PUBLIC ${PROJECT_BINARY_DIR}/src)

target_include_directories(ARMOB-Asm PRIVATE src)
target_include_directories(ARMOB-Asm PUBLIC ${PROJECT_BINARY_DIR}/src)

target_include_directories(ARMOB-Elf PRIVATE src)
target_include_directories(ARMOB-Elf PUBLIC ${PROJECT_BINARY_DIR}/src)

target_include_directories(ARMOB-Tools PRIVATE src)
target_include_directories(ARMOB-Tools PUBLIC ${PROJECT_BINARY_DIR}/src)

target_include_directories(armob PRIVATE src)
target_include_directories(armob PUBLIC ${PROJECT_BINARY_DIR}/src)

target_include_directories(armob_mutate PRIVATE src)
target_include_directories(armob_mutate PUBLIC ${PROJECT_BINARY_DIR}/src)

target_include_directories(armob_elf_inspector PRIVATE src)
target_include_directories(armob_elf_inspector PUBLIC ${PROJECT_BINARY_DIR}/src)

install(TARGETS armob DESTINATION bin)
install(TARGETS armob_mutate DESTINATION bin)
install(TARGETS armob_elf_inspector DESTINATION bin)

#add_subdirectory(../ARM-Helpers ../ARM-Helpers/Debug) 
