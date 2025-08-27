#include "../GamePCH.h"
#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

bool SpaceGame::Initialize()
{
	OBSERVER_ADD(player_dead);
	OBSERVER_ADD(add_points);

    m_scene = std::make_unique<viper::Scene>(this);
	m_scene->Load("scene.json");

	m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "fonts/MetalLord.ttf", 128.0f));
	m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "fonts/MetalLord.ttf", 48.0f));
	m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "fonts/MetalLord.ttf", 48.0f));

    return true;
}

void SpaceGame::Shutdown() {
    //
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {
        m_scene->RemoveAllActors();

		auto player = viper::Factory::Instance().Create<viper::Actor>("player");
		m_scene->AddActor(std::move(player));

        m_gameState = GameState::Game;
    }
    break;
    case SpaceGame::GameState::Game:
    {
        m_timeSinceStart += dt;

        float difficultySteps = m_timeSinceStart / kDifficultyRampSeconds;

        float intervalShrink = difficultySteps * kIntervalDecreasePer30s;
        float currentSpawnInterval = std::max(kMinSpawnInterval, kBaseSpawnInterval - intervalShrink);

        int extraEnemies = static_cast<int>(std::floor(difficultySteps));
        extraEnemies = std::min(extraEnemies, kMaxExtraEnemies);
        int enemiesThisWave = kBaseEnemiesPerWave + extraEnemies;

        auto activeEnemies = m_scene->GetActorsByTag<Enemy>("enemy").size();
    }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0) {
                m_gameState = GameState::GameOver;
                m_stateTimer = 3.0f;
            }
            else {
                m_gameState = GameState::StartRound;
            }
        }
        break;
    case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_gameState = GameState::Title;
        }
        break;
    default:
        break;
    }

    m_scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer)
{
    m_scene->Draw(renderer);

    if (m_gameState == GameState::Title) {
		m_titleText->Create(renderer, "MetalLord", viper::vec3{ 1.0f, 1.0f, 1.0f });
        m_titleText->Draw(renderer, 400, 400);
    }

    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", viper::vec3{ 1.0f, 0.0f, 0.0f });
		m_titleText->Draw(renderer, 400, 400);
    }

	m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), viper::vec3{ 1.0f, 1.0f, 1.0f });
	m_scoreText->Draw(renderer, 20, 20);

	m_livesText->Create(renderer, "Lives: " + std::to_string(m_lives), viper::vec3{ 1.0f, 1.0f, 1.0f });
	m_livesText->Draw(renderer, (float)renderer.GetWidth() - 200, (float)20);

	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnNotify(const viper::Event& event) {
    if (viper::equalsIgnoreCase(event.id, "player_dead")) {
        OnPlayerDeath();
    }
    else if (viper::equalsIgnoreCase(event.id, "add_points")) {
        AddPoints(std::get<int>(event.data));
	}
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemy() {
	viper::Actor* player = m_scene->GetActorByName<viper::Actor>("player");
    if (player) {
		viper::vec2 positon = player->m_transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f, 500.0f);
		viper::Transform transform{ positon, viper::random::getReal(0.0f, 360.0f), 1.0f};

        auto enemy = viper::Instantiate("enemy", transform);
        m_scene->AddActor(std::move(enemy));
    }
}
