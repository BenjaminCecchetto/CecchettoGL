/*
 * FileLoader.h
 *
 *  Created on: Dec 16, 2013
 *      Author: root
 */

#ifndef CGL_FILELOADER_H_
#define CGL_FILELOADER_H_

#include <memory>
#include <string>

namespace cgl {

class FileLoader;
typedef std::shared_ptr<FileLoader> FileLoaderPtr;

class FileLoader {
    std::string _fileName;
    std::string _fileContents;
public:
    FileLoader(std::string filename);

    static std::string FilenameToString(std::string filename);

    static FileLoaderPtr New(std::string filename) {
        return std::make_shared<FileLoader>(filename);
    }
};

}

#endif /* FILELOADER_H_ */
