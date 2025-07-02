CC = gcc
CFLAGS = -O2 -Wall -Wextra -Werror
SRCDIR = src
BUILDDIR = build
OBJECTSDIR = $(BUILDDIR)/objects
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJECTSDIR)/%.o, $(SOURCES))
TARGET = $(BUILDDIR)/cranny

all: $(TARGET)

$(TARGET): $(BUILDDIR) $(OBJECTSDIR) $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

$(OBJECTSDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(OBJECTSDIR):
	mkdir $(OBJECTSDIR)

clean:
	rm -rf $(BUILDDIR)/*
