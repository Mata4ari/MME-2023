#include "stdafx.h"
using namespace std;


int _tmain(int argc,_TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");

	Log::LOG lg;
	Out::OUTFILE out;
	try
	{
		Parm::PARM inputParm = Parm::getparm(argc, argv);
		
		lg = Log::LOG(inputParm.log);
		Log::WriteLine(lg, (char*)"Тест:", "без ошибок \n", "");
		Log::WriteLine(lg, (wchar_t*)L"Тест:", L"без ошибок \n", L"");
		Log::WriteLog(lg);
		Log::WriteParm(lg, inputParm);
		out = Out::OUTFILE(inputParm.out);
		In::INP in = In::getin(inputParm.in);
		Out::writeOutFile(out, in.text);

		LT::LexTable ltable(LT_MAXSIZE);
		IT::IdTable itable(TI_MAXSIZE);
		Lex::Reading(inputParm.out,ltable,itable);

		Log::WriteIn(lg, in);

		IT::PrintIdTable(itable);
		LT::PrintLexTable(ltable);

		/*MFST_TRACE_START
			MFST::Mfst mfst(ltable, GRB::getGreibach());
		mfst.start();*/

		//mfst.savededucation();

		//mfst.printrules();
		PN::getPolish(ltable, itable);
		LT::Initialize(ltable, itable);

		IT::PrintIdTable(itable);
		LT::PrintLexTable(ltable);

		LT::Delete(ltable);
		IT::Delete(itable);


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