cmake_minimum_required(VERSION 3.20)
project(frediff C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor/cjson)

add_executable(log
  src/log.c
  src/diff.c
  src/ses.c
  src/find_middle.c
)

target_link_libraries(log PRIVATE cjson)
target_include_directories(log PRIVATE vendor/cjson)

if(EMSCRIPTEN)
    add_executable(diff_wasm
        src/diff.c
        src/ses.c
        src/find_middle.c
    )
    
    target_link_libraries(diff_wasm PRIVATE cjson)

    target_include_directories(diff_wasm PRIVATE vendor/cjson)

    set_target_properties(diff_wasm PROPERTIES
        LINK_FLAGS "-s WASM=1 -s MODULARIZE=1 -s EXPORT_NAME='DiffModule' -s EXPORTED_FUNCTIONS='[\"_diff\",\"_ses\",\"_find_middle\"]' -s EXPORTED_RUNTIME_METHODS='[\"ccall\",\"cwrap\"]'"
    )
endif()
