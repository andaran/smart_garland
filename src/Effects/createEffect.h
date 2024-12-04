#pragma once

#include "Effect.h"
#include "../Strip/StripProcessor.h"

#include "Test/Test.h"
#include "Rainbow/Rainbow.h"
#include "Stripes/Stripes.h"
#include "Rain/Rain.h"
#include "PaletteEffect.h"

Effect * createEffect(StripProcessor & strip, String name);