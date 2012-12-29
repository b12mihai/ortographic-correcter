CPP = g++
CFLAGS = -Wall -Wextra -funroll-loops -O3
EXEC = tema1pa
OBJ = main.o corector.o util.o

build: $(OBJ)
	$(CPP) $(CFLAGS) $(OBJ) -o $(EXEC)

run:
	./$(EXEC)

.PHONY: clean
clean:
	rm -f a.out $(EXEC) *.o *~

#Test some examples
test:
	echo "error free text" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "this is dumy text" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "supermarket" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "sore served" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "solvethis coo lhomewor" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "schaprobl mcanbe easilisolved" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "alwaysdezire tol earn someting usefull" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "favoritemusikchannel" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	echo "cattt" > input.txt
	time ./$(EXEC) < input.txt >> output.txt
	cat output.txt
	rm -f input.txt output.txt
