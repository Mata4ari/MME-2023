#include "stdafx.h"
using namespace std;

namespace IT 
{
    IdTable::IdTable (int size)
    {
        //if(size > TI_MAXSIZE)

        this->maxsize = size;
        this->size = 0;
        this->table = new Entry[size];
    }
    void Add(IdTable& idtable, Entry& entry)
    {
        if (idtable.size + 1 > TI_MAXSIZE)
            throw ERROR_THROW(122);
        idtable.table[idtable.size] = entry;
        idtable.size++;
    }
    Entry GetEntry(IdTable& idtable, int n)
    {
        return idtable.table[n];
    }

    int IsId(IdTable& idtable, char id[ID_MAXSIZE],char pref[ID_MAXSIZE])
    {
        for (int i = 0; i < idtable.size; i++)
        {
                if (idtable.table[i].idtype==F)
                {
                    if (strcmp(idtable.table[i].id, id) == 0)
                    {
                            return i;
                    }
                }
                if (strcmp(idtable.table[i].id, id) == 0)
                {
                    if (strcmp(idtable.table[i].pref, pref) == 0)
                        return i;
                }
        }
        
        return TI_NULLIDX;
    }

    void Delete(IdTable& idtable)
    {
        delete[] idtable.table;
    }

    char* findPrefix(FuncPrototype& funcs)
    {
        return funcs.table[funcs.size - 1].id;
    }

    int findFirstLT(char*id,char*pref,IdTable& itable)
    {
        for (int i = 0; i < itable.size; i++)
        {
            if (strcmp(id, itable.table[i].id)==0)
            {
                if (strcmp(pref, itable.table[i].pref) == 0 )
                    return itable.table[i].idxfirstLE;
            }
        }
        return -1;
    }

    int findFunc(char* id,int sn, IdTable& itable)
    {
        for (int i = 0; i < itable.size; i++)
        {
            if (strcmp(id, itable.table[i].id) == 0)
            {
                if (itable.table[i].idtype == DF)
                {
                    return i;
                }
            }
        }
        return -1;
    }

    void PrintIdTable(IdTable& itable)
    {
        ofstream f("TableId.txt");
        if (!f.is_open())
            throw ERROR_THROW(128);
        for (int i = 0; i < itable.size; i++)
        {
            if (itable.table[i].idtype == L|| itable.table[i].idtype == V|| itable.table[i].idtype == P)
            {
                if(itable.table[i].iddatatype==INT)
                    f << itable.table[i].pref << "\t" << itable.table[i].id << "\t" << itable.table[i].iddatatype << "\t" << itable.table[i].idtype << "\t" << itable.table[i].idxfirstLE << "\t" << itable.table[i].value.vint << endl;
                if (itable.table[i].iddatatype == STR)
                {
                    f << itable.table[i].pref << "\t" << itable.table[i].id << "\t" << itable.table[i].iddatatype << "\t" << itable.table[i].idtype << "\t" << itable.table[i].idxfirstLE << "\t" << itable.table[i].value.vstr.len << "\t";
                    if(itable.table[i].idtype == L)
                    {
                        f << itable.table[i].value.vstr.str;
                    }
                        f<< endl;
                }
                continue;
            }
            f << itable.table[i].pref<<"\t" << itable.table[i].id << "\t" << itable.table[i].iddatatype << "\t" << itable.table[i].idtype << "\t" << itable.table[i].idxfirstLE << endl;
        }
        f.close();
    }
}
