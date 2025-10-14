CXX = g++
CXXFLAGS = -IC:/SFML-3.0.0/include
LDFLAGS = -LC:/SFML-3.0.0/lib -lmingw32 -lsfml-graphics -lsfml-window -lsfml-system -mwindows
SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
TARGET = $(BUILD_DIR)/main.exe

all: $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)