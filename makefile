run: main.o text_process.o second_stage.o first_stage.o data_structures.o assembler_main.o debug_tools.o error_handlers.o
	gcc -g -Wall -ansi -pedantic main.o text_process.o second_stage.o first_stage.o data_structures.o assembler_main.o debug_tools.o error_handlers.o -lm -o assembler

main.o: main.c assembler_main.h
	gcc -c -Wall -ansi -pedantic main.c -o main.o

text_process.o: text_process.c text_process.h
	gcc -c -Wall -ansi -pedantic text_process.c -o text_process.o

data_structures.o: data_structures.c data_structures.h
	gcc -c -Wall -ansi -pedantic data_structures.c -o data_structures.o

second_stage.o: second_stage.c second_stage.h
	gcc -c -Wall -ansi -pedantic second_stage.c -o second_stage.o

first_stage.o: first_stage.c first_stage.h
	gcc -c -Wall -ansi -pedantic first_stage.c -lm -o first_stage.o

assembler_main.o: assembler_main.c assembler_main.h
	gcc -c -Wall -ansi -pedantic assembler_main.c -o assembler_main.o

debug_tools.o: debug_tools.c debug_tools.h
	gcc -c -Wall -ansi -pedantic debug_tools.c -o debug_tools.o

error_handlers.o: error_handlers.c error_handlers.h
	gcc -c -Wall -ansi -pedantic error_handlers.c -o error_handlers.o

clean:
	rm ~.o
