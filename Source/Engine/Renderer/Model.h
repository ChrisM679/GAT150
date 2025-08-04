#pragma once
#include "../Math/Vector3.h"
#include "../Math/Transform.h"
#include <vector>

namespace viper
{
	class Model
	{
	public:
		Model() = default;
		Model(const std::vector<vec2> points, const vec3& color) : 
			m_points{ points }, 
			m_color{ color }
		{
			CalculateRadius();
		}

		void Draw(class Renderer& renderer, const vec2& postion, float rotation, float scale);
		void Draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() const { return m_radius; }

	private:
		void CalculateRadius();

	private:
		float m_radius{ 0.0f };
		std::vector<vec2> m_points;
		vec3 m_color{ 1, 1, 1 };
	};

}