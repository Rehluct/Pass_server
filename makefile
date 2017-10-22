PassServer: proj5.o passserver.o
	g++ -std=c++11  -lcrypt -o proj5.x proj5.o passserver.o

proj5.o: proj5.cpp passserver.h
	g++ -std=c++11 -c proj5.cpp

passserver.o: passserver.cpp passserver.h
	g++ -std=c++11 -c passserver.cpp
	
clean:
	rm *.o *.gch hw