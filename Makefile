CXX = clang++
CXXFLAGS = -I/opt/homebrew/opt/sdl2/include -I/opt/homebrew/opt/sdl2/include/SDL2 -I/opt/homebrew/opt/sdl2_image/include -I//opt/homebrew/opt/sdl2_ttf/include
LDFLAGS = -L/opt/homebrew/opt/sdl2/lib -lSDL2 -L/opt/homebrew/opt/sdl2_image/lib -lSDL2_image -L//opt/homebrew/opt/sdl2_ttf/lib -lSDL2_ttf

SRC = main.cpp game.cpp object.cpp audio.cpp
TARGET = game

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

clean: 
	rm -f $(TARGET)
