#pragma once

namespace viper {
	class Tilemap : public Resource {
	public:
		struct Layer {
			int height{ 0 };
			int width{ 0 };
			bool hasCollision{ true };
			std::vector<int> data;
			res_t<Texture> texture;
		};

	public:
		Tilemap() = default;
		~Tilemap() = default;

		bool Load(const std::string& filename, class Renderer& renderer);

		const std::vector<Layer>& GetLayers() const { return m_layers; }
		rect GetTextureRect(const Layer& layer, int tileId);
		vec2 GetPosition(const Layer& layer, int tileIndex);

	private:
		int tileheight{ 0 };
		int tilewidth{ 0 };

		std::vector<Layer> m_layers;
	};
}
