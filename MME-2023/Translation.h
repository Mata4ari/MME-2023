#pragma once 

namespace TR
{
	void translation(wchar_t outfile[], LT::LexTable ltable, IT::IdTable itable, IT::FuncPrototype& funcs);
	void codeTranslation(std::ofstream* f, LT::LexTable ltable, IT::IdTable itable, IT::FuncPrototype& funcs);
}