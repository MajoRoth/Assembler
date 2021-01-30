run: main.o word_process.o text_process.o second_stage.o first_stage.o data_structures.o assembler_main.o
	gcc -g -Wall -ansi -pedantic main.o word_process.o text_process.o second_stage.o first_stage.o data_structures.o assembler_main.o -o assembler

main.o: main.c assembler_main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o

word_process.o: word_process.c word_process.h
	gcc -c -Wall -ansi -pedantic word_process.c -o word_process.o

text_process.o: text_process.c text_process.h
	gcc -c -Wall -ansi -pedantic text_process.c -o text_process.o

second_stage.o: second_stage.c second_stage.h
	gcc -c -Wall -ansi -pedantic second_stage.c -o second_stage.o

first_stage.o: first_stage.c first_stage.h
	gcc -c -Wall -ansi -pedantic first_stage.c -o first_stage.o

data_structures.o: data_structures.c data_structures.h
	gcc -c -Wall -ansi -pedantic assembler_main.c -o data_structures.o

assembler_main.o: assembler_main.c assembler_main.h 
	gcc -c -Wall -ansi -pedantic data_structures.c -o assembler_main.o

clean:
	rm *.o *~