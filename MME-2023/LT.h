#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffffff
#define LEX_INTEGER 't'
#define LEX_STRING 't'
#define LEX_ID 'i'
#define LEX_LITERAL 'l'
#define LEX_MAIN 'm'
#define LEX_FUNCTION 'f'
#define LEX_RETURN 'r'
#define LEX_WRITE 'p'
#define LEX_WRITELINE 'w'
#define LEX_IF '?'
#define LEX_ELSE 'e'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACELET '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS 'v'
#define LEX_MINUS 'v'
#define LEX_STAR 'v'
#define LEX_DIRSLASH 'v'
#define LEX_PROCENT 'v'
#define	LEX_EQUAL_SIGN	'='

namespace LT
{
	enum IDDATATYPE { INT = 1, STR = 2 };
	struct Entry
	{
		char lexema;
		int sn;
		int idxTI;
		int idxLT = 0;
		IDDATATYPE idDataType;
		char operatorValue='n';
		Entry()
		{
			lexema = 0;
			sn = 0;
			idxTI = 0;
		}
		Entry(char lex, int sn, int idLT, int idTI)
		{
			lexema = lex;
			this->sn = sn;
			idxTI = idTI;
			idxLT = idLT;
		}
	};

	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		LexTable()
		{
			this->maxsize = LT_MAXSIZE;
			this->size = 0;
			this->table = new Entry[LT_MAXSIZE];
		};
		LexTable (int size);
	};

	Entry& GetEntry(LexTable& lextable, int n);
	void Delete(LexTable& lextable);
	bool isParm(LexTable& ltable, IT::IdTable& itable);
	void PrintLexTable(LexTable& ltable);
}