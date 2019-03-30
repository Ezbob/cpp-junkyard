CXXFLAGS=-std=c++11 -Llua -Ilua/include -g -Wall -Wextra -Wfatal-errors
LDFLAGS=-llua53

SRCS=$(wildcard *.cpp)
HDRS=$(wildcard *.hpp) $(wildcard *.h)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))
TARGET=lualao
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(TARGET)
