#include "stdafx.h"
using namespace std;

/*
 инициализация по умолчанию для выражений
 настроить все исключения
 вызов функции вне выражения
 дописать знаки припинания 
 переписать коды ошибок
 переписать протокол выхода 
 переписать для табуляции
 пропуск строк в лексическом ошибочных при исключении
*/
int _tmain(int argc,_TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	Log::LOG lg;
	Out::OUTFILE out;
	try
	{
		Parm::PARM inputParm = Parm::getparm(argc, argv);
		
		lg = Log::LOG(inputParm.log);
		Log::WriteLog(lg);
		Log::WriteParm(lg, inputParm);
		out = Out::OUTFILE(L"D:\\project\\MME-2023\\MME-2023\\programText.txt.out");
		In::INP in = In::getin(inputParm.in);
		Out::writeOutFile(out, in.text);

		LT::LexTable ltable(LT_MAXSIZE);
		IT::IdTable itable(TI_MAXSIZE);
		IT::FuncPrototype funcs;
		Lex::Reading(L"D:\\project\\MME-2023\\MME-2023\\programText.txt.out",ltable,itable,funcs);
		SA::checkParms(itable, ltable, funcs);

		Log::WriteIn(lg, in);


		IT::PrintIdTable(itable);
		LT::PrintLexTable(ltable);

		MFST_TRACE_START
			MFST::Mfst mfst(ltable, GRB::getGreibach());
		mfst.start();

		mfst.savededucation();

		mfst.printrules();

		SA::checkTypes(itable, ltable, funcs);
		PN::getPolish(ltable, itable);
		SA::Initialize(ltable, itable);

		IT::PrintIdTable(itable);
		LT::PrintLexTable(ltable);

		TR::translation(inputParm.out, ltable, itable,funcs);

		LT::Delete(ltable);
		IT::Delete(itable);
		IT::DeleteFuncs(funcs);


		Log::Close(lg);
		delete[] in.text;
	}
	catch (Error::Error e)
	{
		cout << e.id << " " << e.message << "\n" << e.inext.line << " " << e.inext.col << endl;
		Log::WriteError(lg,out, e);
	}

	return 0;
}