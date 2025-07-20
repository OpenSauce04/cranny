# Set up compiler variables
CC = cc
CFLAGS = -O3 -flto=jobserver -Wall -Wextra -Werror
LDFLAGS = -flto -lm -lpthread
ifeq ($(shell uname -s),Darwin)
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

# Find dependencies
ifeq ($(shell uname -s),Darwin)
	CFLAGS += -I$(shell brew --prefix libvorbis)/include -I$(shell brew --prefix libogg)/include
endif

# Files and directory variables
SRC_DIR = src
BUILD_DIR = build
OBJECTS_DIR = $(BUILD_DIR)/objects
SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCES))
TARGET = cranny
DYNAMIC_TARGET = $(BUILD_DIR)/bin/dynamic/$(TARGET)
STATIC_TARGET = $(BUILD_DIR)/bin/static/$(TARGET)

# --= Recipes =--
all: build-dynamic

build-dynamic: $(DYNAMIC_TARGET)
build-static: $(STATIC_TARGET)

# Initialize directories
$(BUILD_DIR):
	@mkdir -p $@

# Compilation stage
$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Linking stage
$(DYNAMIC_TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(DYNAMIC_LINK_ARGS)

$(STATIC_TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) $(STATIC_LINK_ARGS)

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
