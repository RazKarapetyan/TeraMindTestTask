cmake_minimum_required(VERSION 3.5)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_HEADERS
        command_line_utils/CommandLineUtils.cpp
)

set(PROJECT_SOURCES 
        main.cpp
        command_line_utils/CommandLineUtils.cpp
)

add_executable(TeraMindTestTask
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
)

find_package(Boost COMPONENTS program_options filesystem REQUIRED)
include_directories( ${Boost_INCLUDE_DIR} )

target_include_directories(TeraMindTestTask PUBLIC ${CMAKE_SOURCE_DIR}/stdafx)

target_link_libraries(TeraMindTestTask LINK_PUBLIC ${Boost_LIBRARIES} stdafx)

target_precompile_headers(TeraMindTestTask REUSE_FROM stdafx)
