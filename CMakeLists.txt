cmake_minimum_required(VERSION 3.2.1)

set(CMAKE_CXX_STANDARD 14)

set(IMGUI_DIR third_party/imgui)
set(GLAD_DIR third_party/glad)

set(IMGUI_SOURCES ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp)
set(SOURCES src/main.cpp src/Application.cpp ${IMGUI_SOURCES})

set(COMPILE_DEFINITIONS)
set(COMPILE_OPTIONS)
set(LINK_OPTIONS)
set(LINK_LIBRARIES)
set(INCLUDE_DIRS include ${IMGUI_DIR} ${IMGUI_DIR}/backends)

if($ENV{COMPILE_FOR_WASM})
	set(COMPILE_DEFINITIONS _PLATFORM_WASM)
	set(CMAKE_TOOLCHAIN_FILE $ENV{EMSDK_HOME}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(LINK_OPTIONS ${LINK_OPTIONS} -sUSE_GLFW=3 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sNO_EXIT_RUNTIME=0 -sASSERTIONS=1)
	set(LINK_LIBRARIES ${LINK_LIBRARIES} -lglfw3 -lGLESv2 -lEGL)
else()
	set(COMPILE_DEFINITIONS _PLATFORM_NATIVE)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GLFW3 REQUIRED glfw3)
	set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GLAD_DIR}/include)
	set(LINK_LIBRARIES ${LINK_LIBRARIES} ${GLFW3_LIBRARIES})
endif()

project(listboard)

add_executable(listboard ${SOURCES})
target_compile_options(listboard PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(listboard PUBLIC ${COMPILE_DEFINITIONS})
target_include_directories(listboard PUBLIC ${INCLUDE_DIRS})
target_link_options(listboard PUBLIC ${LINK_OPTIONS})
target_link_libraries(listboard PUBLIC ${LINK_LIBRARIES})
