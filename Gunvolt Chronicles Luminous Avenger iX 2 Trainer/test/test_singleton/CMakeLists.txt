set(TEST_SINGLETON test_singleton)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${TEST_SINGLETON} Entry.cpp)

target_link_libraries(${TEST_SINGLETON} PUBLIC 
	spdlog
	GCLAx2Cheat
)

target_include_directories(${TEST_SINGLETON} PUBLIC 
	${CMAKE_SOURCE_DIR}/include
)