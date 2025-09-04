#include "Texture.h"
#include "Renderer.h"

namespace viper {
    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (m_texture) SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            Logger::Error("SDL_Init Error: {}", SDL_GetError());
            return false;
        }

        return true;
    }

    vec2 Texture::GetSize() {
        float w, h;
        SDL_GetTextureSize(m_texture, &w, &h);
        return vec2(w, h);
    }
}
