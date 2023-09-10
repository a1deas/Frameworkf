#include "file.h"
#include <fstream>
#include "Core/log.h"


namespace Ff
{
	std::string readFileToString(const std::string& path)
	{
		std::ifstream fileObject(path);
		if (!fileObject.is_open())
		{
			FFCRIT("failed open file: {}", path);
			abort();
		}

		std::stringstream ss;
		ss << fileObject.rdbuf();

		return ss.str();
	}

	void writeStringToFile(const std::string& path, const std::string& stringToWrite)
	{
		std::ofstream fileObject(path);
		if(!fileObject.is_open())
		{
			FFCRIT("failed open file: {}", path);
			abort();
		}

		fileObject << stringToWrite;
		fileObject.flush();
	}
}