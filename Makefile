threadsynchro: threadsynchro.cpp buffer.cpp
	g++ -o threadsynchro threadsynchro.cpp buffer.cpp -lpthread

clean:
	rm -f threadsynchro *~