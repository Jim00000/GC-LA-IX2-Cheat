target_sources(GCLAx2Cheat PUBLIC
	DllMain.cpp 
	CheatLogger.cpp
	CheatManager.cpp
	CheatUIRender.cpp
	UIManager.cpp
	GameVersion.cpp
	VTableManager.cpp
	Hook.cpp
)
add_subdirectory(Helper)
add_subdirectory(Gui)