CC = gcc
CFLAGS = -g -Wall
LIBS = -lm -lpng
DEPS = main.h
OBJS = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

writepng: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm writepng *.o *~
