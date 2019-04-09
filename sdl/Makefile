HEADER_INCLUDES=-ISDL2-2.0.9\x86_64-w64-mingw32\include
LIB_INCLUDES=-LSDL2-2.0.9\x86_64-w64-mingw32\lib
CXXFLAGS=-std=c++11 -Wall -Wextra ${HEADER_INCLUDES}
LDLIBS=-lSDL2main -lSDL2

TARGET=test

SRCS=Main.cpp
HDRS=$(wildcard *.hpp)
OBJS=$(patsubst %.cpp, %.o, ${SRCS})

${TARGET}: ${OBJS}
	${CXX} ${LIB_INCLUDES} $^ -o $@ ${LDLIBS}

clean:
	$(RM) ${OBJS} ${TARGET}