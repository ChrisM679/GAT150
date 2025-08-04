#pragma once
#include "Core/Time.h"
#include <memory>

namespace viper {
	class Renderer;
	class InputSystem;
	class AudioSystem;
	class ParticleSystem;

	class Engine
	{
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *m_renderer; }
		InputSystem& GetInput() { return *m_input; }
		AudioSystem& GetAudio() { return *m_audio; }
		ParticleSystem& GetParticleSystem() { return *m_particleSystem; }

		Time& GetTime() { return m_time; }

	private:
		Time m_time;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<ParticleSystem> m_particleSystem;
	};

	Engine& GetEngine();
}