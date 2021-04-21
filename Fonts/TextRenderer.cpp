#include "TextRenderer.h"

#include <GL/glew.h>
#include <SDL_ttf.h>

#include "../cgl.h"

namespace cgl {

uint32_t TextRenderer::s_fontSize = 24;

void TextRenderer::RenderText(glm::vec2 screenPosition, std::string text) {
  static bool ranonce = false;

  static FragmentShaderPtr textFragShader = nullptr;
  static VertexShaderPtr textVertShader = nullptr;
  static TTF_Font* font = nullptr;
  static RenderTexturePassPtr rtp = nullptr;

  static bool initTTF = false;
  if (!initTTF) {
    TTF_Init();
    initTTF = true;
  }

  if (!ranonce) {
    ranonce = true;
    std::string basePath = std::string(SDL_GetBasePath());
    std::string fontName = basePath + "data\\amaro-arial-bold.ttf";

    font = TTF_OpenFont(fontName.c_str(), s_fontSize);  // needs to be freed
    if (font == nullptr) {
      std::cout << "Cannot find font: " << fontName << std::endl;
      return;
    }

    auto fragShaderPath = basePath + "shaders/textFragment.glsl";
    auto vertShaderPath = basePath + "shaders/textVert.glsl";
    textFragShader = FragmentShader::NewFromFile(fragShaderPath);
    textVertShader = VertexShader::NewFromFile(vertShaderPath);
    rtp = RenderTexturePass::New(nullptr, textVertShader, textFragShader);
  }

  SDL_Color white = {255, 255, 255, 255};

  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), white);

  // Find the first power of two for OpenGL image
  int w = surface->w;
  int h = surface->h;

  // Create a surface to the correct size in RGB format, and copy the old image
  SDL_Surface* s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00,
                                        0x000000ff, 0xff000000);
  SDL_BlitSurface(surface, NULL, s, NULL);

  Texture2DPtr tex = Texture2D::New(
      0, GL_RGBA, w, h, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels,
      GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);

  rtp->AppendTexture(tex);
  rtp->GetProgram()->UniformVec2f("texPosition", screenPosition);
  rtp->GetProgram()->UniformVec2f("texSize", glm::vec2(w, h));
  rtp->Dispatch();

  rtp->ClearTextures();

  // Cleanup
  SDL_FreeSurface(s);
  SDL_FreeSurface(surface);
}

uint32_t TextRenderer::FontSize() { return s_fontSize; }

}  // namespace cgl
