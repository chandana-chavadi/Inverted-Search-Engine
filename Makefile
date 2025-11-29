# Build target
output: main.o create_database.o createSLL.o display_output.o common.o save.o search.o update.o validate.o
	gcc -o $@ $^

# Compilation rules for each .c file
main.o: main.c
	gcc -c main.c -o main.o

create_database.o: create_database.c
	gcc -c create_database.c -o create_database.o

createSLL.o: createSLL.c
	gcc -c createSLL.c -o createSLL.o

display_output.o: display_output.c
	gcc -c display_output.c -o display_output.o

common.o: common.c
	gcc -c common.c -o common.o

save.o: save.c
	gcc -c save.c -o save.o

search.o: search.c
	gcc -c search.c -o search.o

update.o: update.c
	gcc -c update.c -o update.o

validate.o: validate.c
	gcc -c validate.c -o validate.o

# Clean rule
clean:
	rm -f *.o output
