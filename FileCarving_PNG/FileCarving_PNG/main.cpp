#include "Carver_HeaderFooter.h"
#include "Carver_ModifiedHeaderLen.h"
#include "FileHelper.h"

int main()
{
    bool isHeaderFooterCarver = false;

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
    Carver* carver;
    if (isHeaderFooterCarver) carver = new Carver_HeaderFooter(disc);
    else carver = new Carver_ModifiedHeaderLen(disc);
    carver->DoCarving();

    return 0;
}