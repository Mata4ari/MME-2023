#include "stdafx.h"

namespace SA
{
	void checkParms(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs)
	{
		int numParms = 0;
		for (int i = 0; i < ltable.size; i++)
		{
			if (ltable.table[i].idxTI != LT_TI_NULLIDX)
				if (itable.table[ltable.table[i].idxTI].idtype == IT::F)
				{
					numParms = 0;
					IT::FuncPrototype::Func* func = Lex::findProt(itable.table[ltable.table[i].idxTI].id, funcs);
					if (func == nullptr)
						throw ERROR_THROW(126, ltable.table[i].sn);

					if (func->numParms == 0)
						continue;
					if (func->numParms == 1)
					{
						if (ltable.table[i + 2].idxTI == LT_TI_NULLIDX)
							throw ERROR_THROW_IN(134, ltable.table[i + 2].sn, -1);
						if (itable.table[ltable.table[i + 2].idxTI].iddatatype != func->parms[0])
							throw ERROR_THROW_IN(134, ltable.table[i + 2].sn, -1);
					}
					if (func->numParms > 1)
					{
						if (ltable.table[i + 2].idxTI == LT_TI_NULLIDX)
							throw ERROR_THROW_IN(134, ltable.table[i + 2].sn, -1);
						if (itable.table[ltable.table[i + 2].idxTI].iddatatype != func->parms[0])
							throw ERROR_THROW_IN(134, ltable.table[i + 2].sn, -1);
						numParms++;
						for (int j = i; ltable.table[j].lexema != ')'; j++)
						{
							if (ltable.table[j].lexema == ',')
							{
								if (ltable.table[j + 1].idxTI == LT_TI_NULLIDX)
									throw ERROR_THROW_IN(134, ltable.table[j + 1].sn, -1);
								if (itable.table[ltable.table[j + 1].idxTI].iddatatype != func->parms[numParms])
									throw ERROR_THROW_IN(134, ltable.table[j + 1].sn, -1);
								numParms++;
							}
						}
						if (numParms != func->numParms)
							throw ERROR_THROW_IN(134, ltable.table[i].sn, -1);
					}
				}
		}
	}

    void Initialize(LT::LexTable& ltable, IT::IdTable& itable)
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
                    if (itable.table[ltable.table[j].idxTI].idtype == IT::F)
                    {
                        initializable = 0;
                        break;
                    }
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
                    if (ltable.table[i + 2].lexema == ';')
                    {
                        LT::Entry temp = ltable.table[i + 2];
                        if (itable.table[ltable.table[i - 1].idxTI].iddatatype == IT::INT)
                        {
                            itable.table[ltable.table[i - 1].idxTI].value = itable.table[ltable.table[i + 1].idxTI].value;
                            ltable.table[i] = temp;
                            ltable.table[i + 1] = { '#' , ltable.table[i].sn , i , -1 };
                            ltable.table[i + 2] = { '#' , ltable.table[i].sn , i , -1 };
                        }
                        if (itable.table[ltable.table[i - 1].idxTI].iddatatype == IT::STR)
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

    void checkTypes(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs)
    {
        for (int i = 0; i < ltable.size; i++)
        {
            if (ltable.table[i].lexema == '=' || ltable.table[i].lexema == 'r'|| ltable.table[i].lexema == '?'|| ltable.table[i].lexema == 'p' || ltable.table[i].lexema == 'w' )
            {
                if (!isValidType(itable, ltable, funcs, i))
                    throw ERROR_THROW_IN(136, ltable.table[i].sn, -1);
            }
        }
    }

    bool isValidType(IT::IdTable& itable, LT::LexTable& ltable, IT::FuncPrototype& funcs,int n)
    {
        IT::IDDATATYPE type;
        if (ltable.table[n].lexema == '?')
        {
            type = type = itable.table[ltable.table[n + 2].idxTI].iddatatype;
            for (int i = n; ltable.table[i].lexema != '{'; i++)
            {
                if (ltable.table[i].lexema == 'v')
                    if (type == IT::STR)
                        throw ERROR_THROW_IN(137, ltable.table[i].sn, -1);
                if (ltable.table[i].idxTI != TI_NULLIDX)
                {
                    if (itable.table[ltable.table[i].idxTI].idtype == IT::F)
                    {
                        if (itable.table[ltable.table[i].idxTI].iddatatype != type)
                            return 0;
                        while (ltable.table[i].lexema != ')')
                            i++;
                        continue;
                    }
                    if (itable.table[ltable.table[i].idxTI].iddatatype != type)
                        return 0;
                }
            }
            return 1;
        }

        if(ltable.table[n].lexema=='=')
            type = itable.table[ltable.table[n - 1].idxTI].iddatatype;
        if(ltable.table[n].lexema=='r')
        {
            type = itable.table[ltable.table[n + 1].idxTI].iddatatype;
            IT::FuncPrototype::Func* func = Lex::findProt(itable.table[ltable.table[n + 1].idxTI].pref, funcs);
            if (func->retType != type)
                throw ERROR_THROW_IN(135, ltable.table[n + 1].sn, -1);
        }
        if(ltable.table[n].lexema == 'p'|| ltable.table[n].lexema == 'w')
        {
            type = itable.table[ltable.table[n + 1].idxTI].iddatatype;
        }
        for (int i = n; ltable.table[i].lexema != ';'; i++)
        {
            if (ltable.table[i].lexema == 'v')
                if (type == IT::STR)
                    throw ERROR_THROW_IN(137, ltable.table[i].sn, -1);
            if (ltable.table[i].idxTI != TI_NULLIDX)
            {
                if (itable.table[ltable.table[i].idxTI].idtype == IT::F)
                {
                    if (itable.table[ltable.table[i].idxTI].iddatatype != type)
                        return 0;
                    while (ltable.table[i].lexema != ')')
                        i++;
                    continue;
                }
                if (itable.table[ltable.table[i].idxTI].iddatatype != type)
                    return 0;
            }
        }
        return 1;
    }
}