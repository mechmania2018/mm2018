# based on a Makefile from CS225
EXENAME = game
OBJS = GameMap.o Unit.o main.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

GameMap.o :	GameMap.h GameMap.cpp
	$(CXX) $(CXXFLAGS) GameMap.cpp

Unit.o : Unit.cpp Unit.h
	$(CXX) $(CXXFLAGS) Unit.cpp

clean :
	rm *.o $(EXENAME)
