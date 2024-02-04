#include "Carver_HeaderFooter.h"

Carver_HeaderFooter::Carver_HeaderFooter(Storage* stor) : Carver(stor)
{
	int numOfBlocks = (stor->NumBytes() / BLOCK_SIZE) + 1;
	_headerPositions = new int[numOfBlocks];
	_footerPositions = new int[numOfBlocks];
}

Carver_HeaderFooter::~Carver_HeaderFooter()
{
	delete _headerPositions;
	delete _footerPositions;
}

void Carver_HeaderFooter::DoCarving()
{
	/*FindHeaders();
	FindFooters();*/
	FindHeadersAndFooters();
	ParseAndSaveResults();
}

//void Carver_HeaderFooter::FindHeaders()
//{
//	std::string hexBytes = _storage->HexString();
//	int hexNum = _storage->NumCharacters();
//
//	_headerCount = 0;
//	std::cout << "Looking for headers...\n";
//
//	int position = 0;
//	do
//	{
//		position = hexBytes.find(Constants::IHDR_HEX, position);
//		if (position != -1)
//		{
//			_headerPositions[_headerCount] = position;
//			_headerCount++;
//			position++;
//		}
//	} while (position != -1 && position < hexNum);
//
//	std::cout << _headerCount << " header found.\n";
//}
//
//void Carver_HeaderFooter::FindFooters()
//{
//	std::string hexBytes = _storage->HexString();
//	int hexNum = _storage->NumCharacters();
//
//	_footerCount = 0;
//	std::cout << "Looking for footers...\n";
//
//	int position = 0;
//	do
//	{
//		position = hexBytes.find(Constants::IEND_HEX, position);
//		if (position != -1)
//		{
//			_footerPositions[_footerCount] = position;
//			_footerCount++;
//			position++;
//		}
//	} while (position != -1 && position < hexNum);
//
//	std::cout << _footerCount << " footers found.\n";
//}

void Carver_HeaderFooter::FindHeadersAndFooters()
{
	int headerLen = Constants::IHDR_HEX.size() / 2;
	int footerLen = Constants::IEND_HEX.size() / 2;
	char* header = new char[headerLen];
	char* footer = new char[footerLen];
	ByteHexConverter::HexToBytes(Constants::IHDR_HEX, header);
	ByteHexConverter::HexToBytes(Constants::IEND_HEX, footer);
	char* bytes = _storage->Bytes();
	int bytesNum = _storage->NumBytes();

	_headerCount = 0;
	std::cout << "Looking for headers...\n";

	for (int i = 0; i < bytesNum - footerLen; i++) {
		if (i % BLOCK_SIZE == 0 && bytes[i] == header[0])
		{
			bool isHeader = true;
			for (int j = 1; j < headerLen; j++)
			{
				if (bytes[i + j] != header[j])
				{
					isHeader = false;
					break;
				}
			}
			if (isHeader)
			{
				_headerPositions[_headerCount] = i;
				_headerCount++;
			}
		}
		if (bytes[i] == footer[0])
		{
			bool isFooter = true;
			for (int j = 1; j < footerLen; j++)
			{
				if (bytes[i + j] != footer[j])
				{
					isFooter = false;
					break;
				}
			}
			if (isFooter)
			{
				_footerPositions[_footerCount] = i;
				_footerCount++;
			}
		}
	}

	std::cout << _headerCount << " headers found.\n";
	std::cout << _footerCount << " footers found.\n";
}

void Carver_HeaderFooter::ParseAndSaveResults()
{
	std::cout << "Parsing results.\n";
	for (int i = 0; i < _headerCount; i++)
	{
		int start = _headerPositions[i];
		int end = _footerPositions[i] + Constants::IEND_HEX.size()/2;
		char* image = new char[end - start];
		int j = 0;
		for (int i = start; i < end; i++)
		{
			image[j] = _storage->Bytes()[i];
			j++;
		}
		std::string fileName = Constants::PATH_RESULTS + "\\image" + std::to_string(i) + ".png";
		std::tuple<char*, int> bytesTuple{ image, j};
		FileHelper::WriteBytesToFile(fileName, bytesTuple);
		delete[] image;
	}
}