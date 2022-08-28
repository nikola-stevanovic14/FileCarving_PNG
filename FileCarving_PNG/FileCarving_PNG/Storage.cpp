#include "Storage.h"

void Storage::BytesToHex()
{
	if (_numBytes == 0)
	{
		throw "There are no bytes in storage!\n";
	}

    std::cout << "Converting " << _numBytes << " bytes to HEX string.\n";
    std::string result(2 * _numBytes, '*');

    for (int i = 0; i < _numBytes; i++)
    {
        unsigned char c = (unsigned char)_bytes[i];

        ostringstream oss;
        oss << hex << static_cast<int>(c);
        string r = oss.str();

        const char* cstr = r.c_str();
        result[i * 2] = cstr[0];
        result[i * 2 + 1] = cstr[1];
    }

    _numCharacters = 2 * _numBytes;
    _hexString = result;

    cout << _numBytes << " bytes converted to HEX string.\n\n";
}

void Storage::HexToBytes()
{
    if (_numCharacters == 0)
    {
        throw "There are no hex in storage!\n";
    }

    std::cout << "Converting " << _numCharacters << " hex to bytes.\n";

    char* result = new char[_numCharacters / 2]();

    int resultIterator = 0;
    for (int i = 0; i < _numCharacters; i += 2)
    {
        std::string hexNum(2, '*');
        hexNum[0] = _hexString[i];
        hexNum[1] = _hexString[i + 1];
        unsigned int intNum;
        std::stringstream ss;
        ss << std::hex << hexNum;
        ss >> intNum;
        char r = (char)intNum;
        result[resultIterator++] = r;
    }

    _numBytes = _numCharacters / 2;
    _bytes = result;

    cout << _numCharacters << " hex converted to bytes.\n\n";
}

Storage::Storage(int num, char* bts)
{
	_numBytes = num;
	_bytes = bts;
    BytesToHex();
}

Storage::Storage(int num, std::string hexStr)
{
	_numCharacters = num;
	_hexString = hexStr;
    HexToBytes();
}

Storage::~Storage()
{
	delete[] this->_bytes;
}