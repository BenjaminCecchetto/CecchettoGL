/*
 * Texture2D.h
 *
 *  Created on: Oct 28, 2013
 *      Author: cecchett
 */

#ifndef CGL_TEXTURE2D_H_
#define CGL_TEXTURE2D_H_

#include <GL/glew.h>
#include <memory>
#include "Texture.h"
#include "Image.h"
#include "../Utility/Random.h"

namespace cgl {

class Texture2D;
typedef std::shared_ptr<Texture2D> Texture2DPtr;

class Texture2D: public Texture {

public:
    Texture2D(int level, int internalFormat, int width, int height,
            int dataFormat, int dataType, void* data, int minFilter,
            int magFilter, int wrapS, int wrapT);

    Texture2D(int level, int internalFormat, int width, int height,
            int minFilter, int magFilter, int wrapS, int wrapT);

    //Create texture on GPU via an image
    static Texture2DPtr New(int level, int internalFormat,
            UnsignedByteImagePtr image, int minFilter, int magFilter, int wrapS,
            int wrapT);

    static Texture2DPtr New(int level, int internalFormat, FloatImagePtr image,
            int minFilter, int magFilter, int wrapS, int wrapT);

//Create texture on GPU with data specified
    static Texture2DPtr New(int level, int internalFormat, int width,
            int height, int dataFormat, int dataType, void* data, int minFilter,
            int magFilter, int wrapS, int wrapT) {
        return std::make_shared<Texture2D>(level, internalFormat, width, height,
                dataFormat, dataType, data, minFilter, magFilter, wrapS, wrapT);
    }

//Create texture on GPU with no data
    static Texture2DPtr New(int level, int internalFormat, int width,
            int height, int minFilter, int magFilter, int wrapS, int wrapT) {
        return std::make_shared<Texture2D>(level, internalFormat, width, height,
                minFilter, magFilter, wrapS, wrapT);
    }

    static Texture2DPtr NewRandom(int width, int height, int minFilter,
            int magFilter, int wrapS, int wrapT) {

        float* data = new float[width * height];
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                data[i + j * width] = Random::frand();
            }
        }

        Texture2DPtr tex = std::make_shared<Texture2D>(0, GL_R32F, width,
                height,
                GL_RED, GL_FLOAT, data, minFilter, magFilter, wrapS, wrapT);

        delete[] data;
        return tex;
    }

    UnsignedByteImagePtr GetImage();
    FloatImagePtr GetImageF();


};

}

#endif /* TEXTURE2D_H_ */
