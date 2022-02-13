set(TEST_GUI_DESIGN test_gui_design)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${TEST_GUI_DESIGN} Entry.cpp)

target_include_directories(${TEST_GUI_DESIGN} PUBLIC 
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
)

target_link_libraries(${TEST_GUI_DESIGN} PUBLIC 
	GCLAx2Cheat
	imgui gdi32.lib shell32.lib imm32.lib d3d9.lib
)