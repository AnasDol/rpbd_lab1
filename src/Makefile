CC=g++
CFLAGS=-Wall -Wextra -Werror

all: main

main:
	$(CC) $(CFLAGS) main.cpp C:/msys64/mingw64/lib/libodbc32.a -o ../build/main.exe

project:
	$(CC) $(CFLAGS) start.cpp defaults.hpp ActiveRecord/*.cpp connection.cpp menu.cpp C:/msys64/mingw64/lib/libodbc32.a -o ../build/start.exe

test:
	$(CC) $(CFLAGS) test.cpp connection.cpp ActiveRecord/*.cpp menu.cpp C:/msys64/mingw64/lib/libodbc32.a -o ../build/test.exe
