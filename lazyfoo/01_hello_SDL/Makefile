# which files to compile as part of the project
OBJS = 01_hello_SDL.cpp

CC = g++
# -w suppresses warnings
COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

# the name of our executable
OBJ_NAME = 01_hello_SDL

# This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

