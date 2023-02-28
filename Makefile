NATIVE_CXX = clang++
WASM_CXX = em++


PROJECT_NAME = listboard
CXX = $(NATIVE_CXX)
IMGUI_DIR = third_party/imgui
SRC = src
BIN = bin
INCLUDE = include
INCLUDE_DIRS = -I$(INCLUDE) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -Ithird_party/glad/include
ASSETS_DIR = assets
CXXFLAGS = -std=c++11 -g -Wall $(INCLUDE_DIRS)
LDFLAGS =
PLATFORM =

SOURCES = src/main.cpp src/Application.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJECTS = $(patsubst %.cpp, $(BIN)/$(PLATFORM)/%.o, $(notdir $(SOURCES)))

# if wasm condition here:
ifeq ($(COMPILE_PLATFORM),$(filter $(COMPILE_PLATFORM),Native,))
	PLATFORM = Native
	CXX = $(NATIVE_CXX)
	CXXFLAGS += -D_PLATFORM_NATIVE $(shell pkg-config --cflags glfw3 fmt)
	LDFLAGS += $(shell pkg-config --libs glfw3)
else ifeq ($(COMPILE_PLATFORM),$(filter $(COMPILE_PLATFORM),Wasm))
	PLATFORM = Wasm
	CXX = $(WASM_CXX)
	CXXFLAGS +=  -D_PLATFORM_WASM -o $(BIN)/$(PLATFORM)/$(PROJECT_NAME).html
	LDFLAGS += -sMIN_WEBGL_VERSION=2 -sMAX_WEBGL_VERSION=2 -sUSE_GLFW=3 -sWASM=1 -lglfw3 -lGLESv2 -lEGL
endif

.PHONY: prepare clean run

default: prepare $(PROJECT_NAME)
all: default

run: default
	$(info ################## Running $(BIN)/$(PROJECT_NAME) ########################)
	@./$(BIN)/Native/$(PROJECT_NAME)

prepare:
	mkdir -p $(BIN) $(BIN)/$(PLATFORM)
	cp -r -u $(ASSETS_DIR) $(BIN)

$(BIN)/$(PLATFORM)/%.o: $(SRC)/%.cpp $(INCLUDE)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/$(PLATFORM)/%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/$(PLATFORM)/%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROJECT_NAME): $(OBJECTS)
	$(CXX) -o $(BIN)/$(PLATFORM)/$@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf $(BIN)
