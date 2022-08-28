#include "Storage.h"
#include "FileHelper.h"

int main()
{
    std::tuple<char*, int> jpgTuple= FileHelper::ReadBytesFromFile("tesla.jpg");
    char* jpgBytes = std::get<0>(jpgTuple);
    int jpgNumBytes = std::get<1>(jpgTuple);
    Storage storage(jpgNumBytes, jpgBytes);
    
    std::tuple<std::string, int> jpgStringTuple{ storage.HexString(), storage.NumCharacters()};
    FileHelper::WriteStringToFile("tesla.txt", jpgStringTuple);

    std::tuple<std::string, int> jpgStringTupleFromTxtFile = FileHelper::ReadHexStringFromFile("tesla.txt");
    std::string jpgStringFromFile = std::get<0>(jpgStringTupleFromTxtFile);
    int jpgCharNumFromFile = std::get<1>(jpgStringTupleFromTxtFile);
    Storage storageFromTxtFile(jpgCharNumFromFile, jpgStringFromFile);
    std::tuple<char*, int> jpgBytesTupleFromTxtFile = std::tuple<char*, int>
    { storageFromTxtFile.Bytes(), storageFromTxtFile.NumBytes() };
    FileHelper::WriteBytesToFile("teslaNew.jpg", jpgBytesTupleFromTxtFile);

    return 0;
}