EXEC := a.out
INCLUDES := 
LINK := 
RM := rm -f
CLEAN_PATH := src/*.o src/core/*.o src/server/*.o src/misc/*.o $(EXEC)

CXX := gcc
CXXFLAGS := -std=c99 -O2 -Wall

SRCS := $(wildcard src/*.c src/core/*.c src/server/*.c src/misc/*.c)
OBJS := $(SRCS:.c=.o)

%.o: %.c
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC) $(LINK)

clean:
	$(RM) $(CLEAN_PATH)
