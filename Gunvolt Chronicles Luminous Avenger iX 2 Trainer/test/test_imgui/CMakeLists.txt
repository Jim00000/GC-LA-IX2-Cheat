set(TEST_IMGUI_BIN test_imgui)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${TEST_IMGUI_BIN} TestGUI.cpp)

target_include_directories(${TEST_IMGUI_BIN} PUBLIC 
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
)

target_link_libraries(${TEST_IMGUI_BIN} PUBLIC 
	imgui gdi32.lib shell32.lib imm32.lib d3d9.lib
)