cmake_minimum_required(VERSION 2.8)

include_directories(/Users/mise/Documents/github/repository/c_libraries)
include_directories(/Users/mise/Documents/github/repository/json_parser)
add_executable(test
    test.c
    json_number.h
    json_number.c
    json_string.h
    json_string.c
    json_value.h
    json_value.c
    json_array.h
    json_array.c
    json_keyandvalue.h
    json_keyandvalue.c
    json_object.h
    json_object.c
    json_common.h
    json_common.c
    ../c_libraries/iobuffer/iobuffer.h
    ../c_libraries/iobuffer/iobuffer.c
)