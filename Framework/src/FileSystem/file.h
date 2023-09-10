#pragma once
#include <string>

namespace Ff
{
	std::string readFileToString(const std::string& path);
	void writeStringToFile(const std::string& path, const std::string& stringToWrite);

	

}