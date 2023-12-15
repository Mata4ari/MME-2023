#include "stdafx.h"

namespace TR
{
	void translation(wchar_t outfile[], LT::LexTable ltable, IT::IdTable itable, IT::FuncPrototype& funcs)
	{

		auto f = new std::ofstream;
		f->open(outfile);
		if (!f->is_open())
			throw ERROR_THROW(150);
		

		*f << ".586" << endl;
		*f << ".model flat, stdcall" << endl;
		*f << "includelib kernel32.lib" << endl << endl;
		*f << "ExitProcess PROTO :DWORD" << endl << endl;
		*f << "SetConsoleTitleA proto :dword\n\
GetStdHandle proto : dword\n\
WriteConsoleA proto : dword, : dword, : dword, : dword, : dword" << endl<<endl;
		*f << ".const" << endl << endl;

		int LiteralCount = 0;
		for (int i = 0; i < itable.size; i++)
		{
			if (itable.table[i].idtype == IT::L)
			{
				if (itable.table[i].iddatatype == IT::INT)
				{
					*f << "L" << itable.table[i].id << " dword " << itable.table[i].value.vint<<endl;
					LiteralCount++;
				}
				if (itable.table[i].iddatatype == IT::STR)
				{
					if(itable.table[i].value.vstr.len==0)
						*f << "L" << itable.table[i].id << " byte " << itable.table[i].value.vstr.len;
					else
						*f << "L" << itable.table[i].id << " byte " << itable.table[i].value.vstr.len;
					*f<< ", " << itable.table[i].value.vstr.str<<", 0" << endl;
					LiteralCount++;
				}
			}
		}
		*f << endl;
		*f << ".data" << endl<<endl;

		for (int i = 0; i < itable.size; i++)
		{
			if (itable.table[i].idtype == IT::V || itable.table[i].idtype == IT::P)
			{
				if (itable.table[i].iddatatype == IT::INT)
				{
					*f << itable.table[i].pref << itable.table[i].id << " dword " << itable.table[i].value.vint << endl;
				}
				if (itable.table[i].iddatatype == IT::STR)
				{
					*f << itable.table[i].pref << itable.table[i].id << " byte ";
					if (itable.table[i].value.vstr.len != 0)
					{
						*f << itable.table[i].value.vstr.len << ", " << itable.table[i].value.vstr.str << ", 0" << endl;
						*f << "\tbyte " << 128 - itable.table[i].value.vstr.len << " dup(0)";
					}
					else
					{
						*f << " 0"<<endl;
						*f << "\tbyte 128 dup(0)";
					}
					*f << endl;
				}
			}
			if (itable.table[i].idtype == IT::DF)
			{
				*f << "ret" << itable.table[i].id << " ";
				if (itable.table[i].iddatatype == IT::INT)
					*f << "dword 0";
				if (itable.table[i].iddatatype == IT::STR)
				{
					*f << "byte 0" << endl;
					*f << "\tbyte 128 dup(0)";
				}
				*f << endl;
			}
		}
		*f << "consol byte \'Console\', 0"<<endl;
		*f << "endl byte 10, 0" << endl;
		*f << "buffer byte 20 dup(0)" << endl;
		*f << endl;
		*f << endl << ".code" << endl;
		*f << "printconsole proc uses eax ebx ecx edi esi,\n\
			pstr:dword, ptitle : dword\n\
			push ptitle\n\
			call SetConsoleTitleA\n\
			push - 11\n\
			call GetStdHandle\n\
			mov esi, pstr\n\
			mov edi, -1\n\
			count:\n\
		inc edi\n\
			cmp byte ptr[esi + edi], 0\n\
			jne count\n\
			push 0\n\
			push 0\n\
			push edi\n\
			push pstr\n\
			push eax\n\
			call WriteConsoleA\n\
			ret\n\
			printconsole endp" << endl<<endl;

		*f << "int_to_char proc uses eax ebx ecx edi esi,\n\
			pstr:dword,\n\
			intfield : dword\n\
			mov edi, pstr\n\
			mov esi, 0\n\
			mov eax, intfield\n\
			cdq\n\
			mov ebx, 10\n\
			idiv ebx\n\
			test eax, 80000000h\n\
			jz plus\n\
			neg eax\n\
			neg edx\n\
			mov cl, '-'\n\
			mov[edi], cl\n\
			inc edi\n\
			plus :\n\
		push dx\n\
			inc esi\n\
			test eax, eax\n\
			jz fin\n\
			cdq\n\
			idiv ebx\n\
			jmp plus\n\
			fin :\n\
		mov ecx, esi\n\
			write :\n\
		pop bx\n\
			add bl, '0'\n\
			mov[edi], bl\n\
			inc edi\n\
			loop write\n\
			ret\n\
			int_to_char endp" << endl << endl;

		codeTranslation(f, ltable, itable,funcs);


		*f << "push - 1" << endl;
		*f << "call ExitProcess" << endl;
		*f << "main endp" << endl << endl;
		*f << "end main" << endl;
	}

