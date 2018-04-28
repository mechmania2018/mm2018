# based on a Makefile from CS225
EXENAME = game.exe

OBJS = ScriptIO.o Unit.o Player.o Monster.o Manager.o Game.o main.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libstdc++ -c -g -O0 -Wall -Wextra -Werror -pedantic -pthread
LDFLAGS = -std=c++1y -stdlib=libstdc++ -pthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

Game.o :	Game.h Game.cpp
	$(CXX) $(CXXFLAGS) Game.cpp

Unit.o : Unit.cpp Unit.h
	$(CXX) $(CXXFLAGS) Unit.cpp

Player.o : Player.cpp Player.h Unit.h
	$(CXX) $(CXXFLAGS) Player.cpp

Monster.o : Monster.cpp Monster.h Unit.h
	$(CXX) $(CXXFLAGS) Monster.cpp

Manager.o : Manager.cpp Manager.h ScriptIO.h
	$(CXX) $(CXXFLAGS) Manager.cpp

ScriptIO.o : ScriptIO.cpp ScriptIO.h
	$(CXX) $(CXXFLAGS) ScriptIO.cpp

clean :
	rm -f *.o $(EXENAME)
