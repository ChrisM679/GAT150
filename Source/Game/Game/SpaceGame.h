#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class SpaceGame : public viper::Game, public viper::IObserver {
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
	SpaceGame() = default;

	bool Initialize() override;
	void Shutdown() override;

	void Update(float dt) override;
	void Draw(class viper::Renderer& renderer) override;
	void OnNotify(const viper::Event& event) override;

	void OnPlayerDeath();

	static constexpr float kBaseSpawnInterval = 2.0f;
	static constexpr float kMinSpawnInterval = 0.5f;
	static constexpr float kIntervalDecreasePer30s = 0.2f;
	static constexpr int   kBaseEnemiesPerWave = 1;
	static constexpr int   kMaxExtraEnemies = 10;
	static constexpr float kDifficultyRampSeconds = 30.0f;
		
private:
	void SpawnEnemy();
	//void SpawnEnemies(int count);

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
