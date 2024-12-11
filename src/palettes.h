#pragma once

#include "structs.h"

// === Палитры ===

// Cyberpunk
static ColorPoint CYBERPUNK_PALETTE[] = {
    {0,   3,  6,  72},
    {38,  12, 50, 188},
    {109, 217, 35,  1},
    {135, 242, 175, 12},
    {178, 161, 32, 87},
    {255,  24,  6, 108}
};
static int CYBERPUNK_PALETTE_SIZE = 
    sizeof(CYBERPUNK_PALETTE) / sizeof(ColorPoint);

// Sunset
static ColorPoint SUNSET_PALETTE[] = {
    {0, 120, 0, 0},
    {22, 179, 22, 0},
    {51, 255, 104, 0},
    {85, 167, 22, 18},
    {135, 100, 0, 103},
    {198, 16, 0, 130},
    {255, 0, 0, 160}
};
static int SUNSET_PALETTE_SIZE = 
    sizeof(SUNSET_PALETTE) / sizeof(ColorPoint);

// Optimus
static ColorPoint OPTIMUS_PALETTE[] = {
    {0, 5, 16, 18},
    {25, 5, 16, 18},
    {51, 7, 25, 39},
    {76, 8, 38, 71},
    {102, 64, 99, 106},
    {127, 194, 189, 151},
    {153, 182, 63, 42},
    {178, 167, 6, 2},
    {204, 100, 3, 1},
    {229, 53, 1, 1},
    {255, 53, 1, 1}
};
static int OPTIMUS_PALETTE_SIZE = 
    sizeof(OPTIMUS_PALETTE) / sizeof(ColorPoint);

// Warm
static ColorPoint WARM_PALETTE[] = {
    {0, 252, 252, 172},
    {25, 239, 255, 61},
    {53, 247, 45, 17},
    {76, 197, 82, 19},
    {96, 239, 255, 61},
    {124, 83, 4, 1},
    {153, 247, 45, 17},
    {214, 23, 15, 17},
    {255, 1, 1, 1}
};
static int WARM_PALETTE_SIZE = 
    sizeof(WARM_PALETTE) / sizeof(ColorPoint);

// Cold
static ColorPoint COLD_PALETTE[] = {
    {0, 66, 186, 192},
    {43, 1, 22, 71},
    {79, 2, 104, 142},
    {117, 66, 186, 192},
    {147, 2, 104, 142},
    {186, 1, 22, 71},
    {224, 2, 104, 142},
    {255, 4, 27, 28}
};
static int COLD_PALETTE_SIZE = 
    sizeof(COLD_PALETTE) / sizeof(ColorPoint);

// Hot
static ColorPoint HOT_PALETTE[] = {
    {0, 157, 21, 2},
    {35, 229, 244, 16},
    {73, 255, 44, 7},
    {107, 142, 7, 1},
    {153, 229, 244, 16},
    {206, 142, 7, 1},
    {255, 135, 36, 0}
};
static int HOT_PALETTE_SIZE = 
    sizeof(HOT_PALETTE) / sizeof(ColorPoint);

// Pink
static ColorPoint PINK_PALETTE[] = {
    {0, 249, 32, 145},
    {28, 208, 1, 7},
    {43, 249, 1, 19},
    {56, 126, 152, 10},
    {73, 234, 23, 84},
    {89, 224, 45, 119},
    {107, 232, 127, 158},
    {127, 244, 13, 89},
    {150, 188, 6, 52},
    {175, 177, 70, 14},
    {221, 194, 1, 8},
    {255, 112, 0, 1}
};
static int PINK_PALETTE_SIZE = 
    sizeof(PINK_PALETTE) / sizeof(ColorPoint);

// Comfy
static ColorPoint COMFY_PALETTE[] = {
    {0, 255, 255, 45},
    {43, 208, 93, 1},
    {137, 224, 1, 242},
    {181, 159, 1, 29},
    {255, 63, 4, 68}
};
static int COMFY_PALETTE_SIZE =
    sizeof(COMFY_PALETTE) / sizeof(ColorPoint);

