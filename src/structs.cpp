#include "structs.h"

Color::Color(byte r, byte g, byte b) : r(r), g(g), b(b) {};
Color::Color() : r(0), g(0), b(0) {};
Color::Color(Color & color) : r(color.r), g(color.g), b(color.b) {};