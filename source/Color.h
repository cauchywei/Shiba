//
// Created by cauchywei on 2017/8/16.
//

#ifndef DCRAFT_COLOR_H
#define DCRAFT_COLOR_H

namespace shiba {

    class Color {
    public:
        Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
        }

    public:
        float r, g, b, a;
    };

    static Color BLACK(0, 0, 0, 1);
    static Color WHITE(1, 1, 1, 1);
}
#endif //DCRAFT_COLOR_H
