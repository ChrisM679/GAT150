#pragma once
#include "Renderer/TextureAnimation.h"
#include <map>
#include <string>

namespace viper {

    class SpriteRenderer;

    class Animator : public Component {
    public:
        struct TextureAnimInfo {
            std::string textureAnimationName;
            res_t<TextureAnimation> textureAnimation;
        };

        int frame = 0;
        float speedMultiplier{ 1.0f };

    public:
        CLASS_PROTOTYPE(Animator)

        void Start() override;
        void Update(float dt) override;

        void Play(const std::string& name, bool resetFrame = true);
        void Pause(bool pause) { m_paused = pause; }
        bool IsPaused() const { return m_paused; }

        const std::string& GetCurrentAnimationName() const { return m_currentAnimationName; }

        void Read(const json::value_t& value) override;

    private:
        float m_frameTimer = 0;
        bool m_paused = false;

        std::string m_currentAnimationName;
        TextureAnimInfo m_currentAnimation;

        std::map<std::string, TextureAnimInfo> m_animations;
        SpriteRenderer* m_spriteRenderer{ nullptr };
    };

}