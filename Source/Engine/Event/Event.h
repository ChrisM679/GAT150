#pragma once
#include <string>
#include <variant>

namespace viper {
	struct Event {
		using id_t = std::string;
		using data_t = std::variant<int, bool, float, std::string, vec2, vec3>;

		id_t id;
		data_t data;

		Event(const id_t& id, data_t data) :
			id{ id },
			data{ data }
		{}
	};
}