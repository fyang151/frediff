# CMake generated Testfile for 
# Source directory: /home/fyang151/cdiff/vendor/cjson
# Build directory: /home/fyang151/cdiff/build_wasm/vendor/cjson
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/home/fyang151/cdiff/build_wasm/vendor/cjson/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/home/fyang151/cdiff/vendor/cjson/CMakeLists.txt;248;add_test;/home/fyang151/cdiff/vendor/cjson/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
