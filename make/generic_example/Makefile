src = $(wildcard *.c)
obj = $(src:.c=.o)

LDFLAGS = -lpng -lz
# For example link libpng and zlib

myprog: $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)
# Automatic Variables 
# $@ ... the file name of the target of the rule
# $^ ... the names of all the prerequisites, with spaces between them

.PHONY: clean
clean:
	rm -f $(obj) myprog

