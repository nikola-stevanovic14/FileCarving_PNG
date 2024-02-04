#pragma once
#include <iostream>
#include <fstream>
#include <tuple>

class FileHelper
{
public:
    static int CalculateNumberOfBytesInFile(std::ifstream& file);
    static std::tuple<char*, int> ReadBytesFromFile(std::string filePath);
    static void WriteStringToFile(std::string fileName, std::string string, int numOfCharacters);
    static std::tuple<std::string, int> ReadHexStringFromFile(std::string filePath);
    static void WriteBytesToFile(std::string filePath, std::tuple<char*, int>  toWrite);
};