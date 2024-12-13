#pragma once

#include <LittleFS.h>

#include "palettes.h"

#include "Effect.h"
#include "../Strip/StripProcessor.h"

#include "Test/Test.h"
#include "Rainbow/Rainbow.h"
#include "Stripes/Stripes.h"
#include "Rain/Rain.h"
#include "Palette/PaletteEffect.h"
#include "Animation/Animation.h"
#include "Color/Color.h"

Effect * createEffect(StripProcessor & strip, String name);