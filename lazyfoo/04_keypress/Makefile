# which files to compile as part of the project
OBJS = 04_keypress.cpp

CC = g++
# -w suppresses warnings
COMPILER_FLAGS = -w

LINKER_FLAGS = -lSDL2

# the name of our executable
OBJ_NAME = 04_keypress

# This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	rm -f $(OBJ_NAME) *.o
