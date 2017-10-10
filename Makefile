INC=./src/
AR=./lib/*.a

all: exercise1.3 FirstRealGA FirstBitGA

exercise1.3: exercise1.3.cpp
	g++ $< $(AR) -I. -I$(INC) -o $@ 

FirstBitGA: FirstBitGA.cpp
	g++ $< $(AR) -I. -I$(INC) -o $@ 

FirstRealGA: FirstRealGA.cpp
	g++ $< $(AR) -I. -I$(INC) -o $@ 
