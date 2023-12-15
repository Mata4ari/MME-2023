#pragma once

namespace SA 
{
	void checkParms(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs);
	void Initialize(LT::LexTable& ltable, IT::IdTable& itable);
	void checkTypes(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs);
	bool isValidType(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs, int n);
}