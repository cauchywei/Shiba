//
// Created by cauchywei on 2017/8/17.
//

#ifndef SHIBA_SHIBATYPE_H
#define SHIBA_SHIBATYPE_H

#include "../utils/Interface.h"
#define sint int


namespace shiba {

    namespace common {

        struct Point {
            sint x, y;

            Point(sint x, sint y) : x(x), y(y) {}

            bool operator==(const Point &rhs) const {
                return x == rhs.x &&
                       y == rhs.y;
            }

            bool operator!=(const Point &rhs) const {
                return !(rhs == *this);
            }
        };

        struct Size {
            int width, height;

            Size(sint x, sint y) : width(x), height(y) {}

            bool operator==(const Size &rhs) const {
                return width == rhs.width &&
                       height == rhs.height;
            }

            bool operator!=(const Size &rhs) const {
                return !(rhs == *this);
            }
        };


    }
}


#endif //SHIBA_SHIBATYPE_H
