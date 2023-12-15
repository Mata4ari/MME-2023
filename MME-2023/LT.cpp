#include "stdafx.h"


namespace LT 
{
    LexTable::LexTable(int size)
    {
        //if(size>LT_MAXSIZE)

        this->maxsize = size;
        this->size = 0;
        this->table = new Entry[size];
    }

    Entry& GetEntry(LexTable& lextable, int n)
    {
        return lextable.table[n];
    }

    void Delete(LexTable& lextable)
    {
        delete[] lextable.table;
    }

    bool isParm(LexTable& ltable,IT::IdTable& itable)
    {
        for (int i = ltable.size - 1; i >= 0; i--)
        {
            if (ltable.table[i].lexema == ')')
                return false;
            if (ltable.table[i].lexema == '(')
            {
                if(ltable.table[i-1].lexema==LEX_ID)
                {
                    if (itable.table[ltable.table[i - 1].idxTI].idtype == IT::DF)
                        return true;
                    else
                        return false;
                }
            }
        }
        return false;
    }


    void PrintLexTable(LexTable& ltable)
    {
        int k = 1;
        std::ofstream f("TableLex.txt");
        if (!f.is_open())
           throw ERROR_THROW(128);
        f << k << " ";
        for (int i = 0; i < ltable.size; i++)
        {
            if (true)
            {
                if (ltable.table[i].lexema == 'v')
                {
                    f << ltable.table[i].operatorValue;
                }
                else
                {
                    f << ltable.table[i].lexema;
                }
            }
            if (ltable.table[i].sn < ltable.table[i + 1].sn)
            {
                k++;
                f << std::endl;
                f << k << " ";
            }
        }
        f <<std:: endl;
        f.close();
    }
}
