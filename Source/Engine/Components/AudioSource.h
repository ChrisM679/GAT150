#pragma once
#include "Framework/Component.h"

namespace viper {
	class AudioSource : public Component {
	public:
		std::string audioClipName; 

		void Update(float dt) override;
		void Play();
	};
}
