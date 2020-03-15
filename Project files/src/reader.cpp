#include <iostream>

#include "reader.h"

//тут много кода, но зато без string

int length(char* word) 
{
	int len = 0;
	while (word[len] != '\0')
		++len;
	return len;
}

int length(const char* word)
{
	int len = 0;
	while (word[len] != '\0')
		++len;
	return len;
}

bool equals(char* word1, const char* word2)
{
	int len1 = length(word1);
	int len2 = length(word2);

	if (len1 != len2) return false;

	for (int i = 0; i < len1; ++i)
		if (word1[i] != word2[i]) return false;

	return true;
}

Line::Line()
{
	str = new char[1];
	str[0] = '\0';
	len = 0;
}

Line::~Line()
{
	delete[] str;
}

char* Line::getLine()
{
	delete[] str;

	int newlen = 0;
	char buf[100];
	std::cin.getline(buf, sizeof(buf));
	for (int i = 0; (i < 100) && (buf[i] != '\0'); ++i)
		++newlen;
	len = newlen;
	str = new char[len + 1];
	str[len] = '\0';
	for (int i = 0; i < len; ++i)
		str[i] = buf[i];
	return str;
}

char* Line::getLine(std::fstream& file)
{
	delete[] str;

	int newlen = 0;
	char buf[100];
	file.getline(buf, sizeof(buf));
	for (int i = 0; (i < 100) && (buf[i] != '\0'); ++i)
		++newlen;
	len = newlen;
	str = new char[len + 1];
	str[len] = '\0';
	for (int i = 0; i < len; ++i)
		str[i] = buf[i];
	return str;
}

char* Line::getFirstWord()
{
	char* word;
	int wordlen = 0, begin = 0;
	while ((begin < len) && (str[begin] == ' ')) ++begin;
	for (int i = begin; (i < len) && (str[i] != ' '); ++i)
		++wordlen;
	word = new char[wordlen + 1];
	word[wordlen] = '\0';
	for (int i = begin; i < begin + wordlen; ++i)
		word[i - begin] = str[i];
	return word;
}

Storage<double> Line::getNumbers()  //достает все числа из строки
{
	int begin = -1, end = -1, t = 0;
	double num;
	Storage<double> numbers;

	for (int i = 0; i < len; ++i)
	{
		if (((str[i] >= '0') && (str[i] <= '9')) || ((begin == -1) && (str[i] == '-')))
		{
			if ((begin == -1) && (end == -1))
				begin = i;
			if (i == len - 1)
			{
				end = i;
				if ((begin > -1) && !((begin == end) && (str[begin] == '-')))
				{
					num = createNumber(begin, end);
					numbers.add(num);
				}
			}
		}
		else
		{
			if (!((str[i] == '.') && (t == 0)))
			{
				end = i - 1;
				if ((begin > -1) && !((begin == end) && (str[begin] == '-')))
				{
					num = createNumber(begin, end);
					numbers.add(num);
				}
				begin = end = -1;
				t = 0;
			}
			else if (str[i] == '.')
				t = 1;
		}
	}

	return numbers;
}

double Line::createNumber(int beg, int en) //кусок строки, содержащий число, преобразует в double
{
	size_t len = en - beg + 1;
	char* strnum = new char[len + 1];

	for (int i = beg; i <= en; ++i)
		strnum[i - beg] = str[i];
	strnum[len] = '\0';

	double num = atof(strnum);
	delete[] strnum;

	return num;
}



Reader::Reader()
{
	str.getLine();
}

Reader::Reader(std::fstream &file)
{
	str.getLine(file);
}

PrimitiveType* Reader::getType()
{
	PrimitiveType* type = nullptr;
	char* word;

	word = str.getFirstWord();

	if (equals(word, "Point"))
	{
		type = new PrimitiveType;
		*type = P_Point;
	}
	if (equals(word, "Segment"))
	{
		type = new PrimitiveType;
		*type = P_Segment;
	}
	if (equals(word, "Circle"))
	{
		type = new PrimitiveType;
		*type = P_Circle;
	}

	return type;
}

Storage<double> Reader::getParams()
{
	return str.getNumbers();
}