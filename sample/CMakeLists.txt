

set(SOURCES
	${IMP_IMGUI_DIR}/imgui.cpp
	${IMP_IMGUI_DIR}/imgui_draw.cpp
	${IMP_IMGUI_DIR}/imgui_widgets.cpp
	${IMP_IMGUI_DIR}/imgui_demo.cpp
	${IMP_IMGUI_DIR}/backends/imgui_impl_sdl.cpp
	${IMP_IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
	${IMP_SOURCE_DIR}/include/imponder.h
	example.h example.cpp
	main.cpp)

set(CMAKE_PREFIX_PATH "${USER_LOCAL}/share/sdl2")
#set(SDL2_DIR

find_package(SDL2 CONFIG REQUIRED)

include_directories(${USER_LOCAL}/include ${IMP_SOURCE_DIR}/include ${IMP_PONDER_DIR}/include ${IMP_IMGUI_DIR} ${IMP_IMGUI_DIR}/backends)

link_directories(AFTER ${USER_LOCAL}/lib)

add_executable(ImPonderSample ${SOURCES})
target_link_libraries(ImPonderSample PRIVATE SDL2::SDL2 SDL2::SDL2main gl3w)
