#include "Carver_HeaderFooter.h"
#include "FileHelper.h"

int main()
{
    /*std::tuple<char*, int> jpgTuple= FileHelper::ReadBytesFromFile("tesla.jpg");
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
    FileHelper::WriteBytesToFile("teslaNew.jpg", jpgBytesTupleFromTxtFile);*/


    //std::tuple<std::string, int> discStringTupleFromTxtFile = FileHelper::ReadHexStringFromFile(Constants::PATH_ABS_SCENARIO_DD_1);
    //std::string discStringFromFile = std::get<0>(discStringTupleFromTxtFile);
    //int discCharNumFromFile = std::get<1>(discStringTupleFromTxtFile);
    //Storage* discFromTxtFile = new Storage(discCharNumFromFile, discStringFromFile);
    //Carver* headerFooterCarver = new Carver_HeaderFooter(discFromTxtFile);
    //headerFooterCarver->DoCarving();


    std::tuple<char*, int> discTuple = FileHelper::ReadBytesFromFile(Constants::PATH_ABS_SCENARIO_DD_1);
    char* bytesNum = std::get<0>(discTuple);
    int bytes = std::get<1>(discTuple);
    Storage* disc = new Storage(bytes, bytesNum);
    Carver* headerFooterCarver = new Carver_HeaderFooter(disc);
    headerFooterCarver->DoCarving();

    return 0;
}