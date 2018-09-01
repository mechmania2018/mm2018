# based on a Makefile from CS225
EXENAME = game.exe

OBJS = ScriptIO.o Unit.o Player.o Monster.o Game.o main.o

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libstdc++ -c -g -O0 -Wall -Wextra -Werror -I./includes/
LDFLAGS = -std=c++1y -stdlib=libstdc++ -lpthread

all : $(EXENAME) example

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp Game.o
	$(CXX) $(CXXFLAGS) main.cpp

Game.o : Game.cpp Game.h
	$(CXX) $(CXXFLAGS) Game.cpp

Unit.o : Unit.cpp Unit.h
	$(CXX) $(CXXFLAGS) Unit.cpp

Player.o : Player.cpp Player.h Unit.o
	$(CXX) $(CXXFLAGS) Player.cpp

Monster.o : Monster.cpp Monster.h Unit.o
	$(CXX) $(CXXFLAGS) Monster.cpp

ScriptIO.o : ScriptIO.cpp ScriptIO.h
	$(CXX) $(CXXFLAGS) ScriptIO.cpp

example : example_script.cpp
	$(CXX) example_script.cpp -o example.exe

clean :
	rm -f *.o $(EXENAME)
