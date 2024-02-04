#include "ByteHexConverter.h"
#include <thread>

void ByteHexConverter::ByteToHexRange(char* data, int start, int end, std::string* result)
{
    int resIterator = 0;
    for (int i = start; i < end; i++)
    {
        ostringstream oss;
        oss << hex << (int)((unsigned char)data[i]);
        std::string cstr = oss.str();
        if (cstr.size() == 1)
        {
            (*result)[resIterator * 2] = '0';
            (*result)[resIterator * 2 + 1] = cstr[0];
        }
        else
        {
            (*result)[resIterator * 2] = cstr[0];
            (*result)[resIterator * 2 + 1] = cstr[1];
        }
        resIterator++;
    }
}

std::string ByteHexConverter::BytesToHex(char* bytes, int numBytes)
{
    if (numBytes == 0)
    {
        throw "There are no bytes in storage!\n";
    }

    std::cout << "Converting " << numBytes << " bytes to HEX string.\n";

    int step = numBytes / 10;

    std::string r1(step * 2, '*');
    thread t1([&] { ByteToHexRange(bytes, 0, step, &r1); });
    std::string r2(step * 2, '*');
    thread t2([&] { ByteToHexRange(bytes, step * 1, step * 2, &r2); });
    std::string r3(step * 2, '*');
    thread t3([&] { ByteToHexRange(bytes, step * 2, step * 3, &r3); });
    std::string r4(step * 2, '*');
    thread t4([&] { ByteToHexRange(bytes, step * 3, step * 4, &r4); });
    std::string r5(step * 2, '*');
    thread t5([&] { ByteToHexRange(bytes, step * 4, step * 5, &r5); });
    std::string r6(step * 2, '*');
    thread t6([&] { ByteToHexRange(bytes, step * 5, step * 6, &r6); });
    std::string r7(step * 2, '*');
    thread t7([&] { ByteToHexRange(bytes, step * 6, step * 7, &r7); });
    std::string r8(step * 2, '*');
    thread t8([&] { ByteToHexRange(bytes, step * 7, step * 8, &r8); });
    std::string r9(step * 2, '*');
    thread t9([&] { ByteToHexRange(bytes, step * 8, step * 9, &r9); });
    std::string r10((numBytes - 9 * step) * 2, '*');
    thread t10([&] { ByteToHexRange(bytes, step * 9, numBytes, &r10); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    std::cout << numBytes << " bytes converted to HEX string.\n\n";
    return r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8 + r9 + r10;
}

void ByteHexConverter::HexToBytes(std::string hexString, char* result)
{
    int numCharacters = hexString.size();
    if (numCharacters == 0)
    {
        throw "There are no hex in storage!\n";
    }

    std::cout << "Converting " << numCharacters << " hex to bytes.\n";

    int resultIterator = 0;
    for (int i = 0; i < numCharacters; i += 2)
    {
        std::string hexNum(2, '*');
        hexNum[0] = hexString[i];
        hexNum[1] = hexString[i + 1];
        unsigned int intNum;
        std::stringstream ss;
        ss << std::hex << hexNum;
        ss >> intNum;
        char r = (char)intNum;
        result[resultIterator++] = r;
    }

    int numBytes = numCharacters / 2;
    char* bytes = result;

    cout << numCharacters << " hex converted to bytes.\n\n";
}