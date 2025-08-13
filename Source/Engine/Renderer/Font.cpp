#include "Font.h"

namespace viper {

	/// <summary>
	/// Destroys the Font object and releases associated resources.
	/// </summary>
	Font::~Font() {
		if (m_ttfFont != nullptr) {
			TTF_CloseFont(m_ttfFont);
		}
	}

	/// <summary>
	/// Loads a font from a file with the specified name and size.
	/// </summary>
	/// <param name="name">The name or path of the font file to load.</param>
	/// <param name="fontSize">The desired size of the font.</param>
	/// <returns>True if the font was loaded successfully; false otherwise.</returns>
	bool Font::Load(const std::string& name, float fontSize) {
		m_ttfFont = TTF_OpenFont(name.c_str(), fontSize);
		if (m_ttfFont == nullptr) {
			Logger::Error("SDL_Init Error: {}", SDL_GetError());
			return false;
		}

		return true;
	}
}
