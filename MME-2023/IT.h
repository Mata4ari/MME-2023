#pragma once
#define ID_MAXSIZE 5
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x00000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffffff
#define TI_STR_MAXSIZE 127
#define TI_INT_MAXSIZE 10
#define FUNC_MAXSIZE 50

namespace IT
{
	enum IDDATATYPE {INT=1,STR=2};
	enum IDTYPE {DF=0,V=1,F=2,P=3,L=4};

	struct Entry
	{
		int idxfirstLE;
		char id[ID_MAXSIZE+1];
		char pref[ID_MAXSIZE+1];
		IDDATATYPE iddatatype;
		IDTYPE idtype;

		union
		{
			unsigned int vint;
			struct
			{
				int len;
				char str[TI_STR_MAXSIZE + 1];
			} vstr;
		} value;
	};

	struct FuncPrototype
	{
		int size=0;
		struct Func
		{
			int idTI = -1;
			char id[ID_MAXSIZE + 1];
			int numParms = 0;
			IDDATATYPE parms[4];
			IDDATATYPE retType;
		};
		Func table[FUNC_MAXSIZE];
		FuncPrototype()
		{
			strcpy_s(this->table[this->size].id, "rand");
			this->table[this->size].numParms = 2;
			this->table[this->size].retType = INT;
			this->table[this->size].parms[0] = INT;
			this->table[this->size].parms[1] = INT;
			this->size++;
		}
	};

	struct IdTable
	{
		IdTable(int size);
		int maxsize;
		int size;
		Entry* table;
	};

	Entry GetEntry(IdTable& idtable, int n);
	int IsId(IdTable& idtable, char id[ID_MAXSIZE], char pref[ID_MAXSIZE]);
	void Delete(IdTable& idtable);
	void PrintIdTable(IdTable& itable);
	char* findPrefix(FuncPrototype& funcs);
	int findFirstLT(char* id, char* pref, IdTable& itable);
	int findFunc(char* id, int sn, IdTable& itable);
}