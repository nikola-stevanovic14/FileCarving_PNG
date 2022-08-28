#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class Storage
{
	private:
		int _numBytes = 0;
		char* _bytes;

		int _numCharacters = 0;
		std::string _hexString;

		void BytesToHex();
		void HexToBytes();
	public:
		inline int NumBytes() { return this->_numBytes; }
		inline char* Bytes() { return this->_bytes; }
		inline int NumCharacters() { return this->_numCharacters; }
		inline std::string HexString() { return this->_hexString; }

		Storage(int num, char* bts);
		Storage(int num, std::string hexStr);
		~Storage();
};