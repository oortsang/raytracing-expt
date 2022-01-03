CC = gcc
CFLAGS = -g -Wall
LIBS = -lm -lpng
DEPS = main.h sphere.h camera.h my_vector.h png_interface.h
OBJS = main.o sphere.o camera.o my_vector.o png_interface.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sphere: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm sphere *.o *~
