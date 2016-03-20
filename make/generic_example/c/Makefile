CC = gcc # c compiler to use

src = $(wildcard *.c)
obj = $(src:.c=.o)

CFLAGS = -Wall # c-compiler flags
CPPFLAGS = # c-preprocessor flags 
LDFLAGS = -lpng -lz # linker flags, for example link libpng and zlib

myprog: $(obj)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
# Automatic Variables 
# $@ ... the file name of the target of the rule
# $^ ... the names of all the prerequisites, with spaces between them

.PHONY: clean
clean:
	rm -f $(obj) myprog

