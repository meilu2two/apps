CXX = g++ # c++ compiler to use

src = $(wildcard *.cpp)
obj = $(src:.cpp=.o)

CXXFLAGS = -Wall # c++-compiler flags
CPPFLAGS = # c-preprocessor flags 
LDFLAGS = #-lpng -lz # linker flags, for example link libpng and zlib

executable: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
# Automatic Variables 
# $@ ... the file name of the target of the rule
# $^ ... the names of all the prerequisites, with spaces between them

.PHONY: clean
clean:
	rm -f $(obj) executable

