#include "Text.h"
#include <SDL3_ttf/SDL_ttf.h>

namespace viper {

	/// <summary>
	/// Destroys the Text object and releases its associated SDL texture if it exists.
	/// </summary>
	Text::~Text() {
		if (m_texture != nullptr) {
			SDL_DestroyTexture(m_texture);
		}
	}

	/// <summary>
	/// Creates a text texture using the specified renderer, text string, and color.
	/// </summary>
	/// <param name="renderer">Reference to the Renderer object used for creating the texture.</param>
	/// <param name="text">The string to be rendered as text.</param>
	/// <param name="color">The color of the text, represented as a vec3 (RGB components in the range [0, 1]).</param>
	/// <returns>True if the text texture was successfully created; false otherwise.</returns>
	bool Text::Create(Renderer& renderer, const std::string& text, const vec3& color) {
		// create a surface using the font, text string and color
		SDL_Color c{ (uint8_t)(color.r * 255), (uint8_t)(color.g * 255), (uint8_t)(color.b * 255), 255 };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), text.size(), c);
		if (surface == nullptr) {
			std::cerr << "Could not create surface.\n";
			return false;
		}

		// create a texture from the surface, only textures can render to the renderer
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		if (m_texture == nullptr) {
			SDL_DestroySurface(surface);
			std::cerr << "Could not create texture" << SDL_GetError() << std::endl;
			return false;
		}

		// free the surface, no longer needed after creating the texture
		SDL_DestroySurface(surface);

		return true;
	}

	/// <summary>
	/// Draws the text texture at the specified position using the given renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the text texture.</param>
	/// <param name="x">The x-coordinate where the text will be drawn.</param>
	/// <param name="y">The y-coordinate where the text will be drawn.</param>
	void Text::Draw(Renderer& renderer, float x, float y) {
		// get the texture width and height
		float width, height;
		bool success = SDL_GetTextureSize(m_texture, &width, &height);
		assert(success);

		// set the texture into the renderer at rect 
		SDL_FRect rect{ x, y, width, height };
		success = SDL_RenderTexture(renderer.m_renderer, m_texture, NULL, &rect);
		assert(success);
	}
}