#pragma once

namespace viper {
	class Object {
	public:
		std::string name;
		bool active{ true };
	public:
		Object() = default;
		virtual ~Object() = default;
	};
}