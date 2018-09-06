# base

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

example : example_script.cpp Game_Api.o
	$(CXX) $(CXXFLAGS) example_script.cpp -o example.exe

Game_Api.o : Game_Api.cpp Game_Api.h
	$(CXX) $(CXXFLAGS) Game_Api.cpp    
    
clean :
	rm -f *.o $(EXENAME)

