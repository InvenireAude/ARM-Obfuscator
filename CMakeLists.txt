cmake_minimum_required(VERSION 3.10)

project(armob VERSION 2.0)

configure_file(src/armob/config.h.in src/armob/config.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(tools OBJECT
  src/tools/common.cpp
  src/tools/Exception.cpp
  src/tools/ValueMap.cpp  
)

add_library(elf OBJECT
    src/elf/Identification.cpp
    src/elf/Image.cpp
    src/elf/Printer.cpp
    src/elf/Specification.cpp

    src/elf/impl/Component.cpp

    src/elf/utils/Converter.cpp
    src/elf/utils/Helper.cpp

    # src/elf/elf32/Printer.cpp
    # src/elf/elf32/Header.cpp
    # src/elf/elf32/Section.cpp
    # src/elf/elf32/Segment.cpp
    # src/elf/elf32/Symbol.cpp
    # src/elf/elf32/SymbolTable.cpp
)

add_executable(armob src/main.cpp)

target_link_libraries(armob PRIVATE elf tools)

#target_link_libraries(armob)

target_include_directories(elf PRIVATE src)
target_include_directories(elf PUBLIC ${PROJECT_BINARY_DIR}/src)


target_include_directories(armob PRIVATE src)
target_include_directories(armob PUBLIC ${PROJECT_BINARY_DIR}/src)

