cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generates compile_commands.json file for clangd, can be turned off if not needed

set(IMGUI_DIR third_party/imgui)
set(GLAD_DIR third_party/glad)

set(IMGUI_SOURCES ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_DIR}/misc/cpp/imgui_stdlib.cpp)
set(SOURCES src/main.cpp src/Application.cpp src/UI.cpp src/UiWidgets.cpp ${IMGUI_SOURCES})

set(COMPILE_DEFINITIONS)
set(COMPILE_OPTIONS)
set(LINK_OPTIONS)
set(LINK_LIBRARIES)

set(INCLUDE_DIRS include ${IMGUI_DIR} ${IMGUI_DIR}/backends ${IMGUI_DIR}/misc/cpp)
set(ASSETS_DIR assets)

set(PLATFORM Native CACHE STRING "Platform to build for. Defaults to Native for Native Build")

project(listboard)

if(PLATFORM MATCHES Emscripten)
	message("Configuring for Emscripten")
	set(COMPILE_DEFINITIONS _PLATFORM_WASM)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
	set(LINK_OPTIONS ${LINK_OPTIONS} -sUSE_GLFW=3 -sWASM=1 -sALLOW_MEMORY_GROWTH=1 -sNO_EXIT_RUNTIME=0 -sASSERTIONS=1 --preload-file ../${ASSETS_DIR})
	set(LINK_LIBRARIES ${LINK_LIBRARIES} -lglfw3 -lGLESv2 -lEGL)
elseif(PLATFORM MATCHES Native)
	set(COMPILE_DEFINITIONS _PLATFORM_NATIVE)
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GLFW3 REQUIRED glfw3)
	set(INCLUDE_DIRS ${INCLUDE_DIRS} ${GLAD_DIR}/include)
	set(LINK_LIBRARIES ${LINK_LIBRARIES} ${GLFW3_LIBRARIES})

	# Copy the assets directory to build directory
	add_custom_target(copy_assets ALL COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${ASSETS_DIR} WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" VERBATIM)
else()
	message("No Platform Specified")
endif()

#project(listboard)
add_executable(listboard ${SOURCES})
target_compile_options(listboard PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(listboard PUBLIC ${COMPILE_DEFINITIONS})
target_include_directories(listboard PUBLIC ${INCLUDE_DIRS})
target_link_options(listboard PUBLIC ${LINK_OPTIONS})
target_link_libraries(listboard PUBLIC ${LINK_LIBRARIES})
