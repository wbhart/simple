CXX=g++
CXX_FLAGS=-O2 -g
LIBS=znat.o nat.o twos.o
INCLUDE=-I.

all: $(LIBS)
	$(CXX) $(CXX_FLAGS) $(INCLUDE) t-znat.c $(LIBS) -o t-znat
	./t-znat

%.o:%.c %.h
	$(CXX) -c $(CXX_FLAGS) $(INCLUDE) $< -o $@

.PHONY: all
