# =========================
# CONFIGURAÇÃO BASE
# =========================
TARGET_EXEC := app.exe

BUILD_DIR := build
SRC_DIR := src
SDL_PATH := SDL3
SDL_ARCH := x86_64-w64-mingw32

# SDL_image paths
SDL_IMAGE_PATH := SDL3_image
SDL_IMAGE_ARCH := x86_64-w64-mingw32

# =========================
# COMPILADOR
# =========================
CC := gcc

# =========================
# SDL PATHS
# =========================
SDL_INCLUDE := $(SDL_PATH)/$(SDL_ARCH)/include
SDL_LIB := $(SDL_PATH)/$(SDL_ARCH)/lib
SDL_BIN := $(SDL_PATH)/$(SDL_ARCH)/bin

SDL_IMAGE_INCLUDE := $(SDL_IMAGE_PATH)/$(SDL_IMAGE_ARCH)/include
SDL_IMAGE_LIB := $(SDL_IMAGE_PATH)/$(SDL_IMAGE_ARCH)/lib
SDL_IMAGE_BIN := $(SDL_IMAGE_PATH)/$(SDL_IMAGE_ARCH)/bin

# =========================
# FLAGS
# =========================
INCLUDES := -I$(SDL_INCLUDE) -I$(SDL_IMAGE_INCLUDE)
DEFINES := -DSDL_MAIN_HANDLED
WARNINGS := -Wall -Wextra

CFLAGS := $(INCLUDES) $(DEFINES) $(WARNINGS)
LDFLAGS := -L$(SDL_LIB) -L$(SDL_IMAGE_LIB) -lSDL3 -lSDL3_image

# =========================
# SOURCES
# =========================
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# =========================
# REGRAS
# =========================

all: compile run

# Compila objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Linka executável
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Compilar
compile: $(BUILD_DIR)/$(TARGET_EXEC)

# Rodar
run: compile
	@echo Copiando SDL3.dll...
	@cp $(SDL_BIN)/SDL3.dll $(BUILD_DIR)
	@echo Copiando SDL3_image.dll...
	@cp $(SDL_IMAGE_BIN)/SDL3_image.dll $(BUILD_DIR)
	@echo Executando...
	@./$(BUILD_DIR)/$(TARGET_EXEC)

# Limpar
clean:
	@echo Limpando build...
	@rmdir /s /q $(BUILD_DIR) 2>nul || exit 0

# Rebuild
rebuild: clean compile

# Debug
debug: CFLAGS += -g -O0
debug: clean compile

# Release
release: CFLAGS += -O2
release: clean compile

# =========================
# UTILS
# =========================
print:
	@echo SRCS: $(SRCS)
	@echo OBJS: $(OBJS)
