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

    void Add(LexTable& lextable, Entry entry)
    {
        if (lextable.size + 1 > LT_MAXSIZE)
            throw ERROR_THROW(120);
        lextable.table[lextable.size] = entry;
        lextable.size++;
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
            if (ltable.table[i].lexema != '#')
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

    void Initialize(LexTable& ltable, IT::IdTable& itable)
    {
        for (int i = 0; i < ltable.size; i++)
        {
            if (ltable.table[i].lexema == '=')
            {
                if (ltable.table[i - 2].lexema != 't')
                    continue;
                bool initializable = 1;
                for (int j = i; ltable.table[j].lexema != ';'; j++)
                {
                    if (ltable.table[j].idxTI == TI_NULLIDX)
                        continue;
                    if (itable.table[ltable.table[j].idxTI].idtype == IT::L || itable.table[ltable.table[j].idxTI].idtype == IT::V)
                    {
                        if (itable.table[ltable.table[j].idxTI].idtype == IT::V)
                        {
                            if (itable.table[ltable.table[j].idxTI].iddatatype == IT::INT)
                            {
                                if (itable.table[ltable.table[j].idxTI].value.vint == TI_INT_DEFAULT)
                                {
                                    initializable = 0;
                                    break;
                                }
                            }
                            if (itable.table[ltable.table[j].idxTI].iddatatype == IT::STR)
                            {
                                if (itable.table[ltable.table[j].idxTI].value.vstr.len == TI_STR_DEFAULT)
                                {
                                    initializable = 0;
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        initializable = 0;
                        break;
                    }
                }

                if (initializable)
                {
                    if (ltable.table[i+2].lexema==';')
                    {
                        LT::Entry temp = ltable.table[i + 2];
                        if (itable.table[ltable.table[i-1].idxTI].iddatatype == IT::INT)
                        {
                            itable.table[ltable.table[i - 1].idxTI].value = itable.table[ltable.table[i + 1].idxTI].value;
                            ltable.table[i] = temp;
                            ltable.table[i + 1] = { '#' , ltable.table[i].sn , i , -1 };
                            ltable.table[i+2] = { '#' , ltable.table[i].sn , i , -1 };
                        }
                        if (itable.table[ltable.table[i-1].idxTI].iddatatype == IT::STR)
                        {
                            itable.table[ltable.table[i - 1].idxTI].value = itable.table[ltable.table[i + 1].idxTI].value;
                            ltable.table[i] = temp;
                            ltable.table[i + 1] = { '#' , ltable.table[i].sn , i , -1 };
                            ltable.table[i + 2] = { '#' , ltable.table[i].sn , i , -1 };
                        }
                    }
                    else
                    {
                        /*for (int j = i; ltable.table[j].lexema != ';'; j++)
                        {

                        }*/
                    }
                }

            }
        }
    }
}
