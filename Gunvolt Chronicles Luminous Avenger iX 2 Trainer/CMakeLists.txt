cmake_minimum_required (VERSION 3.20)

project ("Gunvolt Chronicles Luminous Avenger iX 2 Trainer")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

include(FetchContent)

FetchContent_Declare(   spdlog
    GIT_REPOSITORY      https://github.com/gabime/spdlog
    GIT_TAG             v1.9.2
    GIT_PROGRESS        TRUE
)

FetchContent_Declare(   imgui
    GIT_REPOSITORY      https://github.com/ocornut/imgui
    GIT_TAG             v1.87
    GIT_PROGRESS        TRUE
)

FetchContent_MakeAvailable(spdlog imgui)

add_library(imgui STATIC 
	${imgui_SOURCE_DIR}/imgui_demo.cpp
	${imgui_SOURCE_DIR}/imgui_draw.cpp
	${imgui_SOURCE_DIR}/imgui_tables.cpp
	${imgui_SOURCE_DIR}/imgui_widgets.cpp
	${imgui_SOURCE_DIR}/imgui.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
	${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
)

target_include_directories(imgui PUBLIC 
	${imgui_SOURCE_DIR} 
	${imgui_SOURCE_DIR}/backends
)

add_library(GCLAx2Cheat SHARED)
add_dependencies(GCLAx2Cheat spdlog)
target_link_libraries(GCLAx2Cheat PUBLIC 
	spdlog
	imgui 
	gdi32.lib shell32.lib imm32.lib d3d9.lib 
)
target_include_directories(GCLAx2Cheat PUBLIC 
	${CMAKE_SOURCE_DIR}/include
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
)
add_subdirectory(src/)
add_subdirectory(test/)