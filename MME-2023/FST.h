#pragma once

namespace FST
{
	struct RELATION
	{
		char symbol;
		short nnode;
		RELATION(char c = 0x00, short ns = 0);
	};

	struct NODE
	{
		short n_relation;
		RELATION* relations;
		NODE() ;
		NODE(short n, RELATION rel, ...);
	};

	struct FST
	{
		char* string;
		short position=0;
		short nstates;
		NODE* nodes;
		short* rstates;
		FST(char* s, short ns, NODE n, ...);
	};

	bool execute(FST& fst);
}