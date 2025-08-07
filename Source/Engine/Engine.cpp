#include "Engine.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"

namespace viper {

	bool Engine::Initialize() {
		m_renderer = std::make_unique<viper::Renderer>();
		m_renderer->Initialize();
		m_renderer->CreateWindow("Viper Engine", 1280, 1024);

		m_input = std::make_unique<viper::InputSystem>();
		m_input->Initialize();

		m_audio = std::make_unique<viper::AudioSystem>();
		m_audio->Initialize();

		m_particleSystem = std::make_unique<viper::ParticleSystem>();
		m_particleSystem->Initialize(5000);
		 
		return true;
	}

	void Engine::Shutdown() {
		m_particleSystem->Shutdown();
		m_audio->Shutdown();
		m_input->Shutdown();
		m_renderer->Shutdown();

	}

	void Engine::Update() {
		m_time.Tick();
		m_audio->Update();
		m_input->Update();
		m_particleSystem->Update(m_time.GetDeltaTime());
	}

	void Engine::Draw() {
		//
	}
}