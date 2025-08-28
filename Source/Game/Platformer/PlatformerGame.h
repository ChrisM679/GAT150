#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class PlatformerGame : public viper::Game, public viper::IObserver {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	};

public:
	PlatformerGame() = default;

	bool Initialize() override;
	void Shutdown() override;

	void Update(float dt) override;
	void Draw(class viper::Renderer& renderer) override;
	void OnNotify(const viper::Event& event) override;

	void OnPlayerDeath();

private:
	void SpawnEnemy();
	void SpawnPlayer();

private:
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer{ 0.0f };
	float m_stateTimer{ 0.0f };
	float m_timeSinceStart{ 0.0f };
	int m_maxActiveEnemies = 100;

	std::shared_ptr<class viper::Font> m_titleFont;
	std::shared_ptr<class viper::Font> m_uiFont;

	std::unique_ptr<class viper::Text> m_titleText;
	std::unique_ptr<class viper::Text> m_scoreText;
	std::unique_ptr<class viper::Text> m_livesText;
};
