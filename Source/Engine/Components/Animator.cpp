#include "EnginePCH.h"
#include "Animator.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Renderer/TextureAnimation.h"
#include "Core/StringHelper.h"
#include "Engine.h"

namespace viper {

    FACTORY_REGISTER(Animator)

        void Animator::Start() {
        
        m_spriteRenderer = owner->GetComponent<SpriteRenderer>();
        if (!m_spriteRenderer) {
            Logger::Error("Animator missing SpriteRenderer component.");
        }

        for (auto& animation : m_animations) {
            animation.second.textureAnimation =
                Resources().Get<TextureAnimation>(animation.second.textureAnimationName,
                    GetEngine().GetRenderer());

            if (!animation.second.textureAnimation) {
                Logger::Warning("Could not load Animator texture animation {}", animation.second.textureAnimationName);
            }
            else {
                Logger::Info("Animator animation '{}' loaded (resource: {})",
                    animation.first, animation.second.textureAnimationName);
            }
        }

        if (!m_animations.empty()) {
            auto it = m_animations.begin();
            Play(it->first);
        }
    }

    void Animator::Update(float dt) {
        if (m_paused || !m_currentAnimation.textureAnimation) return;

        m_frameTimer -= dt * speedMultiplier;
        if (m_frameTimer <= 0) {
            m_frameTimer = 1.0f / m_currentAnimation.textureAnimation->GetFPS();
            frame++;

            if (frame >= m_currentAnimation.textureAnimation->GetTotalFrames()) {
                if (m_currentAnimation.textureAnimation->IsLooping()) {
                    frame = 0;
                }
                else {
                    frame = m_currentAnimation.textureAnimation->GetTotalFrames() - 1;
                }
            }

            if (m_spriteRenderer) {
                m_spriteRenderer->textureRect =
                    m_currentAnimation.textureAnimation->GetFrameRect(frame);
            }
        }
    }

    void Animator::Play(const std::string& name, bool resetFrame) {

        if (equalsIgnoreCase(name, m_currentAnimationName)) return;

        auto it = m_animations.find(toLower(name));
        if (it == m_animations.end()) {
            Logger::Error("Animation '{}' does not exist in Animator", name);
            return;
        }

        m_currentAnimationName = name;
        m_currentAnimation = it->second;

        if (resetFrame) frame = 0;
        m_frameTimer = 1.0f / m_currentAnimation.textureAnimation->GetFPS();

        if (m_spriteRenderer) {
            m_spriteRenderer->texture = m_currentAnimation.textureAnimation->GetTexture();
            m_spriteRenderer->textureRect =
                m_currentAnimation.textureAnimation->GetFrameRect(frame);
        }
    }

    void Animator::Read(const json::value_t& value) {
        Object::Read(value);

        JSON_READ(value, frame);

        if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
            for (auto& animValue : JSON_GET(value, animations).GetArray()) {
                std::string name;
                std::string textureAnimationName;

                JSON_READ(animValue, name);
                JSON_READ_NAME(animValue, "texture_animation", textureAnimationName);

                TextureAnimInfo info;
                info.textureAnimationName = textureAnimationName;

                m_animations[toLower(name)] = info;
            }
        }
    }

}
