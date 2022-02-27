cmake_minimum_required(VERSION 3.0.0)
project(search_engine VERSION 0.1.0)

include(CTest)
enable_testing()

set(BUILD_CPR_TESTS OFF)
set(CMAKE_USE_OPENSSL OFF)
set(CPR_ENABLE_SSL OFF)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git GIT_TAG beb9e98806bb84bcc130a2cebfbcbbc6ce62b335) # The commit hash for 1.7.2. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)


add_executable(${PROJECT_NAME} 
        main.cpp
        src/httptools.cpp
        gumbo-parser/src/attribute.c
        gumbo-parser/src/char_ref.c
        gumbo-parser/src/error.c
        gumbo-parser/src/parser.c
        gumbo-parser/src/string_buffer.c
        gumbo-parser/src/string_piece.c
        gumbo-parser/src/tag.c
        gumbo-parser/src/tokenizer.c
        gumbo-parser/src/utf8.c
        gumbo-parser/src/util.c
        gumbo-parser/src/vector.c


)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
