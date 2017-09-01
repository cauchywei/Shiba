//
// Created by cauchywei on 2017/8/25.
//

#include <string>
#include "FileUtil.h"

void shiba::utils::readFile(const std::string &path, std::string &content) {
    std::ifstream t(path);
    content.assign((std::istreambuf_iterator<char>(t)),
                   (std::istreambuf_iterator<char>()));
}
