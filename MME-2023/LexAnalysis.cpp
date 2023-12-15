#include "stdafx.h"
#include <sstream>
using namespace std;


bool hasMain = 0;
int LiteralCount = 0;
namespace Lex
{
	void Reading(const wchar_t infile[], LT::LexTable&ltable,IT::IdTable&itable,IT::FuncPrototype& funcs)
	{
		auto ifile = new std::ifstream;
		ifile->open(infile);
		if (!ifile->is_open())
			throw ERROR_THROW(114);


		char temp[TI_STR_MAXSIZE+3];
		char c;
		int count = 0;
		int sn = 1;
		bool isStrLiteral = 0;

		while (ifile->get(c))
		{
			if (count + 1 > TI_STR_MAXSIZE+3)
				throw ERROR_THROW(123);
			if (c == '\'')
			{
				if (isStrLiteral)
					isStrLiteral = 0;
				else
					isStrLiteral = 1;
			}

			if ((c == ' ' || c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '+' || c == '-' || c == '/' || c == '*' || c == '|' || c == '=')&&!isStrLiteral)
			{
				temp[count] = '\0';
				if (count != 0)
				{
					if (ltable.size + 1 > LT_MAXSIZE)
						throw ERROR_THROW(120);
					addLexem(temp, sn, ltable, itable,funcs);
					count = 0;
				}
				if (c != ' ' && c != '|')
				{
					if (ltable.size + 1 > LT_MAXSIZE)
						throw ERROR_THROW(120);
					addLexem(c, sn, ltable,itable);
				}
				if (c == '|')
				{
					sn++;
				}
				continue;
			}

			if (c != ' '||isStrLiteral)
			{
				temp[count] = c;
			}
			count++;
		}
		if (!hasMain)
			throw ERROR_THROW(132);
	}

