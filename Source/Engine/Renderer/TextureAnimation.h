#pragma once

namespace viper {
    class Texture;

    class TextureAnimation : public Resource {
    public:
        TextureAnimation() = default;
        ~TextureAnimation() = default;

        bool Load(const std::string& filename, class Renderer& renderer);

        vec2 GetSize() const;
        rect GetFrameRect(int frame) const;

        int GetTotalFrames() const { return m_totalFrames; }
        float GetFPS() const { return m_framesPerSecond; }
        bool IsValidFrame(int frame) const { return frame >= 0 && frame < m_totalFrames; }
        bool IsLooping() const { return m_loop; }

        res_t<Texture> GetTexture() { return m_texture; }

    private:
        int m_columns = 0;
        int m_rows = 0;
        int m_startFrame = 0;
        int m_totalFrames = 0;
        float m_framesPerSecond = 0;
        bool m_loop = true;

        res_t<Texture> m_texture;
    };
}