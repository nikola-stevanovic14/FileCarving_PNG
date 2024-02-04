#include "Storage.h"
#include <thread>


//void Storage::BytesToHex()
//{
//	if (_numBytes == 0)
//	{
//		throw "There are no bytes in storage!\n";
//	}
//
//    std::cout << "Converting " << _numBytes << " bytes to HEX string.\n";
//
//    int step = _numBytes / 10;
//
//    std::string r1(step*2, '*');
//    thread t1([&] { this->ByteToHexRange(&r1, _bytes, 0, step); });
//    std::string r2(step * 2, '*');
//    thread t2([&] { this->ByteToHexRange(&r2, _bytes, step * 1, step * 2); });
//    std::string r3(step * 2, '*');
//    thread t3([&] { this->ByteToHexRange(&r3, _bytes, step * 2, step * 3); });
//    std::string r4(step * 2, '*');
//    thread t4([&] { this->ByteToHexRange(&r4, _bytes, step * 3, step * 4); });
//    std::string r5(step * 2, '*');
//    thread t5([&] { this->ByteToHexRange(&r5, _bytes, step * 4, step * 5); });
//    std::string r6(step * 2, '*');
//    thread t6([&] { this->ByteToHexRange(&r6, _bytes, step * 5, step * 6); });
//    std::string r7(step * 2, '*');
//    thread t7([&] { this->ByteToHexRange(&r7, _bytes, step * 6, step * 7); });
//    std::string r8(step * 2, '*');
//    thread t8([&] { this->ByteToHexRange(&r8, _bytes, step * 7, step * 8); });
//    std::string r9(step * 2, '*');
//    thread t9([&] { this->ByteToHexRange(&r9, _bytes, step * 8, step * 9); });
//    std::string r10((_numBytes-9*step) * 2, '*');
//    thread t10([&] { this->ByteToHexRange(&r10, _bytes, step * 9, _numBytes); });
//    
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//    t5.join();
//    t6.join();
//    t7.join();
//    t8.join();
//    t9.join();
//    t10.join();
//
//    _numCharacters = 2 * _numBytes;
//    _hexString = r1+r2+r3+r4+r5+r6+r7+r8+r9+r10;
//
//    std::cout << _numBytes << " bytes converted to HEX string.\n\n";
//}

//void Storage::ByteToHexRange(std::string* result, char* data, int start, int end)
//{
//    int resIterator = 0;
//    for (int i = start; i < end; i++)
//    {
//        ostringstream oss;
//        oss << hex << (int)((unsigned char)data[i]);
//        std::string cstr = oss.str();
//        if (cstr.size() == 1)
//        {
//            (*result)[resIterator * 2] = '0';
//            (*result)[resIterator * 2 + 1] = cstr[0];
//        }
//        else
//        {
//            (*result)[resIterator * 2] = cstr[0];
//            (*result)[resIterator * 2 + 1] = cstr[1];
//        }
//        resIterator++;
//    }
//}

//void Storage::HexToBytes()
//{
//    if (_numCharacters == 0)
//    {
//        throw "There are no hex in storage!\n";
//    }
//
//    std::cout << "Converting " << _numCharacters << " hex to bytes.\n";
//
//    char* result = new char[_numCharacters / 2]();
//
//    int resultIterator = 0;
//    for (int i = 0; i < _numCharacters; i += 2)
//    {
//        std::string hexNum(2, '*');
//        hexNum[0] = _hexString[i];
//        hexNum[1] = _hexString[i + 1];
//        unsigned int intNum;
//        std::stringstream ss;
//        ss << std::hex << hexNum;
//        ss >> intNum;
//        char r = (char)intNum;
//        result[resultIterator++] = r;
//    }
//
//    _numBytes = _numCharacters / 2;
//    _bytes = result;
//
//    cout << _numCharacters << " hex converted to bytes.\n\n";
//}

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