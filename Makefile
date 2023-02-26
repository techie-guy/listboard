PROJECT_NAME = listboard
CXX = clang++
IMGUI_DIR = third_party/imgui
SRC = src
BIN = bin
INCLUDE = include
INCLUDE_DIRS = -I$(INCLUDE) -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends -Ithird_party/glad/include
ASSETS_DIR = assets
CXXFLAGS = -std=c++11 -g -Wall $(INCLUDE_DIRS) $(shell pkg-config --cflags glfw3 libconfig++)
LDFLAGS = $(shell pkg-config --libs glfw3 libconfig++)

SOURCES = src/main.cpp src/Application.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
OBJECTS = $(patsubst %.cpp, $(BIN)/%.o, $(notdir $(SOURCES)))

.PHONY: default all prepare clean run

default: prepare $(PROJECT_NAME)
all: default

run: default
	$(info ################## Running $(BIN)/$(PROJECT_NAME) ########################)
	@./$(BIN)/$(PROJECT_NAME)

prepare:
	mkdir -p $(BIN)
	cp -r -u $(ASSETS_DIR) $(BIN)

$(BIN)/%.o: $(SRC)/%.cpp $(INCLUDE)/*.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/%.o: $(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PROJECT_NAME): $(OBJECTS)
	$(CXX) -o $(BIN)/$@ $^ $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -rf $(BIN)
