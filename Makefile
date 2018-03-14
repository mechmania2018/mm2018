# based on a Makefile from CS225
EXENAME = game.exe

OBJS = Unit.o Node.o Player.o Monster.o Game.o main.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -Werror -pedantic
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

Game.o :	Game.h Game.cpp
	$(CXX) $(CXXFLAGS) Game.cpp

Unit.o : Unit.cpp Unit.h
	$(CXX) $(CXXFLAGS) Unit.cpp

Player.o : Player.cpp Player.h
	$(CXX) $(CXXFLAGS) Player.cpp

Monster.o : Monster.cpp Monster.h
	$(CXX) $(CXXFLAGS) Monster.cpp

Node.o : Node.cpp Node.h
	$(CXX) $(CXXFLAGS) Node.cpp

clean :
	rm -f *.o $(EXENAME)