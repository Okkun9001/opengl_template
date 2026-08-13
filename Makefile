CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused \
				 -I./external/glad/include/ \
				 -I./include/ 
LDFLAGS = -lglfw -lGL -lm

all: main

main: 
	$(CC) $(CFLAGS) \
	main.c \
	shaders/shader_utils.c \
	external/glad/src/gl.c \
	-o main $(LDFLAGS)

run:
	./main

clean:
	rm -f main
