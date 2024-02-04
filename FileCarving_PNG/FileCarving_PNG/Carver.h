#pragma once
#include "Storage.h"
#include "Constants.h"
#include "FileHelper.h"

class Carver
{
protected:
	Storage* _storage;
	int _filesFound = 0;
public:
	Carver(Storage* stor);
	~Carver();
	virtual void DoCarving() = 0;
};
