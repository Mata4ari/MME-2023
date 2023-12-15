#include "stdafx.h"

namespace PN {
	void getPolish(LT::LexTable& lextable, IT::IdTable& idtable)
	{
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].lexema == '='|| lextable.table[i].lexema == 'r'||lextable.table[i].lexema == 'p' || lextable.table[i].lexema == 'w'  )
			{
				PolishNotation(i + 1, lextable, idtable);
			}
			if(lextable.table[i].lexema == '?')
			{
				int j = i;
				LT::Entry temp;
				for (; j < lextable.size; j++)
				{
					if (lextable.table[j].lexema == '{')
					{
						temp = lextable.table[j-1];
						lextable.table[j-1].lexema = ';';
						break;
					}
				}
				PolishNotation(i + 2, lextable, idtable);
				j = i + 2;
				while (lextable.table[j].lexema != ';')
					j++;
				lextable.table[j] = temp;
			}
		}
	}

	bool PolishNotation(int n, LT::LexTable& lextable, IT::IdTable& idtable)
	{

		std::queue<LT::Entry> current;
		std::stack<LT::Entry> stack;

		int i = n;
		int priority;
		int parCount = 0;
		int indID = -1;

		while (lextable.table[i].lexema != ';')
		{
			priority = getP(lextable.table[i]);

			if (lextable.table[i].lexema == 'i' && lextable.table[i + 1].lexema == '(') 
			{
				indID = lextable.table[i].idxTI;
				i++;
				priority = getP(lextable.table[i]);
				while (priority < 2)
				{
					if (priority == 0)
					{
						current.push(lextable.table[i]);
						parCount++;
					}
					else if (priority == 1)stack.push(lextable.table[i]);
					else if (priority == -2);
					else if (priority == -1)
					{
						while (getP(stack.top()) != 1)			
						{
							current.push(stack.top());
							stack.pop();
						}
						stack.pop();
						current.push({ '@', lextable.table[i].sn, lextable.table[i].idxLT, indID });
						i++;
						priority = getP(lextable.table[i]);
						break;
					}

					i++;
					priority = getP(lextable.table[i]);
				}
			}

			if (priority == 0) current.push(lextable.table[i]);
			else if (priority == 1) stack.push(lextable.table[i]);
			else if (priority == 2 || priority == 3)
			{
				while (!stack.empty())
				{
					if (getP(stack.top()) >= priority)
					{
						current.push(stack.top());
						stack.pop();
					}
					else break;
				}
				stack.push(lextable.table[i]);
			}
			else if (priority == -1)
			{
				if(!stack.empty())
				{
					while (getP(stack.top()) != 1)			
					{
						current.push(stack.top());
						stack.pop();
					}
					stack.pop();
				}
			}
			else if (priority == -3) break;
			i++;
		}
		while (!stack.empty())
		{
			current.push(stack.top());
			stack.pop();
		}
		current.push(lextable.table[i]);
		


		int posLast = i; 
		i = n;

		for (i; i <= posLast; i++) {
			lextable.table[i] = { '#' , lextable.table[i].sn , i , -1};
			while (!current.empty())
			{
				lextable.table[i] = current.front();
				lextable.table[i].idxLT = i;
				current.pop();
				i++;
			}
			if(current.empty()&&i<=posLast)lextable.table[i] = { '#' , lextable.table[i].sn , i , -1 };
		}
		return true;
	}

	int getP(LT::Entry table)
	{
		char token = table.lexema;

		if (token == 'v') token = table.operatorValue;
		
		if (token == '*' || token == '/' || token == '%') return 3;
		else if (token == '+' || token == '-') return 2;
		else if (token == '(') return 1;
		else if (token == ')') return -1;
		else if (token == ',') return -2;
		else if (token == ';') return -3;
		else return 0;
	}
}