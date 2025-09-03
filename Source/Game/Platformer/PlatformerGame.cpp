#include "PlatformerGame.h"


bool PlatformerGame::Initialize() {
	OBSERVER_ADD(player_dead);
	OBSERVER_ADD(add_points);

	m_scene = std::make_unique<viper::Scene>(this);
	m_scene->Load("scenes/prototypes.json");
	m_scene->Load("scenes/level.json");

	return true;
}

void PlatformerGame::Update(float dt) {
	switch (m_gameState){
	case PlatformerGame::GameState::Initialize:
		m_gameState = GameState::StartRound;
		break;

	case PlatformerGame::GameState::Title:
		break;

	case PlatformerGame::GameState::StartGame:
		break;

	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		SpawnEnemy();
		m_gameState = GameState::Game;
		break;

	case PlatformerGame::GameState::Game:
		break;

	case PlatformerGame::GameState::PlayerDead:
		break;

	case PlatformerGame::GameState::GameOver:
		break;

	default:
		break;
	}
	m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Shutdown() {
	//
}

void PlatformerGame::Draw(class viper::Renderer& renderer) {
	m_scene->Draw(renderer);
	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void PlatformerGame::OnNotify(const viper::Event& event) {

}

void PlatformerGame::OnPlayerDeath() {

}

void PlatformerGame::SpawnEnemy() {
	//auto enemy = viper::Instantiate("platformenemy");
	auto enemy = viper::Instantiate("bat");
	enemy->m_transform.position = viper::vec2{ 900 , 400 };
	m_scene->AddActor(std::move(enemy));
}

void PlatformerGame::SpawnPlayer() {
	auto player = viper::Instantiate("platformplayer");
	player->m_transform.position = viper::vec2{ 500 , 400 };
	m_scene->AddActor(std::move(player));
}

