diss: src/main.c src/disassemble.c src/disassemble.h src/instructions.h src/instructions.c src/cpu.h src/cpu.c src/stack.h src/stack.c src/interrupt.h src/display.h src/display.c
	gcc src/main.c src/disassemble.c src/disassemble.h src/instructions.h src/instructions.c src/cpu.h src/cpu.c src/stack.h src/stack.c src/interrupt.h src/display.h src/display.c -o diss -g -lSDL2 -lSDL2_ttf -lSDL2_image
