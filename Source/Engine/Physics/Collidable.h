#pragma once

namespace viper {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void OnCollision(class Actor* other) = 0;
	};
}