CC = cc
CFLAGS = -O2 -Wall -Wextra -Werror
SRCDIR = src
BUILDDIR = build
OBJECTSDIR = $(BUILDDIR)/objects
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJECTSDIR)/%.o, $(SOURCES))
TARGET = $(BUILDDIR)/cranny

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

$(OBJECTSDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	@mkdir -p $@

clean:
	rm -rf $(BUILDDIR)/*

.PHONY: all clean