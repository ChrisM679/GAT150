#pragma once
#include "../Renderer/Renderer.h"
#include "../Renderer/Font.h"
#include "../Math/Vector3.h"

#include <string>
#include <memory>

struct SDL_Texture;

namespace viper {
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<class Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const viper::vec3& color);
		void Draw(Renderer& renderer, float  x, float  y);

	private:
		std::shared_ptr <class Font> m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
	};
}