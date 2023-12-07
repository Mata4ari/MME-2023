﻿#pragma once
#include "GRB.h"

#define GRB_ERROR_SERIES 600
#define NS(n) GRB::Rule::Chain::N(n)
#define TS(n) GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'),				//стартовый символ, дно стека
		7,											//количество правил
		Rule(NS('S'), GRB_ERROR_SERIES + 0,			//Неверная структура программы
			3,		
			Rule::Chain(4, TS('m'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(10, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), NS('S'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,			//Операторы программы
			8,		
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(4, TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(6, TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('w'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(8, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('Q'), TS('}'), NS('N')),
			Rule::Chain(12, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('Q'), TS('}'), TS('e'), TS('{'), NS('Q'), TS('}'),NS('N'))
		),
		Rule(NS('Q'), GRB_ERROR_SERIES + 5,			//Операторы внутри if-else
			11,		
			Rule::Chain(3, TS('r'), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('Q')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('Q')),
			Rule::Chain(4, TS('w'), NS('E'), TS(';'), NS('Q')),
			Rule::Chain(8, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('Q'), TS('}'), NS('Q')),
			Rule::Chain(12, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('Q'), TS('}'), TS('e'), TS('{'), NS('Q'), TS('}'), NS('Q')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(3, TS('w'), NS('E'), TS(';')),
			Rule::Chain(7, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('Q'), TS('}')),
			Rule::Chain(11, TS('?'), TS('('), NS('E'), TS(')'), TS('{'), NS('Q'), TS('}'), TS('e'), TS('{'), NS('Q'), TS('}'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,			//Выражение
			9,		
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(3, TS('i'), TS('('), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 3,			//Подвыражение для аргументов функции
			4,		//W	→	i	|	l	|	i,W	|	l,W
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,			//Параметры функции
			2,		//F	→	ti	|	ti,F
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 2,			//Выражение
			2,		//M →		vE	|	vEM
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		)
	);
}
