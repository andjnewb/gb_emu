diss: src/main.c src/disassemble.c src/disassemble.h src/instructions.h src/instructions.c src/cpu.h src/cpu.c src/stack.h src/stack.c
	gcc -o diss src/main.c src/disassemble.c src/disassemble.h src/instructions.h src/instructions.c src/cpu.h src/cpu.c src/stack.h src/stack.c  -g -lSDL2 -lSDL2_ttf
