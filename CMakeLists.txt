cmake_minimum_required(VERSION 3.20)
project(badiff C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT EMSCRIPTEN)
    add_executable(log
        src/log.c
        src/diff.c
        src/ses.c
        src/find_middle.c
    )
endif()

if(EMSCRIPTEN)
    add_executable(diff_wasm
        src/diff.c
        src/ses.c
        src/find_middle.c
    )

    set_target_properties(diff_wasm PROPERTIES
        OUTPUT_NAME "diff"
        SUFFIX ".js"
    )

    target_link_options(diff_wasm PRIVATE
        "-sMODULARIZE=1"
        "-sEXPORT_ES6=1"
        "-sENVIRONMENT=web"
        "-sEXPORTED_FUNCTIONS=['_diff','_malloc','_free']"
        "-sEXPORTED_RUNTIME_METHODS=['stringToUTF8','lengthBytesUTF8','HEAP32']"
    )
endif()
