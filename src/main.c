#include <stdio.h>
#include <string.h>
#include "disassemble.h"
#include "display.h"
#include <inttypes.h>
#include "instructions.h"
#include "cpu.h"
#include "ppu.h"
#include <endian.h>

int main(int argc, char *argv[])
{

    video_state v_state;

    if (init_video(&v_state) != 1)
    {
        printf("Error intializing video. Exiting....\n");
        exit(0);
    }

    struct romBytes *r = malloc(sizeof(struct romBytes));
    //

    *r = getBytes("cpu_instrs.gb");
    r->metaData = getMetaData(r);

    FILE *out = fopen("test.out", "w");

    cpu_state state;
    ppu_state _ppu_state;
    init_cpu(&state, r);
    init_ppu(&state, &_ppu_state);

    memcpy(state.address_space, r->bytes, 0x7fff); // map rom cart to memory map of cpu
    state.step = 0;

    int delay = 0;

    while (state.halt != 1)
    {
            
        while (SDL_PollEvent(&v_state.event) == 1)
        {
            if (v_state.event.type == SDL_QUIT)
            {
                state.halt = 1;
            }

            if (v_state.event.type == SDL_KEYDOWN)
            {
                // if (v_state.event.key.keysym.sym == SDLK_SPACE)
                // {
                //     if (state.step == 1)
                //     {
                //         state.step = 0;
                //     }
                //     else
                //     {
                //         state.step = 1;
                //     }
                // }

                if (v_state.event.key.keysym.sym == SDLK_s)
                {
                    delay += 10;
                }

                if (v_state.event.key.keysym.sym == SDLK_f)
                {
                    delay -= 10;
                }

                if (delay < 0)
                {
                    delay = 0;
                }
            }
        }

        SDL_Delay(delay);

        if (state.step == 1)
        {

            continue;
        }

        char text_state[512];

        // sprintf(text_state, "PC: 0x%x\nA:%x B:%x C:%x D:%x E:%x H:%x L:%x \nFlags: %d%d%d%d\nStack Pointer: %x\nFetched Data: %x \nHalted: %d\nCycle: %d\nInterrupts Enabled: %s\n",
        //         state.regs.pc,
        //         state.regs.a, state.regs.b, state.regs.c, state.regs.d, state.regs.e, state.regs.h, state.regs.l,
        //         state.regs.z_flag, state.regs.n_flag, state.regs.h_flag, state.regs.c_flag,
        //         state.regs.sp,
        //         state.fetched_data,
        //         state.halt,
        //         state.cycles,
        //         state.interrupt_master_enable == 1 ? "Yes" : "No");

        char toAppend[256];

        int lcd_regs[8];
        get_lcd_regs(&state, lcd_regs);

        system("clear");
        printf("\nPC: 0x%x\n", state.regs.pc);
        printf("A:%x B:%x C:%x D:%x E:%x H:%x L:%x \n", state.regs.a, state.regs.b, state.regs.c, state.regs.d, state.regs.e, state.regs.h, state.regs.l);
        printf("Flags: %d%d%d%d\n", state.regs.z_flag, state.regs.n_flag, state.regs.h_flag, state.regs.c_flag);
        printf("Stack Pointer: %x\n", state.regs.sp);
        printf("Fetched Data: %x \n", state.fetched_data);
        printf("Halted: %d\n", state.halt);
        printf("Cycle: %d\n\n", state.cycles);
        printf("Interrupts Enabled: %s\n", state.interrupt_master_enable == 1 ? "Yes" : "No");
        printf("LCD CONTROL REGS:\nLCD & PPU ENABLE-%d WINDOW TILE MAP AREA:%d WINDOW ENABLE:%d BG AND WINDOW TILE DATA AREA:%d BG TILE MAP AREA:%d OBJ SIZE:%d OBJ ENABLE:%d BG AND WINDOW ENABLE/PRIORITY:%d\n",
               lcd_regs[7], lcd_regs[6], lcd_regs[5], lcd_regs[4], lcd_regs[3], lcd_regs[2], lcd_regs[1], lcd_regs[0]);


        fetch_instruction(&state, r);
        //fprintf(out, "0x%x : 0x%x %s %x \n", state.regs.pc, state.curr_inst.op_code, state.curr_inst.mnmemonic, state.curr_inst.d_type == 5 ? state.fetched_data_8_signed : state.fetched_data);
        call_func(&state, state.curr_inst, r);

        // if(state.fetched_data == 0xff01)
        // {
        //     fprintf(out, "%x", state.address_space[0xff01]);
        //     clean_SDL(&v_state);
        //     exit(0);
        // }


        

        ppu_cycle(&state, &_ppu_state);

        if (state.interrupt_master_enable == 1)
        {
            handle_interrupt(&state);
        }

        state.step = 0;

        if(state.address_space[0xff02] == 0x81)//Check if the serial port is enabled, then write its contents.
        {
            fprintf(out, "%c", state.address_space[0xff01]);
        }
    }
    printf("Console output written to: %s\n", "test.out");

    

    fclose(out);

    return clean_SDL(&v_state);
}
