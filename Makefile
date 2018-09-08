# base

CXX = clang++
LD = clang++
CXXFLAGS = -std=c++1y -stdlib=libstdc++ -c -g -O0 -Wall -Wextra -Werror -I./includes/
LDFLAGS = -std=c++1y -stdlib=libstdc++

all : $(EXENAME) example.exe

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

example.exe : example_script.cpp
	$(LD) example_script.cpp $(LDFLAGS) -o example.exe
    
clean :
<<<<<<< HEAD
	rm -f *.o $(EXENAME)

=======
	rm -f *.o $(EXENAME) example.exe
>>>>>>> 1726a7a5984a206a769c27cbc45ec91cfdf25ec3
