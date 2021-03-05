/*
 * Texture3D.h
 *
 *  Created on: Oct 28, 2013
 *      Author: cecchett
 */

#ifndef CGL_TEXTURE3D_H_
#define CGL_TEXTURE3D_H_

#include <GL/glew.h>
#include <memory>
#include "Texture.h"

namespace cgl {

class Texture3D;
typedef std::shared_ptr<Texture3D> Texture3DPtr;

class Texture3D: public Texture {

public:
    Texture3D(int level, int internalFormat, int width, int height, int depth,
            int dataFormat, int dataType, void* data, int minFilter,
            int magFilter, int wrapS, int wrapT, int wrapR);

    Texture3DPtr New(int level, int internalFormat, int width, int height,
            int depth, int dataFormat, int dataType, void* data, int minFilter,
            int magFilter, int wrapS, int wrapT, int wrapR) {
        return std::make_shared<Texture3D>(level, internalFormat, width, height,
                depth, dataFormat, dataType, data, minFilter, magFilter, wrapS,
                wrapT, wrapR);
    }
};

}

#endif /* TEXTURE3D_H_ */
