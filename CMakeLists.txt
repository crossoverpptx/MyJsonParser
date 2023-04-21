cmake_minimum_required(VERSION 3.0.0)
project(cppjson VERSION 0.1.0)

# The default include directory
include_directories(./)

# home directory source
aux_source_directory(. ROOT_SOURCE)

# sub directory source
add_subdirectory(json)

# build executable file
add_executable(main ${ROOT_SOURCE} ${PARSER_SRC})
