#pragma once
#include <string>
#include <vector>
#include <span>

namespace Ff
{
	std::string readFileToString(const std::string& path);

	void writeStringToFile(const std::string& path, const std::string& stringToWrite);
	
	std::vector<std::byte> readBinaryFile(const std::string& path);

	template<typename T>
	T readBinaryFile(const std::string& path)
	{
		std::vector<std::byte> bytes = readBinaryFile(path);
		return *reinterpret_cast<T*>(bytes.data());
	}
	
	void writeToBinaryFile(const std::string& path, const void* data, uint64_t size);

	template<typename T>
	void writeToBinaryFile(const std::string& path, const T& object)
	{
		writeToBinaryFile(path, &object, sizeof(object));
	}
}