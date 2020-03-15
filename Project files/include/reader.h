#pragma once

#include "controller.h"
#include <fstream>

class Line
{
public:
	char* str;
	size_t len;

	Line();
	~Line();

	char* getLine();
	char* getLine(std::fstream& file);
	char* getFirstWord();
	Storage<double> getNumbers();

private:
	double createNumber(int beg, int en);
};

class Reader
{
public:
	Reader();
	Reader(std::fstream &file);
    PrimitiveType* getType();
	Storage<double> getParams();
private:
	Line str;
};