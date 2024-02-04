#pragma once
#include "Carver.h"

class Carver_HeaderFooter : public Carver
{
private:
	int* _headerPositions;
	int* _footerPositions;
	int _headerCount = 0;
	int _footerCount = 0;
	//void FindHeaders();
	//void FindFooters();
	void FindHeadersAndFooters();
	void ParseAndSaveResults();
public:
	Carver_HeaderFooter(Storage* stor);
	~Carver_HeaderFooter();
	void DoCarving();
};