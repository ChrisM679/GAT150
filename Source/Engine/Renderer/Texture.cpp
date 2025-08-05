#include "Texture.h"
#include "Renderer.h"
#include <SDL3_image/SDL_image.h>
#include <iostream>

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
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }

        // create texture from surface, texture is a friend class of renderer
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        
        // once texture is created, surface can be freed up
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }

        return true;
    }

    vec2 Texture::GetSize()
    {
        float w = 0.0f, h = 0.0f;
        SDL_GetTextureSize(m_texture, &w, &h);
        return vec2(w, h);

    }
}
