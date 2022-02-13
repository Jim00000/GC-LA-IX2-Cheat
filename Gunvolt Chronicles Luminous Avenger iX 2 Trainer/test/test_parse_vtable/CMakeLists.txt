set(TEST_PARSE_VTABLE_BIN test_parse_vt)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${TEST_PARSE_VTABLE_BIN} Entry.cpp)

target_link_libraries(${TEST_PARSE_VTABLE_BIN} PUBLIC 
	spdlog
	GCLAx2Cheat
)