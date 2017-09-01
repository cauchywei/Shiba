//
// Created by cauchywei on 2017/8/20.
//

#ifndef SHIBA_FILEUTIL_H
#define SHIBA_FILEUTIL_H


#include <fstream>
#include <streambuf>
#include <string>

namespace shiba {
    namespace utils {
        void readFile(const std::string &path,std::string& content);
    }
}


#endif //SHIBA_FILEUTIL_H
