#pragma once
#include <string>

namespace viper {
	inline std ::string tolower(const std::string& str) {
		std::string result = str;
		for (char& c : result) {
			c = std::tolower(c);
		}
		return result;
	}
	inline std::string toupper(const std::string& str) {
		std::string result = str;
		for (char& c : result) {
			c = std::toupper(c);
		}
		return result;
	}
}