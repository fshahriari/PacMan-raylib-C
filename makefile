# OBJS specifies which files to compile as part of the project
OBJS = PACMAN.c

# CC specifies which compiler we're using
CC = gcc

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I C:/raylib/raylib/src

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L C:/raylib/raylib/src

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

# LINKER_FLAGS specifies the libraries we're linking against
# -Wl,-subsystem,windows gets rid of the console window
LINKER_FLAGS = -lraylib -lmingw32 -lgdi32 -lwinmm -Wl,-subsystem,windows

# OBJ_NAME specifies the name of our executable
OBJ_NAME = PACMAN

# This is the target that compiles our executable
all: $(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

clean:
	del $(OBJ_NAME).exe

.PHONY: all clean