	void codeTranslation(ofstream*f,LT::LexTable ltable, IT::IdTable itable,IT::FuncPrototype&funcs)
	{
		char temp[20]="\0";
		bool start = 1;
		int res;
		bool isInt=0, isStr=0,isEqual=0,isReturn=0,isIf=0,isWrite=0,isWriteline=0;
		int ifCount = 0,elseCount=0;
		char pref[15];
		bool blockIf = 0,hasElse=0;
		for (int i = 0; i<ltable.size; i++)
		{
			if (ltable.table[i].lexema == '#')
				continue;
			if(ltable.table[i].idxTI!=LT_TI_NULLIDX)
			{
				if (itable.table[ltable.table[i].idxTI].idtype == IT::DF)
				{
					if (strcmp(itable.table[ltable.table[i].idxTI].id, temp) != 0 && !start)
					{
						*f << temp << " endp" << endl<<endl;
					}
					strcpy_s(temp,itable.table[ltable.table[i].idxTI].id);
					start = 0;
					*f << itable.table[ltable.table[i].idxTI].id << " proc " << endl<<endl;
				}
			}
			if (ltable.table[i].lexema == '=')
			{
				if (itable.table[ltable.table[i - 1].idxTI].iddatatype == IT::INT)
					isInt = 1;
				else
					isStr = 1;
				res = i-1;
				isEqual = 1;
			}
			if (ltable.table[i].lexema == 'p'|| ltable.table[i].lexema == 'w')
			{
				if (itable.table[ltable.table[i + 1].idxTI].iddatatype == IT::INT)
					isInt = 1;
				else
					isStr = 1;
				if (ltable.table[i].lexema == 'w') isWriteline = 1;
				isWrite = 1;
			}
			if (ltable.table[i].lexema == 'r')
			{
				if (itable.table[ltable.table[i + 1].idxTI].iddatatype == IT::INT)
					isInt = 1;
				else
					isStr = 1;
				isReturn = 1;
				strcpy_s(pref, itable.table[ltable.table[i + 1].idxTI].pref);
			}
			if (ltable.table[i].lexema == '?')
			{
				if (itable.table[ltable.table[i + 2].idxTI].iddatatype == IT::INT)
					isInt = 1;
				else
					isStr = 1;
				isIf = 1;
				blockIf = 1;
			}
			if (isIf && ltable.table[i].lexema == ')')
			{
				if(isInt)
				{
					*f << "pop eax" << endl;
				}
				if (isStr)
				{
					*f << "pop edx" << endl;
					*f << "mov eax,[edx]" << endl;
				}
				*f << "cmp eax, 0" << endl<<endl;
				int k = i;
				while (ltable.table[k].lexema != '}')
					k++;
				if (ltable.table[k + 1].lexema == 'e')
					*f << "jz labelf" << elseCount << endl;
				else
					*f << "jz endif" << ifCount << endl;
				if (isInt) isInt = 0;
				if (isStr) isStr = 0;
				isIf = 0;
			}
			if (hasElse && ltable.table[i].lexema == '}')
			{
				*f <<endl<< "endif" << ifCount << ":" << endl<<endl;
				ifCount++;
				hasElse = 0;
			}
			if (blockIf && ltable.table[i].lexema == '}')
			{
				*f << "jmp endif" << ifCount << endl;
				if (ltable.table[i + 1].lexema == 'e')
					hasElse = 1;
				else
				{
					*f <<endl<< "endif" << ifCount << ":" << endl<<endl;
					ifCount++;
				}
				blockIf = 0;
			}
			if (ltable.table[i].lexema == 'e')
			{
				*f<<endl << "labelf" << elseCount << ":" << endl<<endl;
				elseCount++;
			}
			if (ltable.table[i].lexema == ';')
			{
				if(isEqual)
				{
					if(isInt)
					{
						*f << "pop " << itable.table[ltable.table[res].idxTI].pref << itable.table[ltable.table[res].idxTI].id << endl;
					}
					if(isStr)
					{
						*f << "xor ecx,ecx" << endl;
						*f<<"lea edi,"<< itable.table[ltable.table[res].idxTI].pref << itable.table[ltable.table[res].idxTI].id << endl;
						*f << "pop esi" << endl;
						*f << "mov cl,[esi]" << endl;
						*f << "rep movsb" << endl;
					}
					isEqual = 0;
				}
				if (isReturn)
				{
					if(isInt)
					{
						*f << "pop ret" << pref << endl;
					}
					if (isStr)
					{
						*f << "xor ecx,ecx" << endl;
						*f << "lea edi,ret" << pref << endl;
						*f << "pop esi" << endl;
						*f << "mov cl,[esi]" << endl;
						*f << "rep movsb" << endl;
					}
					if(strcmp(pref,"main")!=0)
					{
						*f << "ret" << endl;
					}
					isReturn = 0;
				}
				if (isWrite)
				{
					if (isInt)
					{
						*f << "push offset buffer" << endl;
						*f << "call int_to_char" << endl;
						*f << "push offset consol" << endl;
						*f << "push offset buffer" << endl;
						*f << "call printconsole" << endl;
					}
					if (isStr)
					{
						*f << "pop eax" << endl;
						*f << "push offset consol" << endl;
						*f << "inc eax" << endl;
						*f << "push eax" << endl;
						*f << "call printconsole" << endl;
					}
					if (isWriteline)
					{
						*f << "push offset consol" << endl;
						*f << "push offset endl" << endl;
						*f << "call printconsole" << endl;
					}
					isWrite = 0;
					isWriteline = 0;
				}
				if (isInt) isInt = 0;
				if (isStr) isStr = 0;
			}
			if(isInt)
			{
				if (ltable.table[i].lexema == 'i')
				{
					*f << "push " << itable.table[ltable.table[i].idxTI].pref << itable.table[ltable.table[i].idxTI].id << endl;
				}
				if (ltable.table[i].lexema == 'l')
				{
					*f << "push L" << itable.table[ltable.table[i].idxTI].id << endl;
				}
			}
			if (isStr)
			{
				if (ltable.table[i].lexema == 'i')
				{
					*f << "lea eax," << itable.table[ltable.table[i].idxTI].pref << itable.table[ltable.table[i].idxTI].id << endl;
					*f << "push eax" << endl;
				}
				if (ltable.table[i].lexema == 'l')
				{
					*f<<"lea eax,L"<< itable.table[ltable.table[i].idxTI].id << endl;
					*f << "push eax" << endl;
				}
			}
			if (ltable.table[i].lexema == 'v'&&isInt)
			{
				if (ltable.table[i].operatorValue == '+')
				{
					*f << "pop ebx" << endl;
					*f << "pop eax" << endl;
					*f << "add eax,ebx" << endl;
					*f << "push eax" << endl;
				}
				if (ltable.table[i].operatorValue == '*')
				{
					*f << "pop ebx" << endl;
					*f << "pop eax" << endl;
					*f << "mul ebx" << endl;
					*f << "push eax" << endl;
				}
				if (ltable.table[i].operatorValue == '-')
				{
					*f << "pop ebx" << endl;
					*f << "pop eax" << endl;
					*f << "sub eax,ebx" << endl;
					*f << "push eax" << endl;
				}
				if (ltable.table[i].operatorValue == '/')
				{
					*f << "pop ebx" << endl;
					*f << "mov edx,0" << endl;
					*f << "pop eax" << endl;
					*f << "div ebx" << endl;
					*f << "push eax" << endl;
				}
				if (ltable.table[i].operatorValue == '%')
				{
					*f << "pop ebx" << endl;
					*f << "mov edx,0" << endl;
					*f << "pop eax" << endl;
					*f << "div ebx" << endl;
					*f << "push edx" << endl;
				}
			}
			if (ltable.table[i].lexema == '@')
			{
				if (!itable.table[ltable.table[i].idxTI].inlib)
				{
					int prot = IT::findFirstLT(itable.table[ltable.table[i].idxTI].id, (char*)"\0", itable);
					int k=prot;
					while (ltable.table[k].lexema != ')')
						k++;
					while (ltable.table[k].lexema != '(')
					{
						if(ltable.table[k].idxTI!=LT_TI_NULLIDX)
							if (itable.table[ltable.table[k].idxTI].idtype == IT::P)
							{
								if(isInt)
								{
									*f << "pop " << itable.table[ltable.table[k].idxTI].pref << itable.table[ltable.table[k].idxTI].id << endl;
								}
								if (isStr)
								{
									*f << "xor ecx,ecx" << endl;
									*f << "lea edi," << itable.table[ltable.table[k].idxTI].pref << itable.table[ltable.table[k].idxTI].id << endl;
									*f << "pop esi" << endl;
									*f << "mov cl,[esi]" << endl;
									*f << "rep movsb" << endl;
								}
							}
						k--;
					}
					*f << "call " << itable.table[ltable.table[i].idxTI].id << endl;
					if (isIf || isReturn || isEqual||isWrite)
					{
						if(isInt)
						{
							*f << "push ret" << itable.table[ltable.table[prot].idxTI].id << endl;
						}
						if (isStr)
						{
							*f << "xor ecx,ecx" << endl;
							*f << "lea edi,ret" << itable.table[ltable.table[prot].idxTI].id << endl;
							*f << "pop esi" << endl;
							*f << "mov cl,[esi]" << endl;
							*f << "rep movsb" << endl;
						}
					}
				}
				else
				{
					*f << "call " << itable.table[ltable.table[i].idxTI].id << endl;
					if (isIf || isReturn || isEqual||isWrite)
						*f << "push eax" << endl;
				}
			}

		}
	}
}