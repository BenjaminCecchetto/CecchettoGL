/*
 * FileLoader.cpp
 *
 *  Created on: Dec 16, 2013
 *      Author: root
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "FileLoader.h"

namespace cgl {

std::string FileLoader::FilenameToString(std::string filename) {
    std::string line;
    std::ifstream myfile(filename);
    std::stringstream ss;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {

            ss << line << '\n';
        }
        myfile.close();
        //std::cout << ss.str();
    } else
        std::cerr << "Unable to open file " << filename;

    return ss.str();
}
FileLoader::FileLoader(std::string filename) :
        _fileName(filename) {
    _fileContents = FilenameToString(filename);
}

}

