//
// Created by cauchywei on 2017/8/18.
//

#ifndef SHIBA_LIST_H
#define SHIBA_LIST_H

#include <vector>
#include "Interface.h"

namespace shiba {
    template<typename T>
    class List : public Interface {
    public:
        inline int size() {
            return vector.size();
        }

        inline bool empty() {
            return vector.empty();
        }

        inline T &operator[](int index) {
            return vector[index];
        }

        inline void add(T &t) {
            vector.push_back(t);
        }

        bool remove(const T &t) {
            for (auto it = std::begin(vector); it != std::end(vector); it++) {
                if (*it == t) {
                    vector.erase(it);
                    return true;
                }
            }
            return false;
        }

        ~List() override {

        };

        bool contains(T &t) {
            for (auto it = std::begin(vector); it != std::end(vector); it++) {
                if (*it == t) {
                    return true;
                }
            }
            return false;
        }

    private:
        std::vector<T> vector;
    };

}

#endif //SHIBA_LIST_H
