#pragma once
#include <box2d/box2d.h>
#include <memory>

namespace viper {
	inline b2Vec2 to_b2(const vec2& v) { return b2Vec2{ v.x, v.y }; }
	inline vec2 to_vec2(const b2Vec2& v) { return vec2{ v.x, v.y }; }

	class Physics {
	public:
		Physics() = default;

		bool Initialize();
		void Shutdown();

		void Update(float dt);

		static vec2 WorldToPixel(const vec2& world) { return world * ms_pixlesPerUnit; }
		static vec2 PixelToWorld(const vec2& pixels) { return pixels / ms_pixlesPerUnit; }

		static void SetPixelsPerUnit(float ppu) { ms_pixlesPerUnit = ppu; }

		static float ms_pixlesPerUnit;

	private:
		friend class PhysicsBody;

		void ProcessCollisionEvent();

		b2WorldId m_worldId;
	};
}