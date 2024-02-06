#pragma once
#include "Carver.h"

class Carver_ModifiedHeaderLen : public Carver
{
private:
	int _imageCount = 0;

	int _headerLen;
	int _footerLen;
	int _maxIndex;
	char* _header;
	char* _iendSig;

	std::tuple<int, int> FindNextFile(int startingPosition);
	void ParseAndSaveResult(int start, int end);
public:
	Carver_ModifiedHeaderLen(Storage* stor);
	~Carver_ModifiedHeaderLen();
	void DoCarving();
};