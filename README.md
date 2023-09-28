# gb_emu
This project started out and continues to be a way for me to learn more about emulation. To that end, it is far from perfect and though usuable for CPU emulation, other parts such as PPU emulation are under-developed or incomplete.
# Status
Currently, my testing method is to run my emulator alongside a more established emulator with a built in debugger running Tetris. To that end my emulator can accurately emulate CPU function up to address 0x31. It will effectively emulate thousands of lines of code before reaching that point,
as 0x31 is actually a subroutine and not where program execution begins on the GameBoy. Most of the bitwise "extra" functions of the GameBoy architecture have already been implemented using macros. Bugs still exist, and the ones that do are pesky to hunt down because they behave 
well until around 0x31. Again, almost all of my testing has been done with Tetris as it is arguably the simplest game to emulate. I have also used various test suites for GameBoy functions. Currently all of the non-cb functions are implemented as well, but the bug load there is 
much higher than in the CB instructions. Most of the issues stem from behavior that is not clearly documented, as in edge cases which many programs take advantage of. The only way to figure out that stuff is to watch a debugger and see how it behaves, which can be very tedious for
the 256 base instructions.
# Goals
When I started this project I had every intention of emulating the GameBoy from the bottom up. Now, having realized the scope of what I was attempting, my current focus is on non-cycle accurate CPU emulation. I'm not entirely ignorning cycles per-se, as I have a way to know how many
cycles(even on branching instructions) that each instruction should take. I just don't have system to actually use that cycle information as of yet. Once I have confidence that my registers and memory locations agree with what established emulators show, I plan to implement a system
to execute the code in a cycle-accurate way. Possible methods include artificial speed restriction, a loop that only runs a given number of cycles etc.
# Building
This project uses standard C libraries and as such should build without any dependcies. At some point, I planned to use other libraries to parse code, so if any weird includes are hanging out in there they should be safe to delete if you're getting build errors.
Linux was used for the majority of development and is the recommended platform. Newer commits can be convinced, with a lot of work, to run on Windows but behaviour differs for known and unknown reasons. The first issue that you'll likely encounter is that Windows has no idea 
what uint_16 or any related types are. The windows version of inttypes seem to use different naming conventions. Otherwise, the included make file should work for you on Linux provided you have a recent version of gcc. Do note that most of the work was done on Arch, so my gcc 
version probably differs from yours. This is rarely an issue with C but could pose some problems.
