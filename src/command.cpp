#include "command.h"


std::unordered_map<std::string, Command::Name> Command::nameMap = {
	{"USER", Name::USER}, {"PASS", Name::PASS}
};


Command::Command() : name{Name::_NONE} {
}


Command::Command(const std::string& str) : Command{} {
	const std::size_t spIndex = str.find(' ');
	if (spIndex == std::string::npos) {
		name = parseName(str);
	}
	else {
		name = parseName(str.substr(0, spIndex));
	}
}


Command::Name Command::parseName(const std::string& str) {
	auto it = nameMap.find(str);
	if (it == nameMap.end()) {
		return Name::_INVALID;
	}
	else {
		return it->second;
	}
}