	void addLexem(char c,int sn, LT::LexTable& ltable, IT::IdTable& itable)
	{
		if (c == ',')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_COMMA;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == ';')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_SEMICOLON;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '(')
		{
			if (ltable.table[ltable.size - 1].idxTI != TI_NULLIDX)
				if (itable.table[ltable.table[ltable.size - 1].idxTI].idtype != IT::F&& itable.table[ltable.table[ltable.size - 1].idxTI].idtype != IT::DF)
					throw ERROR_THROW_IN(138, sn, -1);
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_LEFTHESIS;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == ')')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_RIGHTHESIS;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '{')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_LEFTBRACELET;
			ltable.table[ltable.size].sn = sn;
			ltable.size++;
		}
		else if (c == '}')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_BRACELET;
			ltable.table[ltable.size].sn = sn;
			ltable.size++;
		}
		else if (c == '+')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_PLUS;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '-')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_MINUS;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '/')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_DIRSLASH;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '%')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_PROCENT;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '*')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_STAR;
			ltable.table[ltable.size].sn = sn;
			ltable.table[ltable.size].operatorValue = c;
			ltable.size++;
		}
		else if (c == '=')
		{
			ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
			ltable.table[ltable.size].lexema = LEX_EQUAL_SIGN;
			ltable.table[ltable.size].sn = sn;
			ltable.size++;
		}
		else
		{
			throw ERROR_THROW(123);
		}
	}

	void addLexem(char* temp, int sn, LT::LexTable& ltable, IT::IdTable& itable,IT::FuncPrototype&funcs)
	{
		if (temp[0]=='f')
		{
			FST::FST fst(FUNCTION(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_FUNCTION;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 'm')
		{
			FST::FST fst(MAIN(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = setMain(itable,temp,sn,ltable,funcs);
				ltable.table[ltable.size].lexema = LEX_MAIN;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 'u')
		{
			FST::FST fst(INTEGER(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_INTEGER;
				ltable.table[ltable.size].sn = sn;
				ltable.table[ltable.size].idDataType = LT::INT;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 'i')
		{
			FST::FST fst(IF_G(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_IF;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 'e')
		{
			FST::FST fst(ELSE_G(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_ELSE;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 's')
		{
			FST::FST fst(STRING(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_STRING;
				ltable.table[ltable.size].sn = sn;
				ltable.table[ltable.size].idDataType = LT::STR;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 'r')
		{
			FST::FST fst(RETURN(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_RETURN;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == 'w')
		{
			FST::FST fst(WRITE(temp));
			if (FST::execute(fst))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_WRITE;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
			FST::FST fst2(WRITE_LINE(temp));
			if (FST::execute(fst2))
			{
				ltable.table[ltable.size].idxTI = LT_TI_NULLIDX;
				ltable.table[ltable.size].lexema = LEX_WRITELINE;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == '\'')
		{
			FST::FST fst(STRING_LITERAL(temp));
			if (FST::execute(fst))
			{
				if (strlen(temp) > TI_STR_MAXSIZE+3)
					throw ERROR_THROW_IN(127, sn, -1);
				ltable.table[ltable.size].idxTI = setStrLiteral(itable, temp, sn,ltable,funcs);
				ltable.table[ltable.size].lexema = LEX_LITERAL;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		else if (temp[0] == '0'|| temp[0] == '1'||temp[0] == '2' || temp[0] == '3' || temp[0] == '4' || temp[0] == '5' || 
			temp[0] == '6' || temp[0] == '7' || temp[0] == '8' || temp[0] == '9')
		{
			FST::FST fst(INTEGER_LITERAL(temp));
			if (FST::execute(fst))
			{
				if (strlen(temp) > TI_INT_MAXSIZE)
					throw ERROR_THROW_IN(124, sn, -1);
				ltable.table[ltable.size].idxTI = setIntLiteral(itable,temp,sn,ltable,funcs);
				ltable.table[ltable.size].lexema = LEX_LITERAL;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
			FST::FST fst2(INTEGER_LITERAL16(temp));
			if (FST::execute(fst2))
			{
				if (strlen(temp) > TI_INT_MAXSIZE)
					throw ERROR_THROW_IN(124, sn, -1);
				ltable.table[ltable.size].idxTI = setIntLiteral(itable, temp, sn, ltable, funcs);
				ltable.table[ltable.size].lexema = LEX_LITERAL;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
				return;
			}
		}
		
			FST::FST fst(IDENTIFICATOR(temp));
			if (FST::execute(fst))
			{
				if (strlen(temp) > ID_MAXSIZE)
					throw ERROR_THROW_IN(121, sn, -1);
				if (itable.size + 1 > TI_MAXSIZE)
					throw ERROR_THROW(122);
				ltable.table[ltable.size].idxTI = setIdentificator(itable, ltable, temp, sn,funcs);
				ltable.table[ltable.size].lexema = LEX_ID;
				ltable.table[ltable.size].sn = sn;
				ltable.size++;
			}
			else
			{
				throw ERROR_THROW_IN(123, sn, -1)
			}
	}

	int setStrLiteral(IT::IdTable& itable,char *temp,int sn,LT::LexTable&ltable,IT::FuncPrototype&funcs)
	{
		IT::Entry entry;

		entry.idtype = IT::L;
		entry.iddatatype = IT::STR;
		entry.value.vstr.len = strlen(temp)-1;
		strcpy_s(entry.value.vstr.str, temp);
		strcpy_s(entry.pref, IT::findPrefix(funcs));
		int id = IT::findFirstLiteral(entry.value.vstr.len,entry.value.vstr.str,itable);
		if (id != -1)
		{
			return id;
		}
		else
		{
			_itoa_s(LiteralCount, entry.id, 10);
			LiteralCount++;
			entry.idxfirstLE = ltable.size;
			itable.table[itable.size] = entry;
		}
		itable.size++;
		return itable.size - 1;
	}

	int setIntLiteral(IT::IdTable& itable, char* temp, int sn, LT::LexTable& ltable, IT::FuncPrototype& funcs)
	{
		IT::Entry entry;
		unsigned int x;

		if (temp[1]=='x')
		{
			sscanf_s(temp, "%x", &x);
		}
		else
		{
			sscanf_s(temp, "%u", &x);
		}
		if (x > 4294967295)
			throw ERROR_THROW_IN(130, sn, -1);

		entry.idtype = IT::L;
		entry.iddatatype = IT::INT;
		entry.value.vint = x;
		strcpy_s(entry.pref, IT::findPrefix(funcs));
		int id = IT::findFirstLiteral(x,itable);
		if (id != -1)
		{
			return id;
		}
		else
		{
			_itoa_s(LiteralCount, entry.id, 10);
			LiteralCount++;
			entry.idxfirstLE = ltable.size;
			itable.table[itable.size] = entry;
		}
		itable.size++;
		return itable.size - 1;
	}

	int setIdentificator(IT::IdTable& itable,LT::LexTable& ltable, char* temp, int sn,IT::FuncPrototype&funcs)
	{
		IT::Entry entry;
		strcpy_s(entry.id, temp);
		if (LT::GetEntry(ltable, ltable.size - 1).lexema == LEX_FUNCTION)
		{
			entry.idtype = IT::DF;
			entry.pref[0] ='\0';
			if (IT::findFirstLT(temp, entry.pref, itable) == -1)
			{
				entry.idxfirstLE = ltable.size;
			}
			else
			{
				throw ERROR_THROW_IN(125, sn, -1);
			}
			if (LT::GetEntry(ltable, ltable.size - 2).lexema == LEX_INTEGER&& LT::GetEntry(ltable, ltable.size - 2).idDataType==LT::INT)
				entry.iddatatype = IT::INT;
			else if (LT::GetEntry(ltable, ltable.size - 2).lexema == LEX_STRING&& LT::GetEntry(ltable, ltable.size - 2).idDataType == LT::STR)
				entry.iddatatype = IT::STR;
			else
				throw ERROR_THROW_IN(131, sn, -1);

			strcpy_s(funcs.table[funcs.size].id, temp);
			funcs.table[funcs.size].retType = entry.iddatatype;
			funcs.table[funcs.size].idTI = itable.size;
			funcs.size++;

			itable.table[itable.size] = entry;

			itable.size++;
			return itable.size - 1;
		}

		if (LT::isParm(ltable,itable))
		{
			entry.idtype = IT::P;
			strcpy_s(entry.pref, IT::findPrefix(funcs));
			if (IT::findFirstLT(temp, entry.pref, itable) != -1)
				throw ERROR_THROW_IN(125, sn, -1);
			if (LT::GetEntry(ltable, ltable.size - 1).lexema == LEX_INTEGER&& LT::GetEntry(ltable, ltable.size - 1).idDataType == LT::INT)
			{
				entry.iddatatype = IT::INT;
				entry.value.vint = TI_INT_DEFAULT;
			}
			else if (LT::GetEntry(ltable, ltable.size - 1).lexema == LEX_STRING&& LT::GetEntry(ltable, ltable.size - 1).idDataType == LT::STR)
			{
				entry.iddatatype = IT::STR;
				entry.value.vstr.len = TI_STR_DEFAULT;
			}
			else
				throw ERROR_THROW_IN(131, sn, -1);
			entry.idxfirstLE = ltable.size;

			if (funcs.table[funcs.size - 1].numParms + 1 > 4)
				throw ERROR_THROW_IN(133, sn, -1);
			funcs.table[funcs.size-1].parms[funcs.table[funcs.size-1].numParms] = entry.iddatatype;
			funcs.table[funcs.size - 1].numParms++;

			itable.table[itable.size] = entry;

			itable.size++;
			return itable.size - 1;
		}

		strcpy_s(entry.pref, IT::findPrefix(funcs));
		int firstLT = IT::findFirstLT(temp, entry.pref, itable);
		if (firstLT == -1)
		{
			IT::FuncPrototype::Func* prototype = findProt(temp,funcs);
			if (prototype!=nullptr)
			{
				entry.idtype = IT::F;
				if (prototype->idTI == -1)
				{
					entry.iddatatype = prototype->retType;
					entry.idxfirstLE = ltable.size;
					entry.inlib = 1;
				}
				else
				{
					entry.iddatatype = prototype->retType;
					entry.idxfirstLE = ltable.size;
				}
			}
			else
			{
				entry.idtype = IT::V;
				if (LT::GetEntry(ltable, ltable.size - 1).lexema == LEX_INTEGER&& LT::GetEntry(ltable, ltable.size - 1).idDataType == LT::INT)
				{
					entry.iddatatype = IT::INT;
					entry.value.vint = TI_INT_DEFAULT;
				}
				else if (LT::GetEntry(ltable, ltable.size - 1).lexema == LEX_STRING&& LT::GetEntry(ltable, ltable.size - 1).idDataType == LT::STR)
				{
					entry.iddatatype = IT::STR;
					entry.value.vstr.len = TI_STR_DEFAULT;
				}
				else
					throw ERROR_THROW_IN(126, sn, -1);
				entry.idxfirstLE = ltable.size;
			}
		}
		else
		{
			if (LT::GetEntry(ltable, ltable.size - 1).lexema == LEX_INTEGER)
				throw ERROR_THROW_IN(136, sn, -1);
			return ltable.table[firstLT].idxTI;
		}
		itable.table[itable.size] = entry;
		itable.size++;
		return itable.size - 1;
	}

	int setMain(IT::IdTable& itable, char* temp, int sn,LT::LexTable& ltable,IT::FuncPrototype&funcs)
	{
		strcpy_s(itable.table[itable.size].id, temp);
		itable.table[itable.size].idtype = IT::DF;
		itable.table[itable.size].pref[0] = '\0';
		if (IT::findFirstLT(temp, itable.table[itable.size].pref, itable) == -1)
		{
			itable.table[itable.size].idxfirstLE = ltable.size;
		}
		else
		{
			throw ERROR_THROW_IN(129, sn, -1);
		}
		itable.table[itable.size].iddatatype = IT::INT;

		strcpy_s(funcs.table[funcs.size].id, temp);
		funcs.table[funcs.size].retType = itable.table[itable.size].iddatatype;
		funcs.size++;

		hasMain=1;
		itable.size++;
		return itable.size - 1;
	}

	IT::FuncPrototype::Func* findProt(char* id, IT::FuncPrototype& funcs)
	{
		for (int i = 0; i < funcs.size; i++)
		{
			if (strcmp(id, funcs.table[i].id) == 0)
				return &funcs.table[i];
		}
		return nullptr;
	}

}
