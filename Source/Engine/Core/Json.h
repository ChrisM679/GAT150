#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"

#include <rapidjson/document.h>
#include <string>

#define JSON_READ(value, data) viper::json::Read(value, #data, data)

namespace viper::json
{
	bool Load(const std::string& filename, rapidjson::Document& document);

	bool Read(const rapidjson::Value& value, const std::string& name, int& data);

	bool Read(const rapidjson::Value& value, const std::string& name, float& data);
	bool Read(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Read(const rapidjson::Value& value, const std::string& name, std::string& data);
	bool Read(const rapidjson::Value& value, const std::string& name, vec2& data);
	bool Read(const rapidjson::Value& value, const std::string& name, vec3& data);
}