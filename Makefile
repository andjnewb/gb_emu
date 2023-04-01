diss: src/main.c src/disassemble.c src/disassemble.h src/instructions.h src/cpu.h src/cpu.c
	gcc -o diss src/main.c src/disassemble.c src/disassemble.h src/instructions.h src/cpu.h src/cpu.c  -g
