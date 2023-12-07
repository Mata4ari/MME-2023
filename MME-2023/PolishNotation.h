#pragma once

namespace PN 
{
	int getP(LT::Entry table);
	bool PolishNotation(int n, LT::LexTable& lextable, IT::IdTable& idtable);
	void getPolish(LT::LexTable& lextable, IT::IdTable& idtable);
}