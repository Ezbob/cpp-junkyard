HEADER_INCLUDES=-Ilibs\SDL2-2.0.9\x86_64-w64-mingw32\include\SDL2 -Ilibs\SDL2_image-2.0.4\x86_64-w64-mingw32\include\SDL2
LIB_INCLUDES=-Llibs\SDL2-2.0.9\x86_64-w64-mingw32\lib -Llibs\SDL2_image-2.0.4\x86_64-w64-mingw32\lib
CXXFLAGS=-std=c++17 -Wall -g -Wextra ${HEADER_INCLUDES}
LDLIBS=-lSDL2main -lSDL2 -lSDL2_image

TARGET=test

SRCS=Main.cpp
HDRS=$(wildcard *.hpp)
OBJS=$(patsubst %.cpp, %.o, ${SRCS})

${TARGET}: ${OBJS}
	${CXX} ${LIB_INCLUDES} ${RUNTIME_INCLUDES} $^ -o $@ ${LDLIBS}

clean:
	$(RM) ${OBJS} ${TARGET}