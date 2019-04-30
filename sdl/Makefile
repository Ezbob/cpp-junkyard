
SDL2_LIB_PATH=libs/SDL2-2.0.9/x86_64-w64-mingw32
SDL2_IMAGE_LIB_PATH=libs/SDL2_image-2.0.4/x86_64-w64-mingw32

HEADER_INCLUDES=-I${SDL2_LIB_PATH}/include/SDL2 -I${SDL2_IMAGE_LIB_PATH}/include/SDL2
LIB_INCLUDES=-L${SDL2_LIB_PATH}/lib -L${SDL2_IMAGE_LIB_PATH}/lib

CXXFLAGS=-std=c++17 -Wall -g -Wextra ${HEADER_INCLUDES} -m64
LDLIBS=-lSDL2main -lSDL2 -lSDL2_image

TARGET=game

SRCS=Main.cpp
HDRS=$(wildcard *.hpp)
OBJS=$(patsubst %.cpp, %.o, ${SRCS})

${TARGET}: ${OBJS}
	${CXX} ${LIB_INCLUDES} ${RUNTIME_INCLUDES} $^ -o $@ ${LDLIBS}

clean:
	$(RM) ${OBJS} ${TARGET}