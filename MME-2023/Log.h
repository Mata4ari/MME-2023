#pragma once
#include "Out.h"

namespace Log
{
	struct LOG
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream* stream;

		LOG() { this->stream = nullptr;}
		LOG(wchar_t logfile[]);
	};

	void WriteLine(LOG log, char* c, ...);
	void WriteLine(LOG log, wchar_t* c, ...);
	void WriteLog(LOG log);
	void WriteParm(LOG log, Parm::PARM parm);
	void WriteIn(LOG log, In::INP in);
	void WriteError(LOG log, Out::OUTFILE out, Error::Error error);
	void Close(LOG log);
}