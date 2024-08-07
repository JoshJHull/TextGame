CXX = g++

CXXFLAGS = -std=c++17

main: main.cpp Enemy.o Object.o Player.o Room.o
	$(CXX) $(CXXFLAGS) main.cpp Enemy.o Object.o Player.o Room.o -o main
	
Enemy.o: Enemy.cpp Enemy.h
	$(CXX) $(CXXFLAGS) -c Enemy.cpp -o Enemy.o
	
Object.o: Object.cpp Object.h
	$(CXX) $(CXXFLAGS) -c Object.cpp -o Object.o
	
Player.o: Player.cpp Player.h
	$(CXX) $(CXXFLAGS) -c Player.cpp -o Player.o

Room.o: Room.cpp Room.h
	$(CXX) $(CXXFLAGS) -c Room.cpp -o Room.o
	
deepclean:
	rm -f *.o main main.exe *.stackdump