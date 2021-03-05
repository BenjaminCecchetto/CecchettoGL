#ifndef TEXT_RENDERER_H_
#define TEXT_RENDERER_H_

#include <glm.hpp>
#include <string>

namespace cgl {

class TextRenderer {
   static uint32_t s_fontSize;

public:
    
    static void RenderText(glm::vec2 screenPosition, std::string text);

    static uint32_t FontSize();
};

}
#endif
