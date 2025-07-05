# Set up compiler variables
CC = cc
CFLAGS = -O3 -flto -Wall -Wextra -Werror
LDFLAGS = -flto -lm
ifeq ($(shell uname -s),Darwin)
	CFLAGS += -mmacosx-version-min=13.0
	LDFLAGS += -mmacosx-version-min=13.0
	STATICLIBS = $(shell brew --prefix libvorbis)/lib/libvorbis.a \
	             $(shell brew --prefix libvorbis)/lib/libvorbisfile.a \
	             $(shell brew --prefix libogg)/lib/libogg.a
else
	LDFLAGS += -lvorbisfile -lvorbis -logg -static
endif

# Find dependencies
ifeq ($(shell uname -s),Darwin)
	CFLAGS += -I$(shell brew --prefix libvorbis)/include -I$(shell brew --prefix libogg)/include
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
	$(CC) -o $@ $(OBJECTS) $(STATICLIBS) $(LDFLAGS)

clean:
	rm -rf $(BUILDDIR)/*

.PHONY: all clean
