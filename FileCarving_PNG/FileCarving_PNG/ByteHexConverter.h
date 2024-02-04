#pragma once
#include <iostream>
#include <sstream>
using namespace std;

static class ByteHexConverter
{
private:
	static void ByteToHexRange(char* data, int start, int end, std::string* result);
public:
	static std::string BytesToHex(char* bytes, int numBytes);
	static void HexToBytes(std::string hexString, char* result);
};