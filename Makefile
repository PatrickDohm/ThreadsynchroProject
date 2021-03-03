threadsynchro: threadsynchro.o buffer.o
	g++ threadsynchro.cpp buffer.cpp -lpthread -o threadsynchro


clean:
	rm -f threadsynchro *~