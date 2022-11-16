
calculatrice : calculatrice.o pile.o table.c table.o 
	gcc -o calculatrice calculatrice.o pile.o table.o  

calculatrice.o : calculatrice.c pile.h calculatrice.h
	gcc -c calculatrice.c

pile.o : pile.c pile.h
	gcc -c pile.c

table.o: table.c calculatrice.h pile.h
	gcc -c table.c

table.c: calculatrice.lex calculatrice.h pile.h
	lex -t calculatrice.lex > table.c

clean:
	rm -f *.o *~ table.c