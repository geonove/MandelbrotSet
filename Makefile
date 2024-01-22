CXXFLAGS = -O3 -fopenmp
main: main.o game.o mandelbrot.o 
	$(CXX) $(CXXFLAGS) main.o Game.o Mandelbrot.o -o main -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

game.o:
	$(CXX) $(CXXFLAGS) -c Game.cpp

mandelbrot.o: 
	$(CXX) $(CXXFLAGS) -c Mandelbrot.cpp

clean: 
	rm -f main

distclean: clean
	rm -f *.o

run:
	./main

new: distclean main.o main run
	