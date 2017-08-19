//
// Created by cauchywei on 2017/8/16.
//

#ifndef DCRAFT_SINGLETON_H
#define DCRAFT_SINGLETON_H

template<typename T>
class Singleton<T> {
public:
    static T &get() {
        static T t;
        return t;
    }

private:
    Singleton() {}

};


#endif //DCRAFT_SINGLETON_H
