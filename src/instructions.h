#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
#include <inttypes.h>
#include "disassemble.h"

enum data_type
{
    NONE, //Instruction is not followed by data or an address.
    d8,   //Instruction is followed by immediate 8 bit data
    d16,  //Instruction is followed by immediate 16bit data. Don't forget to shift the bits!
    a8,  //Instruction is followed by 8 bit unsigned data. Added to $FF00 in certain instructions.
    a16, //Instruction is followed by 16bit address
    r8  //Instruction is followed by 8 bit signed data, which is added to the program counter.
};

typedef struct instruction
{
    char mnmemonic[16];
    uint8_t op_code;
    int length;
    int d_type;
    char flags[4];
    char cycles[4];
} instruction;




// const struct instruction instructions[512] =
//     {
//         [0] = {"NOP", 0x0, 1},
//         [1] = {"LD BC,d16", 0x1, 3},
//         [2] = {"LD (BC),A", 0x2, 1},
//         [3] = {"UNDEFINED", -1, 0},
//         [4] = {"UNDEFINED", -1, 0},
//         [5] = {"UNDEFINED", -1, 0},
//         [6] = {"UNDEFINED", -1, 0},
//         [7] = {"UNDEFINED", -1, 0},
//         [8] = {"UNDEFINED", -1, 0},
//         [9] = {"UNDEFINED", -1, 0},
//         [10] = {"UNDEFINED", -1, 0},
//         [11] = {"UNDEFINED", -1, 0},
//         [12] = {"UNDEFINED", -1, 0},
//         [13] = {"UNDEFINED", -1, 0},
//         [14] = {"UNDEFINED", -1, 0},
//         [15] = {"UNDEFINED", -1, 0},
//         [16] = {"UNDEFINED", -1, 0},
//         [17] = {"UNDEFINED", -1, 0},
//         [18] = {"UNDEFINED", -1, 0},
//         [19] = {"UNDEFINED", -1, 0},
//         [20] = {"UNDEFINED", -1, 0},
//         [21] = {"UNDEFINED", -1, 0},
//         [22] = {"UNDEFINED", -1, 0},
//         [23] = {"UNDEFINED", -1, 0},
//         [24] = {"UNDEFINED", -1, 0},
//         [25] = {"UNDEFINED", -1, 0},
//         [26] = {"UNDEFINED", -1, 0},
//         [27] = {"UNDEFINED", -1, 0},
//         [28] = {"UNDEFINED", -1, 0},
//         [29] = {"UNDEFINED", -1, 0},
//         [30] = {"UNDEFINED", -1, 0},
//         [31] = {"UNDEFINED", -1, 0},
//         [32] = {"UNDEFINED", -1, 0},
//         [33] = {"UNDEFINED", -1, 0},
//         [34] = {"UNDEFINED", -1, 0},
//         [35] = {"UNDEFINED", -1, 0},
//         [36] = {"UNDEFINED", -1, 0},
//         [37] = {"UNDEFINED", -1, 0},
//         [38] = {"UNDEFINED", -1, 0},
//         [39] = {"UNDEFINED", -1, 0},
//         [40] = {"UNDEFINED", -1, 0},
//         [41] = {"UNDEFINED", -1, 0},
//         [42] = {"UNDEFINED", -1, 0},
//         [43] = {"UNDEFINED", -1, 0},
//         [44] = {"UNDEFINED", -1, 0},
//         [45] = {"UNDEFINED", -1, 0},
//         [46] = {"UNDEFINED", -1, 0},
//         [47] = {"UNDEFINED", -1, 0},
//         [48] = {"UNDEFINED", -1, 0},
//         [49] = {"UNDEFINED", -1, 0},
//         [50] = {"UNDEFINED", -1, 0},
//         [51] = {"UNDEFINED", -1, 0},
//         [52] = {"UNDEFINED", -1, 0},
//         [53] = {"UNDEFINED", -1, 0},
//         [54] = {"UNDEFINED", -1, 0},
//         [55] = {"UNDEFINED", -1, 0},
//         [56] = {"UNDEFINED", -1, 0},
//         [57] = {"UNDEFINED", -1, 0},
//         [58] = {"UNDEFINED", -1, 0},
//         [59] = {"UNDEFINED", -1, 0},
//         [60] = {"UNDEFINED", -1, 0},
//         [61] = {"UNDEFINED", -1, 0},
//         [62] = {"UNDEFINED", -1, 0},
//         [63] = {"UNDEFINED", -1, 0},
//         [64] = {"UNDEFINED", -1, 0},
//         [65] = {"UNDEFINED", -1, 0},
//         [66] = {"UNDEFINED", -1, 0},
//         [67] = {"UNDEFINED", -1, 0},
//         [68] = {"UNDEFINED", -1, 0},
//         [69] = {"UNDEFINED", -1, 0},
//         [70] = {"UNDEFINED", -1, 0},
//         [71] = {"UNDEFINED", -1, 0},
//         [72] = {"UNDEFINED", -1, 0},
//         [73] = {"UNDEFINED", -1, 0},
//         [74] = {"UNDEFINED", -1, 0},
//         [75] = {"UNDEFINED", -1, 0},
//         [76] = {"UNDEFINED", -1, 0},
//         [77] = {"UNDEFINED", -1, 0},
//         [78] = {"UNDEFINED", -1, 0},
//         [79] = {"UNDEFINED", -1, 0},
//         [80] = {"UNDEFINED", -1, 0},
//         [81] = {"UNDEFINED", -1, 0},
//         [82] = {"UNDEFINED", -1, 0},
//         [83] = {"UNDEFINED", -1, 0},
//         [84] = {"UNDEFINED", -1, 0},
//         [85] = {"UNDEFINED", -1, 0},
//         [86] = {"UNDEFINED", -1, 0},
//         [87] = {"UNDEFINED", -1, 0},
//         [88] = {"UNDEFINED", -1, 0},
//         [89] = {"UNDEFINED", -1, 0},
//         [90] = {"UNDEFINED", -1, 0},
//         [91] = {"UNDEFINED", -1, 0},
//         [92] = {"UNDEFINED", -1, 0},
//         [93] = {"UNDEFINED", -1, 0},
//         [94] = {"UNDEFINED", -1, 0},
//         [95] = {"UNDEFINED", -1, 0},
//         [96] = {"UNDEFINED", -1, 0},
//         [97] = {"UNDEFINED", -1, 0},
//         [98] = {"UNDEFINED", -1, 0},
//         [99] = {"UNDEFINED", -1, 0},
//         [100] = {"UNDEFINED", -1, 0},
//         [101] = {"UNDEFINED", -1, 0},
//         [102] = {"UNDEFINED", -1, 0},
//         [103] = {"UNDEFINED", -1, 0},
//         [104] = {"UNDEFINED", -1, 0},
//         [105] = {"UNDEFINED", -1, 0},
//         [106] = {"UNDEFINED", -1, 0},
//         [107] = {"UNDEFINED", -1, 0},
//         [108] = {"UNDEFINED", -1, 0},
//         [109] = {"UNDEFINED", -1, 0},
//         [110] = {"UNDEFINED", -1, 0},
//         [111] = {"UNDEFINED", -1, 0},
//         [112] = {"UNDEFINED", -1, 0},
//         [113] = {"UNDEFINED", -1, 0},
//         [114] = {"UNDEFINED", -1, 0},
//         [115] = {"UNDEFINED", -1, 0},
//         [116] = {"UNDEFINED", -1, 0},
//         [117] = {"UNDEFINED", -1, 0},
//         [118] = {"UNDEFINED", -1, 0},
//         [119] = {"UNDEFINED", -1, 0},
//         [120] = {"UNDEFINED", -1, 0},
//         [121] = {"UNDEFINED", -1, 0},
//         [122] = {"UNDEFINED", -1, 0},
//         [123] = {"UNDEFINED", -1, 0},
//         [124] = {"UNDEFINED", -1, 0},
//         [125] = {"UNDEFINED", -1, 0},
//         [126] = {"UNDEFINED", -1, 0},
//         [127] = {"UNDEFINED", -1, 0},
//         [128] = {"UNDEFINED", -1, 0},
//         [129] = {"UNDEFINED", -1, 0},
//         [130] = {"UNDEFINED", -1, 0},
//         [131] = {"UNDEFINED", -1, 0},
//         [132] = {"UNDEFINED", -1, 0},
//         [133] = {"UNDEFINED", -1, 0},
//         [134] = {"UNDEFINED", -1, 0},
//         [135] = {"UNDEFINED", -1, 0},
//         [136] = {"UNDEFINED", -1, 0},
//         [137] = {"UNDEFINED", -1, 0},
//         [138] = {"UNDEFINED", -1, 0},
//         [139] = {"UNDEFINED", -1, 0},
//         [140] = {"UNDEFINED", -1, 0},
//         [141] = {"UNDEFINED", -1, 0},
//         [142] = {"UNDEFINED", -1, 0},
//         [143] = {"UNDEFINED", -1, 0},
//         [144] = {"UNDEFINED", -1, 0},
//         [145] = {"UNDEFINED", -1, 0},
//         [146] = {"UNDEFINED", -1, 0},
//         [147] = {"UNDEFINED", -1, 0},
//         [148] = {"UNDEFINED", -1, 0},
//         [149] = {"UNDEFINED", -1, 0},
//         [150] = {"UNDEFINED", -1, 0},
//         [151] = {"UNDEFINED", -1, 0},
//         [152] = {"UNDEFINED", -1, 0},
//         [153] = {"UNDEFINED", -1, 0},
//         [154] = {"UNDEFINED", -1, 0},
//         [155] = {"UNDEFINED", -1, 0},
//         [156] = {"UNDEFINED", -1, 0},
//         [157] = {"UNDEFINED", -1, 0},
//         [158] = {"UNDEFINED", -1, 0},
//         [159] = {"UNDEFINED", -1, 0},
//         [160] = {"UNDEFINED", -1, 0},
//         [161] = {"UNDEFINED", -1, 0},
//         [162] = {"UNDEFINED", -1, 0},
//         [163] = {"UNDEFINED", -1, 0},
//         [164] = {"UNDEFINED", -1, 0},
//         [165] = {"UNDEFINED", -1, 0},
//         [166] = {"UNDEFINED", -1, 0},
//         [167] = {"UNDEFINED", -1, 0},
//         [168] = {"UNDEFINED", -1, 0},
//         [169] = {"UNDEFINED", -1, 0},
//         [170] = {"UNDEFINED", -1, 0},
//         [171] = {"UNDEFINED", -1, 0},
//         [172] = {"UNDEFINED", -1, 0},
//         [173] = {"UNDEFINED", -1, 0},
//         [174] = {"UNDEFINED", -1, 0},
//         [175] = {"UNDEFINED", -1, 0},
//         [176] = {"UNDEFINED", -1, 0},
//         [177] = {"UNDEFINED", -1, 0},
//         [178] = {"UNDEFINED", -1, 0},
//         [179] = {"UNDEFINED", -1, 0},
//         [180] = {"UNDEFINED", -1, 0},
//         [181] = {"UNDEFINED", -1, 0},
//         [182] = {"UNDEFINED", -1, 0},
//         [183] = {"UNDEFINED", -1, 0},
//         [184] = {"UNDEFINED", -1, 0},
//         [185] = {"UNDEFINED", -1, 0},
//         [186] = {"UNDEFINED", -1, 0},
//         [187] = {"UNDEFINED", -1, 0},
//         [188] = {"UNDEFINED", -1, 0},
//         [189] = {"UNDEFINED", -1, 0},
//         [190] = {"UNDEFINED", -1, 0},
//         [191] = {"UNDEFINED", -1, 0},
//         [192] = {"UNDEFINED", -1, 0},
//         [193] = {"UNDEFINED", -1, 0},
//         [194] = {"UNDEFINED", -1, 0},
//         [195] = {"UNDEFINED", -1, 0},
//         [196] = {"UNDEFINED", -1, 0},
//         [197] = {"UNDEFINED", -1, 0},
//         [198] = {"UNDEFINED", -1, 0},
//         [199] = {"UNDEFINED", -1, 0},
//         [200] = {"UNDEFINED", -1, 0},
//         [201] = {"UNDEFINED", -1, 0},
//         [202] = {"UNDEFINED", -1, 0},
//         [203] = {"UNDEFINED", -1, 0},
//         [204] = {"UNDEFINED", -1, 0},
//         [205] = {"UNDEFINED", -1, 0},
//         [206] = {"UNDEFINED", -1, 0},
//         [207] = {"UNDEFINED", -1, 0},
//         [208] = {"UNDEFINED", -1, 0},
//         [209] = {"UNDEFINED", -1, 0},
//         [210] = {"UNDEFINED", -1, 0},
//         [211] = {"UNDEFINED", -1, 0},
//         [212] = {"UNDEFINED", -1, 0},
//         [213] = {"UNDEFINED", -1, 0},
//         [214] = {"UNDEFINED", -1, 0},
//         [215] = {"UNDEFINED", -1, 0},
//         [216] = {"UNDEFINED", -1, 0},
//         [217] = {"UNDEFINED", -1, 0},
//         [218] = {"UNDEFINED", -1, 0},
//         [219] = {"UNDEFINED", -1, 0},
//         [220] = {"UNDEFINED", -1, 0},
//         [221] = {"UNDEFINED", -1, 0},
//         [222] = {"UNDEFINED", -1, 0},
//         [223] = {"UNDEFINED", -1, 0},
//         [224] = {"UNDEFINED", -1, 0},
//         [225] = {"UNDEFINED", -1, 0},
//         [226] = {"UNDEFINED", -1, 0},
//         [227] = {"UNDEFINED", -1, 0},
//         [228] = {"UNDEFINED", -1, 0},
//         [229] = {"UNDEFINED", -1, 0},
//         [230] = {"UNDEFINED", -1, 0},
//         [231] = {"UNDEFINED", -1, 0},
//         [232] = {"UNDEFINED", -1, 0},
//         [233] = {"UNDEFINED", -1, 0},
//         [234] = {"UNDEFINED", -1, 0},
//         [235] = {"UNDEFINED", -1, 0},
//         [236] = {"UNDEFINED", -1, 0},
//         [237] = {"UNDEFINED", -1, 0},
//         [238] = {"UNDEFINED", -1, 0},
//         [239] = {"UNDEFINED", -1, 0},
//         [240] = {"UNDEFINED", -1, 0},
//         [241] = {"UNDEFINED", -1, 0},
//         [242] = {"UNDEFINED", -1, 0},
//         [243] = {"UNDEFINED", -1, 0},
//         [244] = {"UNDEFINED", -1, 0},
//         [245] = {"UNDEFINED", -1, 0},
//         [246] = {"UNDEFINED", -1, 0},
//         [247] = {"UNDEFINED", -1, 0},
//         [248] = {"UNDEFINED", -1, 0},
//         [249] = {"UNDEFINED", -1, 0},
//         [250] = {"UNDEFINED", -1, 0},
//         [251] = {"UNDEFINED", -1, 0},
//         [252] = {"UNDEFINED", -1, 0},
//         [253] = {"UNDEFINED", -1, 0},
//         [254] = {"UNDEFINED", -1, 0},
//         [255] = {"UNDEFINED", -1, 0},
//         [256] = {"UNDEFINED", -1, 0},
//         [257] = {"UNDEFINED", -1, 0},
//         [258] = {"UNDEFINED", -1, 0},
//         [259] = {"UNDEFINED", -1, 0},
//         [260] = {"UNDEFINED", -1, 0},
//         [261] = {"UNDEFINED", -1, 0},
//         [262] = {"UNDEFINED", -1, 0},
//         [263] = {"UNDEFINED", -1, 0},
//         [264] = {"UNDEFINED", -1, 0},
//         [265] = {"UNDEFINED", -1, 0},
//         [266] = {"UNDEFINED", -1, 0},
//         [267] = {"UNDEFINED", -1, 0},
//         [268] = {"UNDEFINED", -1, 0},
//         [269] = {"UNDEFINED", -1, 0},
//         [270] = {"UNDEFINED", -1, 0},
//         [271] = {"UNDEFINED", -1, 0},
//         [272] = {"UNDEFINED", -1, 0},
//         [273] = {"UNDEFINED", -1, 0},
//         [274] = {"UNDEFINED", -1, 0},
//         [275] = {"UNDEFINED", -1, 0},
//         [276] = {"UNDEFINED", -1, 0},
//         [277] = {"UNDEFINED", -1, 0},
//         [278] = {"UNDEFINED", -1, 0},
//         [279] = {"UNDEFINED", -1, 0},
//         [280] = {"UNDEFINED", -1, 0},
//         [281] = {"UNDEFINED", -1, 0},
//         [282] = {"UNDEFINED", -1, 0},
//         [283] = {"UNDEFINED", -1, 0},
//         [284] = {"UNDEFINED", -1, 0},
//         [285] = {"UNDEFINED", -1, 0},
//         [286] = {"UNDEFINED", -1, 0},
//         [287] = {"UNDEFINED", -1, 0},
//         [288] = {"UNDEFINED", -1, 0},
//         [289] = {"UNDEFINED", -1, 0},
//         [290] = {"UNDEFINED", -1, 0},
//         [291] = {"UNDEFINED", -1, 0},
//         [292] = {"UNDEFINED", -1, 0},
//         [293] = {"UNDEFINED", -1, 0},
//         [294] = {"UNDEFINED", -1, 0},
//         [295] = {"UNDEFINED", -1, 0},
//         [296] = {"UNDEFINED", -1, 0},
//         [297] = {"UNDEFINED", -1, 0},
//         [298] = {"UNDEFINED", -1, 0},
//         [299] = {"UNDEFINED", -1, 0},
//         [300] = {"UNDEFINED", -1, 0},
//         [301] = {"UNDEFINED", -1, 0},
//         [302] = {"UNDEFINED", -1, 0},
//         [303] = {"UNDEFINED", -1, 0},
//         [304] = {"UNDEFINED", -1, 0},
//         [305] = {"UNDEFINED", -1, 0},
//         [306] = {"UNDEFINED", -1, 0},
//         [307] = {"UNDEFINED", -1, 0},
//         [308] = {"UNDEFINED", -1, 0},
//         [309] = {"UNDEFINED", -1, 0},
//         [310] = {"UNDEFINED", -1, 0},
//         [311] = {"UNDEFINED", -1, 0},
//         [312] = {"UNDEFINED", -1, 0},
//         [313] = {"UNDEFINED", -1, 0},
//         [314] = {"UNDEFINED", -1, 0},
//         [315] = {"UNDEFINED", -1, 0},
//         [316] = {"UNDEFINED", -1, 0},
//         [317] = {"UNDEFINED", -1, 0},
//         [318] = {"UNDEFINED", -1, 0},
//         [319] = {"UNDEFINED", -1, 0},
//         [320] = {"UNDEFINED", -1, 0},
//         [321] = {"UNDEFINED", -1, 0},
//         [322] = {"UNDEFINED", -1, 0},
//         [323] = {"UNDEFINED", -1, 0},
//         [324] = {"UNDEFINED", -1, 0},
//         [325] = {"UNDEFINED", -1, 0},
//         [326] = {"UNDEFINED", -1, 0},
//         [327] = {"UNDEFINED", -1, 0},
//         [328] = {"UNDEFINED", -1, 0},
//         [329] = {"UNDEFINED", -1, 0},
//         [330] = {"UNDEFINED", -1, 0},
//         [331] = {"UNDEFINED", -1, 0},
//         [332] = {"UNDEFINED", -1, 0},
//         [333] = {"UNDEFINED", -1, 0},
//         [334] = {"UNDEFINED", -1, 0},
//         [335] = {"UNDEFINED", -1, 0},
//         [336] = {"UNDEFINED", -1, 0},
//         [337] = {"UNDEFINED", -1, 0},
//         [338] = {"UNDEFINED", -1, 0},
//         [339] = {"UNDEFINED", -1, 0},
//         [340] = {"UNDEFINED", -1, 0},
//         [341] = {"UNDEFINED", -1, 0},
//         [342] = {"UNDEFINED", -1, 0},
//         [343] = {"UNDEFINED", -1, 0},
//         [344] = {"UNDEFINED", -1, 0},
//         [345] = {"UNDEFINED", -1, 0},
//         [346] = {"UNDEFINED", -1, 0},
//         [347] = {"UNDEFINED", -1, 0},
//         [348] = {"UNDEFINED", -1, 0},
//         [349] = {"UNDEFINED", -1, 0},
//         [350] = {"UNDEFINED", -1, 0},
//         [351] = {"UNDEFINED", -1, 0},
//         [352] = {"UNDEFINED", -1, 0},
//         [353] = {"UNDEFINED", -1, 0},
//         [354] = {"UNDEFINED", -1, 0},
//         [355] = {"UNDEFINED", -1, 0},
//         [356] = {"UNDEFINED", -1, 0},
//         [357] = {"UNDEFINED", -1, 0},
//         [358] = {"UNDEFINED", -1, 0},
//         [359] = {"UNDEFINED", -1, 0},
//         [360] = {"UNDEFINED", -1, 0},
//         [361] = {"UNDEFINED", -1, 0},
//         [362] = {"UNDEFINED", -1, 0},
//         [363] = {"UNDEFINED", -1, 0},
//         [364] = {"UNDEFINED", -1, 0},
//         [365] = {"UNDEFINED", -1, 0},
//         [366] = {"UNDEFINED", -1, 0},
//         [367] = {"UNDEFINED", -1, 0},
//         [368] = {"UNDEFINED", -1, 0},
//         [369] = {"UNDEFINED", -1, 0},
//         [370] = {"UNDEFINED", -1, 0},
//         [371] = {"UNDEFINED", -1, 0},
//         [372] = {"UNDEFINED", -1, 0},
//         [373] = {"UNDEFINED", -1, 0},
//         [374] = {"UNDEFINED", -1, 0},
//         [375] = {"UNDEFINED", -1, 0},
//         [376] = {"UNDEFINED", -1, 0},
//         [377] = {"UNDEFINED", -1, 0},
//         [378] = {"UNDEFINED", -1, 0},
//         [379] = {"UNDEFINED", -1, 0},
//         [380] = {"UNDEFINED", -1, 0},
//         [381] = {"UNDEFINED", -1, 0},
//         [382] = {"UNDEFINED", -1, 0},
//         [383] = {"UNDEFINED", -1, 0},
//         [384] = {"UNDEFINED", -1, 0},
//         [385] = {"UNDEFINED", -1, 0},
//         [386] = {"UNDEFINED", -1, 0},
//         [387] = {"UNDEFINED", -1, 0},
//         [388] = {"UNDEFINED", -1, 0},
//         [389] = {"UNDEFINED", -1, 0},
//         [390] = {"UNDEFINED", -1, 0},
//         [391] = {"UNDEFINED", -1, 0},
//         [392] = {"UNDEFINED", -1, 0},
//         [393] = {"UNDEFINED", -1, 0},
//         [394] = {"UNDEFINED", -1, 0},
//         [395] = {"UNDEFINED", -1, 0},
//         [396] = {"UNDEFINED", -1, 0},
//         [397] = {"UNDEFINED", -1, 0},
//         [398] = {"UNDEFINED", -1, 0},
//         [399] = {"UNDEFINED", -1, 0},
//         [400] = {"UNDEFINED", -1, 0},
//         [401] = {"UNDEFINED", -1, 0},
//         [402] = {"UNDEFINED", -1, 0},
//         [403] = {"UNDEFINED", -1, 0},
//         [404] = {"UNDEFINED", -1, 0},
//         [405] = {"UNDEFINED", -1, 0},
//         [406] = {"UNDEFINED", -1, 0},
//         [407] = {"UNDEFINED", -1, 0},
//         [408] = {"UNDEFINED", -1, 0},
//         [409] = {"UNDEFINED", -1, 0},
//         [410] = {"UNDEFINED", -1, 0},
//         [411] = {"UNDEFINED", -1, 0},
//         [412] = {"UNDEFINED", -1, 0},
//         [413] = {"UNDEFINED", -1, 0},
//         [414] = {"UNDEFINED", -1, 0},
//         [415] = {"UNDEFINED", -1, 0},
//         [416] = {"UNDEFINED", -1, 0},
//         [417] = {"UNDEFINED", -1, 0},
//         [418] = {"UNDEFINED", -1, 0},
//         [419] = {"UNDEFINED", -1, 0},
//         [420] = {"UNDEFINED", -1, 0},
//         [421] = {"UNDEFINED", -1, 0},
//         [422] = {"UNDEFINED", -1, 0},
//         [423] = {"UNDEFINED", -1, 0},
//         [424] = {"UNDEFINED", -1, 0},
//         [425] = {"UNDEFINED", -1, 0},
//         [426] = {"UNDEFINED", -1, 0},
//         [427] = {"UNDEFINED", -1, 0},
//         [428] = {"UNDEFINED", -1, 0},
//         [429] = {"UNDEFINED", -1, 0},
//         [430] = {"UNDEFINED", -1, 0},
//         [431] = {"UNDEFINED", -1, 0},
//         [432] = {"UNDEFINED", -1, 0},
//         [433] = {"UNDEFINED", -1, 0},
//         [434] = {"UNDEFINED", -1, 0},
//         [435] = {"UNDEFINED", -1, 0},
//         [436] = {"UNDEFINED", -1, 0},
//         [437] = {"UNDEFINED", -1, 0},
//         [438] = {"UNDEFINED", -1, 0},
//         [439] = {"UNDEFINED", -1, 0},
//         [440] = {"UNDEFINED", -1, 0},
//         [441] = {"UNDEFINED", -1, 0},
//         [442] = {"UNDEFINED", -1, 0},
//         [443] = {"UNDEFINED", -1, 0},
//         [444] = {"UNDEFINED", -1, 0},
//         [445] = {"UNDEFINED", -1, 0},
//         [446] = {"UNDEFINED", -1, 0},
//         [447] = {"UNDEFINED", -1, 0},
//         [448] = {"UNDEFINED", -1, 0},
//         [449] = {"UNDEFINED", -1, 0},
//         [450] = {"UNDEFINED", -1, 0},
//         [451] = {"UNDEFINED", -1, 0},
//         [452] = {"UNDEFINED", -1, 0},
//         [453] = {"UNDEFINED", -1, 0},
//         [454] = {"UNDEFINED", -1, 0},
//         [455] = {"UNDEFINED", -1, 0},
//         [456] = {"UNDEFINED", -1, 0},
//         [457] = {"UNDEFINED", -1, 0},
//         [458] = {"UNDEFINED", -1, 0},
//         [459] = {"UNDEFINED", -1, 0},
//         [460] = {"UNDEFINED", -1, 0},
//         [461] = {"UNDEFINED", -1, 0},
//         [462] = {"UNDEFINED", -1, 0},
//         [463] = {"UNDEFINED", -1, 0},
//         [464] = {"UNDEFINED", -1, 0},
//         [465] = {"UNDEFINED", -1, 0},
//         [466] = {"UNDEFINED", -1, 0},
//         [467] = {"UNDEFINED", -1, 0},
//         [468] = {"UNDEFINED", -1, 0},
//         [469] = {"UNDEFINED", -1, 0},
//         [470] = {"UNDEFINED", -1, 0},
//         [471] = {"UNDEFINED", -1, 0},
//         [472] = {"UNDEFINED", -1, 0},
//         [473] = {"UNDEFINED", -1, 0},
//         [474] = {"UNDEFINED", -1, 0},
//         [475] = {"UNDEFINED", -1, 0},
//         [476] = {"UNDEFINED", -1, 0},
//         [477] = {"UNDEFINED", -1, 0},
//         [478] = {"UNDEFINED", -1, 0},
//         [479] = {"UNDEFINED", -1, 0},
//         [480] = {"UNDEFINED", -1, 0},
//         [481] = {"UNDEFINED", -1, 0},
//         [482] = {"UNDEFINED", -1, 0},
//         [483] = {"UNDEFINED", -1, 0},
//         [484] = {"UNDEFINED", -1, 0},
//         [485] = {"UNDEFINED", -1, 0},
//         [486] = {"UNDEFINED", -1, 0},
//         [487] = {"UNDEFINED", -1, 0},
//         [488] = {"UNDEFINED", -1, 0},
//         [489] = {"UNDEFINED", -1, 0},
//         [490] = {"UNDEFINED", -1, 0},
//         [491] = {"UNDEFINED", -1, 0},
//         [492] = {"UNDEFINED", -1, 0},
//         [493] = {"UNDEFINED", -1, 0},
//         [494] = {"UNDEFINED", -1, 0},
//         [495] = {"UNDEFINED", -1, 0},
//         [496] = {"UNDEFINED", -1, 0},
//         [497] = {"UNDEFINED", -1, 0},
//         [498] = {"UNDEFINED", -1, 0},
//         [499] = {"UNDEFINED", -1, 0},
//         [500] = {"UNDEFINED", -1, 0},
//         [501] = {"UNDEFINED", -1, 0},
//         [502] = {"UNDEFINED", -1, 0},
//         [503] = {"UNDEFINED", -1, 0},
//         [504] = {"UNDEFINED", -1, 0},
//         [505] = {"UNDEFINED", -1, 0},
//         [506] = {"UNDEFINED", -1, 0},
//         [507] = {"UNDEFINED", -1, 0},
//         [508] = {"UNDEFINED", -1, 0},
//         [509] = {"UNDEFINED", -1, 0},
//         [510] = {"UNDEFINED", -1, 0},
//         [511] = {"UNDEFINED", -1, 0},
// };

    //

    // typedef enum
    // {//
    //     NOP,
    //     LD_BC_d16,
    //     LD_BC_A,
    //     INC_BC,
    //     INC_B,
    //     DEC_B,
    //     LD_B_d8,
    //     RLCA,
    //     LD_a16_SP,
    //     ADD_HL_BC,
    //     LD_A_BC,
    //     DEC_BC,
    //     INC_C,
    //     DEC_C,
    //     LD_C_d8,
    //     RRCA,
    //     STOP0,
    //     LD_DE_d16,
    //     LD_DE_A,
    //     INC_DE,
    //     INC_D,
    //     DEC_D,
    //     LD_D_d8,
    //     RLA,
    //     JR_r8,
    //     ADD_HL_DE,
    //     LD_A_DE,
    //     DEC_DE,
    //     INC_E,
    //     DEC_E,
    //     LD_E_d8,
    //     RRA,
    //     JR_NZ_r8,
    //     LD_HL_d16,
    //     LD_HLplus_A,
    //     INC_HL,
    //     INC_H,
    //     DEC_H,
    //     LD H,

    // }mnemonics;





#endif