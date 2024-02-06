#include "Carver_ModifiedHeaderLen.h"

Carver_ModifiedHeaderLen::Carver_ModifiedHeaderLen(Storage* stor) : Carver(stor)
{
	_headerLen = Constants::IHDR_HEX.size() / 2;
	_footerLen = Constants::IEND_HEX.size() / 2;
	_maxIndex = _storage->NumBytes();
	_header = new char[_headerLen];
	_iendSig = new char[4];
	ByteHexConverter::HexToBytes(Constants::IHDR_HEX, _header);
	ByteHexConverter::HexToBytes(Constants::IEND_SIG_HEX, _iendSig);
}

Carver_ModifiedHeaderLen::~Carver_ModifiedHeaderLen()
{
}

std::tuple<int, int> Carver_ModifiedHeaderLen::FindNextFile(int startingPosition)
{
	int i = startingPosition;
	char* bytes = _storage->Bytes();

	if (i == 79465378)
	{
		int a = 5;
	}

	while (i < _maxIndex)
	{
		if (i % BLOCK_SIZE == 0 && bytes[i] == _header[0])
		{
			bool isHeader = true;
			for (int j = 1; j < _headerLen; j++)
			{
				if (bytes[i + j] != _header[j])
				{
					isHeader = false;
					break;
				}
			}
			if (isHeader)
			{
				int chunkStart = i
					+ 8 //8B PNG signature
					+ 4 //4B IHDR len field
					+ 4 //4B IHDR signature
					+ 13 //13B IHDR data
					+ 4; //4B CRC

				int j = chunkStart;
				bool isEnd = false;
				int fileEnd = j;
				while (j < _maxIndex)
				{
					int chunkDataLen = int((unsigned char)(bytes[j]) << 24 |
						(unsigned char)(bytes[j + 1]) << 16 |
						(unsigned char)(bytes[j + 2]) << 8 |
						(unsigned char)(bytes[j + 3]));

					isEnd = bytes[j + 4] == _iendSig[0] &&
						bytes[j + 5] == _iendSig[1] &&
						bytes[j + 6] == _iendSig[2] &&
						bytes[j + 7] == _iendSig[3];

					if (isEnd)
					{
						fileEnd = j + _footerLen;
						if (isEnd) return std::tuple<int, int>{i, fileEnd};
					}
					else
					{
						j = j +
							+ 4 //4B IDAT len field
							+ 4 //4B IDAT signature
							+ chunkDataLen //data
							+ 4; //4B CRC
					}
				}
				return std::tuple<int, int>{-1, -1};
			}
		}
		i = i + (BLOCK_SIZE - i%BLOCK_SIZE);
	}
	return std::tuple<int, int>{-1, -1};
}

void Carver_ModifiedHeaderLen::ParseAndSaveResult(int start, int end)
{
	char* image = new char[end - start];
	int j = 0;
	for (int i = start; i < end; i++)
	{
		image[j] = _storage->Bytes()[i];
		j++;
	}
	std::string fileName = Constants::PATH_RESULTS + "\\image" + std::to_string(_imageCount) + ".png";
	std::tuple<char*, int> bytesTuple{ image, j };
	FileHelper::WriteBytesToFile(fileName, bytesTuple);
	delete[] image;
}

void Carver_ModifiedHeaderLen::DoCarving()
{
	cout << "Modified Header-Length carving has started.\n";
	int i = 0;
	while(1)
	{
		cout << "Looking for the next file. Starting position " + std::to_string(i) + ".\n";
		std::tuple<int, int> filePosition = FindNextFile(i);
		int fileStart = std::get<0>(filePosition);
		int fileEnd = std::get<1>(filePosition);
		if (fileStart == -1) break;
		cout << "File found. Start = " + std::to_string(fileStart) + ", End = " + std::to_string(fileEnd) + "\n";
		_imageCount++;
		ParseAndSaveResult(fileStart, fileEnd);
		i = fileEnd + 1;
	}
	cout << "Modified Header-Length carving completed.\n";
}