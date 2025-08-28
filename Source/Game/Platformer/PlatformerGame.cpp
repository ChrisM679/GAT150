#include "PlatformerGame.h"


bool PlatformerGame::Initialize() {
	OBSERVER_ADD(player_dead);
	OBSERVER_ADD(add_points);

	m_scene = std::make_unique<viper::Scene>(this);
	m_scene->Load("scenes/prototypes.json");
	m_scene->Load("scenes/level.json");

	m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "Archeologicaps.ttf", 128.0f));
	m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Archeologicaps.ttf", 48.0f));
	m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "Archeologicaps.ttf", 48.0f));

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

}

void PlatformerGame::SpawnPlayer() {
	auto player = viper::Instantiate("player");
	player->m_transform.position = viper::vec2 { 200 , 200 };
	m_scene->AddActor(std::move(player));
}

