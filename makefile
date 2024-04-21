CC=g++ -g
EXE_FILE=coffee

all: $(EXE_FILE)

$(EXE_FILE): prog.o shop.o order.o coffee.o menu.o display.o
	$(CC) prog.o shop.o order.o coffee.o menu.o display.o -o $(EXE_FILE)

prog.o: prog.cpp
	$(CC) -c prog.cpp

shop.o: shop.cpp shop.h menu.h order.h
	$(CC) -c shop.cpp

menu.o: menu.cpp menu.h coffee.h
	$(CC) -c menu.cpp

coffee.o: coffee.cpp coffee.h
	$(CC) -c coffee.cpp

order.o: order.cpp order.h
	$(CC) -c order.cpp

display.o: display.cpp display.h
	$(CC) -c display.cpp

clean:
	rm -f *.o $(EXE_FILE)