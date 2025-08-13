#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "../GameData.h"

bool SpaceGame::Initialize()
{
    m_scene = std::make_unique<viper::Scene>(this);

	m_titleText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("title_font", "fonts/MetalLord.ttf", 128.0f));
	m_scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "fonts/MetalLord.ttf", 48.0f));
	m_livesText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font", "fonts/MetalLord.ttf", 48.0f));

    return true;
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

        // create player
        //std::shared_ptr<viper::Model> model = std::make_shared<viper::Model>(GameData::shipPoints, viper::vec3{ 0.0f, 0.4f, 1.0f });
        viper::Transform transform{ viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() * 0.5f, viper::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 0.5f };
        auto player = std::make_unique<Player>(transform);
        player->speed = 1500.0f;
        player->rotationRate = 600.0f;
        player->name = "player";
        player->tag = "player";

        //components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "textures/playership.png";
        player->AddComponent(std::move(spriteRenderer));

		auto rb = std::make_unique<viper::RigidBody>();
		rb->damping = 1.5f;
		player->AddComponent(std::move(rb));

		auto collider = std::make_unique<viper::CircleCollider2D>();
		collider->radius = 20.0f;
		player->AddComponent(std::move(collider));

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

        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0.0f) {
            m_enemySpawnTimer = currentSpawnInterval;
            if ((int)activeEnemies < m_maxActiveEnemies) {
                int allowedToSpawn = std::min(enemiesThisWave, m_maxActiveEnemies - static_cast<int>(activeEnemies));
                SpawnEnemies(allowedToSpawn);
            }
        }
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

    m_scene->Draw(renderer);

	viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDeath()
{
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2.0f;
}

void SpaceGame::SpawnEnemies()
{
    SpawnEnemies(kBaseEnemiesPerWave);
}

void SpaceGame::SpawnEnemies(int count)
{
    Player* player = m_scene->GetactorByName<Player>("player");
    viper::vec2 playerPos = {};
    float playerRadius = 0.0f;

    if (player) {
        playerPos = player->m_transform.position;
		playerRadius = player->GetComponent<viper::CircleCollider2D>()->radius;
    }

    float screenW = (float)viper::GetEngine().GetRenderer().GetWidth();
    float screenH = (float)viper::GetEngine().GetRenderer().GetHeight();

    for (int i = 0; i < count; ++i) {
        viper::vec2 spawnPos;
        bool validSpawn = false;

        do {
            int edge = static_cast<int>(viper::random::getReal(0.0f, 4.0f));
            switch (edge) {
            case 0: 
                spawnPos.x = viper::random::getReal() * screenW;
                spawnPos.y = 0.0f;
                break;
            case 1:
                spawnPos.x = viper::random::getReal() * screenW;
                spawnPos.y = screenH;
                break;
            case 2: 
                spawnPos.x = 0.0f;
                spawnPos.y = viper::random::getReal() * screenH;
                break;
            case 3:
            default:
                spawnPos.x = screenW;
                spawnPos.y = viper::random::getReal() * screenH;
                break;
            }

            if (player) {
                viper::vec2 direction = playerPos - spawnPos;
                if (direction.LengthSqr() > (playerRadius * playerRadius * 4.0f)) {
                    validSpawn = true;
                }
            } else {
                validSpawn = true;\
            }
        } while (!validSpawn);

        viper::Transform transform{ spawnPos, 0, 0.5f };
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);

        auto rb = std::make_unique<viper::RigidBody>();
        rb->damping = 0.5f;
        enemy->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 20.0f;
        enemy->AddComponent(std::move(collider));

        float enemySpeed = viper::random::getReal(250.0f, 500.0f);
        enemy->speed = enemySpeed;

        enemy->fireTime = 100.0f;
        enemy->fireTimer = enemy->fireTime;

         /*
        if (player) {
            viper::vec2 direction = playerPos - spawnPos;
            if (direction.LengthSqr() > 0.0f) {
                direction = direction.Normalized();
                enemy->m_transform.rotation = viper::math::radToDeg(direction.Angle());
                enemy->velocity = direction * enemySpeed;
            }
        } else {
            enemy->velocity = viper::vec2{ 0, 0 };
        }
        */

        //components
        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "textures/playership.png";
        enemy->AddComponent(std::move(spriteRenderer));

        enemy->tag = "enemy";
        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::Shutdown()
{
    //
}
