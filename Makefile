################################################################################
#   Object oriented GLFW wrapper
#   Build rules
#   
#   © 2023—2024, Sauron
################################################################################

NAME=glfwxx
CC=$(if $(TOOLCHAIN), /usr/bin/$(TOOLCHAIN)-)g++
CFLAGS=-Wall -Wextra #-Wno-unused-parameter
CXXFLAGS=$(CFLAGS) -pthread 
CXXFLAGS_LIBS=$(CXXFLAGS) -Os -shared -fPIC
SOURCES=*.cpp
HEADERS=*.hpp
LIBRARIES=-lglfw -lstdc++
OUTPUT=libglfw++.so

all: $(OUTPUT)

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CC) $(CXXFLAGS_LIBS) -o $(OUTPUT) $(SOURCES) $(LIBRARIES)

clean:
	rm -f *.o *.so

release: all
	strip $(OUTPUT)

install: $(OUTPUT)
	strip $(OUTPUT)
	mv $(OUTPUT) /usr/lib64
	mkdir -p /usr/include/GLFW
	cp $(HEADERS) /usr/include/GLFW

.PHONY:
	all release install clean

