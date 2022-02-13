set(TEST_GUI_HOOK test_gui_hook)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${TEST_GUI_HOOK} WIN32 Entry.cpp)

target_include_directories(${TEST_GUI_HOOK} PUBLIC 
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
)

target_link_libraries(${TEST_GUI_HOOK} PUBLIC 
	GCLAx2Cheat
	spdlog 
	imgui gdi32.lib shell32.lib imm32.lib d3d9.lib
)

target_include_directories(${TEST_GUI_HOOK} PUBLIC ${CMAKE_SOURCE_DIR}/include)