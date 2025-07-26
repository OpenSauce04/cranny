# Set up compiler variables
CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm -lpthread

ifeq ($(shell uname -s),Darwin)
	CFLAGS += -I$(shell brew --prefix libvorbis)/include -I$(shell brew --prefix libogg)/include
	CFLAGS += -mmacosx-version-min=13.0
	LDFLAGS += -mmacosx-version-min=13.0
	DYNAMIC_LINK_ARGS = -L$(shell brew --prefix libvorbis)/lib -lvorbis -lvorbisfile
	STATIC_LINK_ARGS = $(shell brew --prefix libvorbis)/lib/libvorbis.a \
	                   $(shell brew --prefix libvorbis)/lib/libvorbisfile.a \
	                   $(shell brew --prefix libogg)/lib/libogg.a
else
	ifeq ($(shell uname -s),FreeBSD)
		CFLAGS += -I/usr/local/include -Wno-unused-function
		LDFLAGS += -L/usr/local/lib
	endif
	LDFLAGS += -lvorbis -lvorbisfile
	STATIC_LINK_ARGS = -lvorbis -logg -static
endif

DEBUG_CFLAGS = $(CFLAGS) -g
RELEASE_CFLAGS = $(CFLAGS) -O3 -flto=jobserver
DEBUG_LDFLAGS = $(LDFLAGS)
RELEASE_LDFLAGS = $(LDFLAGS) -flto

# Files and directory variables
SRC_DIR = src
BUILD_DIR = build
OBJECTS_DIR = $(BUILD_DIR)/objects
SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
DEBUG_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/debug/%.o, $(SOURCES))
RELEASE_OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/release/%.o, $(SOURCES))
TARGET = cranny
DEBUG_TARGET = $(BUILD_DIR)/bin/debug/$(TARGET)
DYNAMIC_TARGET = $(BUILD_DIR)/bin/dynamic/$(TARGET)
STATIC_TARGET = $(BUILD_DIR)/bin/static/$(TARGET)

# --= Recipes =--
all: build-dynamic

build-debug: $(DEBUG_TARGET)
build-dynamic: $(DYNAMIC_TARGET)
build-static: $(STATIC_TARGET)

# Initialize directories
$(BUILD_DIR):
	@mkdir -p $@

# Compilation stage
$(OBJECTS_DIR)/debug/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

$(OBJECTS_DIR)/release/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(RELEASE_CFLAGS) -c $< -o $@

# Linking stage
$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $(DEBUG_OBJECTS) $(DEBUG_LDFLAGS) $(DYNAMIC_LINK_ARGS)

$(DYNAMIC_TARGET): $(RELEASE_OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $(RELEASE_OBJECTS) $(RELEASE_LDFLAGS) $(DYNAMIC_LINK_ARGS)

$(STATIC_TARGET): $(RELEASE_OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $(RELEASE_OBJECTS) $(RELEASE_LDFLAGS) $(STATIC_LINK_ARGS)

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
