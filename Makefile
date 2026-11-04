PROGRAMS = freq

CXX = c++
CXXFLAGS = -Wall -Wextra -pedantic -O2 -std=c++17
LDLIBS =

.PHONY: all clean

all: $(PROGRAMS)

%: %.cc
	$(CXX) $(CXXFLAGS) $< $(LDLIBS) -o $@
	strip $@

clean:
	rm -f $(PROGRAMS)
