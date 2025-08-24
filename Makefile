# === Configuração ===
CONFIG ?= debug
CC      := gcc
CSTD    := -std=c11
WARN    := -Wall -Wextra -Wpedantic
DEFS 	:= -D_CRT_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0601
INCS    := -Iinclude

ifeq ($(CONFIG),debug)
  CFLAGS := $(CSTD) $(WARN) -Og -g $(DEFS) $(INCS)
else
  CFLAGS := $(CSTD) $(WARN) -O2 -DNDEBUG $(DEFS) $(INCS)
endif

LDLIBS := -lwinmm -luser32 -lkernel32

# === Arquivos ===
SRC_LIB := $(wildcard src/*.c)
OBJ_LIB := $(patsubst src/%.c,build/%.o,$(SRC_LIB))
DEP_LIB := $(OBJ_LIB:.o=.d)

DEMO_TITLE := jump
DEMO       := examples/$(DEMO_TITLE)/main.c
OBJ_DEMO   := build/$(DEMO_TITLE).o
DEP_DEMO   := $(OBJ_DEMO:.o=.d)

BIN_DIR := bin
BLD_DIR := build
TARGET  := $(BIN_DIR)/$(DEMO_TITLE).exe

# === Alvos ===
.PHONY: all run clean rebuild

# Alvo principal, que também executa o programa
all: $(TARGET) run

$(TARGET): $(OBJ_LIB) $(OBJ_DEMO) | $(BIN_DIR)
	$(CC) $^ -o $@ $(LDLIBS)

# Objetos da lib
build/%.o: src/%.c | $(BLD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Objeto do demo
$(OBJ_DEMO): $(DEMO) | $(BLD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Diretiva para rodar o programa após compilação
run: $(TARGET)
	./$(TARGET)

clean:
	-$(RM) -r $(BLD_DIR) $(BIN_DIR)

rebuild: clean all

$(BIN_DIR) $(BLD_DIR):
	mkdir -p $@

-include $(DEP_LIB) $(DEP_DEMO)
