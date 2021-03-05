#ifndef CGL_TEXTURE_H
#define CGL_TEXTURE_H

#include <memory>
#include <GL/glew.h>
#include <string>

namespace cgl {

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class ImproperTexParameter: public std::exception {
    std::string _class;
    std::string _type;
public:
    ImproperTexParameter(std::string className, std::string errorType) :
            _class(className), _type(errorType) {
    }

    virtual const char* what() const throw ();
};

class Texture {
protected:
    GLuint id;
    GLenum target;

    GLenum _format;
    GLint _level, _width, _height, _channels;
public:
    Texture();

    TexturePtr New() {
        return std::make_shared<Texture>();
    }

    virtual ~Texture();

    GLuint GetID() {
        return id;
    }

    void SetID(GLuint ID) {
        id = ID;
    }

    void BindTextureLocation(int loc);
    void BindImageTexture(int loc, bool layered, int layer, GLenum access);
    void Bind();
};

}

#endif
