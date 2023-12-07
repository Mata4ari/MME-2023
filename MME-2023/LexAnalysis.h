#pragma once
#include "IT.h"
#include "LT.h"

namespace Lex
{
	void Reading(wchar_t infile[], LT::LexTable& ltable, IT::IdTable& itable);
	void addLexem(char c, int sn, LT::LexTable& ltable);
	void addLexem(char* temp, int sn, LT::LexTable& ltable, IT::IdTable& itable, IT::FuncPrototype& funcs);
	int setStrLiteral(IT::IdTable& itable, char* temp, int sn, LT::LexTable& ltable, IT::FuncPrototype& funcs);
	int setIntLiteral(IT::IdTable& itable, char* temp, int sn, LT::LexTable& ltable, IT::FuncPrototype& funcs);
	int setIdentificator(IT::IdTable& itable, LT::LexTable& ltable, char* temp, int sn, IT::FuncPrototype& funcs);
	int setMain(IT::IdTable& itable, char* temp, int sn, LT::LexTable& ltable, IT::FuncPrototype& funcs);
	void checkParms(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs);
	IT::FuncPrototype::Func* findProt(char* id, IT::FuncPrototype& funcs);
}