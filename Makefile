PROGRAMS = c-sim

CC = gcc
CFLAGS = -Wall

%: %.c %.h
	$(CC) $(CFLAGS) -o $@ $< -lm
.PHONY: all clean

all: $(PROGRAMS)

clean:
	@rm -f *.o $(PROGRAMS)
