#include "stdafx.h"

namespace In
{
	INP getin(wchar_t infile[])
	{
		setlocale(LC_ALL, "rus");
		INP inp;
		
		std::ifstream ifile;
		ifile.open(infile);
		if (!ifile.is_open())
			throw ERROR_THROW(110);

		char c;
		unsigned char ch, temp = 'z';

		int position = 0;
		inp.text = new unsigned char[IN_MAX_LEN_TEXT];
		while (ifile.get(c))
		{
			ch = c;
			if (ch == IN_CODE_ENDL)
			{
				inp.lines++;
				position = 0;
			}
			if (inp.code[ch] == INP::F)
			{
				std::cout << ch;
				inp.size++;
				throw ERROR_THROW_IN(111, inp.lines, position + 1);
			}
			else if (inp.code[ch] == INP::I)
			{
				position++;
				inp.ignore++;
			}
			else if (inp.code[ch] == INP::T)
			{
				if (!(ch == ' ' && temp == ' '))
				{
					if ((ch == ',' || ch == ';' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '+' || ch == '-' || ch == '/' || ch == '*' ||ch == '=')&&temp==' ')
					{
						inp.text[inp.size-1] = ch;
						temp = ch;
						continue;
					}
					if((temp == ',' || temp == ';' || temp == '(' || temp == ')' || temp == '{' || temp == '}' || temp == '+' || temp == '-' || temp == '/' || temp == '*' || temp == '='|| temp == '\n') && ch == ' ')
					{
						continue;
					}
					position++;
					inp.text[inp.size] = ch;
					inp.size++;
				}
			}
			else
			{
				if (temp == ' ')
				{
					inp.text[inp.size-1] = inp.code[ch];
					temp = inp.code[ch];
					continue;
				}
				position++;
				inp.text[inp.size] = inp.code[ch];
				inp.size++;
			}
			temp = c;
		}

		inp.text[inp.size] = '\0';
		ifile.close();
		return inp;
	}
}
