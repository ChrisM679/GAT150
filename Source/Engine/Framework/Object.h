#pragma once
#include "Core/Serializable.h"
#include <string>

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }

namespace viper {
	class Object : public Serializable {
	public:
		std::string name;
		bool active{ true };
	public:
		Object() = default;
		virtual ~Object() = default;

		virtual std::unique_ptr<Object> Clone() = 0;

		// Inherited via Serializable
		void Read(const json::value_t& value) override;
	};
}