#pragma once
#include "Resources/Resource.h"

namespace viper {
	class AudioClip : public Resource {
	public:
		AudioClip() = default;
		~AudioClip();

		bool Load(const std::string& filename, class AudioSystem& renderer);

	private:
		friend class AudioSystem;

		FMOD::Sound* m_sound{ nullptr };
	};
}