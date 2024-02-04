#include "FileHelper.h"

int FileHelper::CalculateNumberOfBytesInFile(std::ifstream& file)
{
    file.seekg(0, std::ifstream::end);
    int numOfBytes = file.tellg();
    file.seekg(std::ifstream::beg);
    return numOfBytes;
}

std::tuple<char*, int> FileHelper::ReadBytesFromFile(std::string filePath)
{
    std::cout << "Loading byte file " << filePath << "\n";
    std::ifstream fileToRead;
    fileToRead.open(filePath, std::ifstream::in | std::ifstream::binary);
    size_t numOfBytes = FileHelper::CalculateNumberOfBytesInFile(fileToRead);

    fileToRead.seekg(std::ifstream::beg);
    char* bytes = new char[numOfBytes];
    fileToRead.read(bytes, numOfBytes);
    fileToRead.close();

    std::cout << filePath << " loaded.\n\n";
    return std::tuple<char*, int>{bytes, numOfBytes};
}

void FileHelper::WriteStringToFile(std::string fileName, std::string string, int numOfCharacters)
{
    std::cout << "Writing " << numOfCharacters << " HEX characters to " << fileName << " file.\n";
    std::ofstream fileToWrite(fileName);
    for (int i = 0; i < numOfCharacters; i++)
    {
        fileToWrite << string[i];
    }
    fileToWrite.close();
    std::cout << "Writing to " << fileName << " is finished.\n\n";
}

std::tuple<std::string, int> FileHelper::ReadHexStringFromFile(std::string filePath)
{
    std::cout << "Reading hex from " << filePath << "\n";
    std::ifstream fileWithHexBytes(filePath);
    int numOfBytes = FileHelper::CalculateNumberOfBytesInFile(fileWithHexBytes);
    std::string result(numOfBytes, '*');

    char hex;
    int resultIterator = 0;
    while (fileWithHexBytes.get(hex))
    {
        result[resultIterator++] = hex;
    }

    std::cout << "Reading hex from " << filePath << " finished.\n";

    return std::tuple<std::string, int>{result, numOfBytes};
}

void FileHelper::WriteBytesToFile(std::string filePath, std::tuple<char*, int>  toWrite)
{
    char* bytes = std::get<0>(toWrite);
    int numBytes= std::get<1>(toWrite);

    std::cout << "Writing " << numBytes << " bytes to "<< filePath <<".\n";


    std::ofstream outputFile(filePath, std::ios::out | std::ios::binary);
    outputFile.write(bytes, numBytes);

    std::cout << "Writing " << numBytes << " bytes to " << filePath << " finished.\n";
}