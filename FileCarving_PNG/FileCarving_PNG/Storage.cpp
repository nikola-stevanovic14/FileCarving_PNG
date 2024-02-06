#include "Storage.h"
#include <thread>

Storage::Storage(int num, char* bts)
{
	_numBytes = num;
	_bytes = bts;
	_numCharacters = _numBytes * 2;
	//_hexString = ByteHexConverter::BytesToHex(_bytes, _numBytes);
}

Storage::Storage(int num, std::string hexStr)
{
	_numCharacters = num;
	_hexString = hexStr;
	_bytes = new char[_numCharacters / 2]();
    ByteHexConverter::HexToBytes(_hexString, _bytes);
}

Storage::~Storage()
{
	//delete this->_bytes;
}