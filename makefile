CC=gcc
BUILD_DIR=build
SRC_DIR=src
INC_DIR=include
INCLUDE=-I$(INC_DIR)
LIBS=-lMLV -lm
CFLAGS= -Wall -std=c17 -pedantic -g -g3

EXEC=convexhull

SOURCES=$(wildcard $(SRC_DIR)/*.c)
HEADERS=$(wildcard $(INC_DIR)/*.h)

# On récupère tous les fichiers sources .c, et on leurs préfixe
# le chemin de build, et suffixe en .o :
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCES))
#$(info $(OBJS))

all: $(EXEC)

# Assemblage de l'exécutable final
$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

# Dépendances
main.o: main.c game.h graph.h init.h interaction.h struct.h tool.h
game.o: struct.h game.h
graph.o: struct.h graph.h
init.o: struct.h init.h tool.h
interaction.o: struct.h interaction.h
tool.o: struct.h tool.h

# Création des fichiers objets à partir des fichiers sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir --parents $(BUILD_DIR)
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

mrproper: clean
	rm -f $(EXEC)