// Girl
static ColorPoint GIRL_PALETTE[] = {
    {0, 103, 1, 10},
    {33, 109, 1, 12},
    {76, 159, 5, 48},
    {119, 175, 55, 103},
    {127, 175, 55, 103},
    {178, 159, 5, 48},
    {221, 109, 1, 12},
    {255, 103, 1, 10}
};
static int GIRL_PALETTE_SIZE =
    sizeof(GIRL_PALETTE) / sizeof(ColorPoint);

// Christmas
static ColorPoint CHRISTMAS_PALETTE[] = {
    {0, 0, 12, 0},
    {40, 0, 55, 0},
    {66, 1, 117, 2},
    {77, 1, 84, 1},
    {81, 0, 55, 0},
    {119, 0, 12, 0},
    {153, 42, 0, 0},
    {181, 121, 0, 0},
    {204, 255, 12, 8},
    {224, 121, 0, 0},
    {244, 42, 0, 0},
    {255, 42, 0, 0}
};
static int CHRISTMAS_PALETTE_SIZE =
    sizeof(CHRISTMAS_PALETTE) / sizeof(ColorPoint);

// Acid
static ColorPoint ACID_PALETTE[] = {
    {0, 0, 12, 0},
    {61, 153, 239, 112},
    {127, 0, 12, 0},
    {165, 106, 239, 2},
    {196, 167, 229, 71},
    {229, 106, 239, 2},
    {255, 0, 12, 0}
};
static int ACID_PALETTE_SIZE =
    sizeof(ACID_PALETTE) / sizeof(ColorPoint);

// Smoke
static ColorPoint SMOKE_PALETTE[] = {
    {0, 0, 0, 0},
    {12, 1, 1, 3},
    {53, 8, 1, 22},
    {80, 4, 6, 89},
    {119, 2, 25, 216},
    {145, 7, 10, 99},
    {186, 15, 2, 31},
    {233, 2, 1, 5},
    {255, 0, 0, 0}
};
static int SMOKE_PALETTE_SIZE =
    sizeof(SMOKE_PALETTE) / sizeof(ColorPoint);

// Aurora
static ColorPoint AURORA_PALETTE[] = {
    {0, 17, 177, 13},
    {64, 121, 242, 5},
    {128, 25, 173, 121},
    {192, 250, 77, 127},
    {255, 171, 101, 221}
};
static int AURORA_PALETTE_SIZE =
    sizeof(AURORA_PALETTE) / sizeof(ColorPoint);

// RedWhite
static ColorPoint REDWHITE_PALETTE[] = {
    {0, 255, 0, 0},
    {25, 255, 255, 255},
    {51, 255, 0, 0},
    {76, 255, 255, 255},
    {102, 255, 0, 0},
    {127, 255, 255, 255},
    {153, 255, 0, 0},
    {178, 255, 255, 255},
    {204, 255, 0, 0},
    {229, 255, 255, 255},
    {255, 255, 0, 0}
};
static int REDWHITE_PALETTE_SIZE =
    sizeof(REDWHITE_PALETTE) / sizeof(ColorPoint);

// Ocean
static ColorPoint OCEAN_PALETTE[] = {
    {0, 52, 152, 219}, // rgb(52, 152, 219)
    {64, 0, 0, 0},
    {128, 155, 89, 182}, // rgb(155, 89, 182)
    {192, 0, 0, 0},
    {255, 52, 152, 219} // rgb(52, 152, 219)
};
static int OCEAN_PALETTE_SIZE =
    sizeof(OCEAN_PALETTE) / sizeof(ColorPoint);

// Fog
static ColorPoint FOG_PALETTE[] = {
    {0, 25, 30, 15},
    {64, 10, 20, 35},
    {128, 25, 30, 15},
    {192, 10, 20, 35},
    {255, 25, 30, 15},
};
static int FOG_PALETTE_SIZE =
    sizeof(FOG_PALETTE) / sizeof(ColorPoint);