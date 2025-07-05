# Set up compiler variables
CC = cc
CFLAGS = -O2 -Wall -Wextra -Werror
LDFLAGS = -lm -lvorbisfile
ifeq ($(shell uname -s),Darwin)
	CFLAGS += -mmacosx-version-min=11.0
	LDFLAGS += -mmacosx-version-min=11.0
endif

# Find dependencies
ifeq ($(shell uname -s),Darwin)
	CFLAGS += -I$(shell brew --prefix libvorbis)/include -I$(shell brew --prefix libogg)/include
	LDFLAGS += -L$(shell brew --prefix libvorbis)/lib
endif

# Files and directory variables
SRCDIR = src
BUILDDIR = build
OBJECTSDIR = $(BUILDDIR)/objects
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJECTSDIR)/%.o, $(SOURCES))
TARGET = $(BUILDDIR)/cranny

all: $(TARGET)

# Initialize directories
$(BUILDDIR):
	@mkdir -p $@

# Compilation stage
$(OBJECTSDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Linking stage
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)/*

.PHONY: all clean
