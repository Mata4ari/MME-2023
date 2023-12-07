#include "stdafx.h"
#include <string>

namespace Log
{
	LOG::LOG(wchar_t logfile[])
	{
		auto ofile = new std::ofstream;
		ofile->open(logfile, std::ios::out | std::ios::app);
		if (!ofile->is_open())
			throw ERROR_THROW(112);

		this->stream = ofile;
		wcscpy_s(this->logfile, logfile);
	}

	void WriteLine(LOG log, char* c, ...)
	{
		char str[300];
		char** p = &c;
		int k = 0;
		int j = 0;
		while (*(p + k)[0] != 0x00)
		{
			for (int i = 0; i < strlen(*(p + k)); i++)
			{
				str[j] = (*(p + k))[i];
				j++;
			}
			k++;
		}
		str[j] = '\0';
		*log.stream << str;
	}

	void WriteLine(LOG log, wchar_t* c, ...)
	{
		wchar_t str[300];
		char st[300];
		wchar_t** p = &c;
		int k = 0;
		int j = 0;
		while (*(p + k)[0] != 0x00)
		{
			for (int i = 0; i < wcslen(*(p + k)); i++)
			{
				str[j] = (*(p + k))[i];
				j++;
			}
			k++;
		}
		str[j] = '\0';
		wcstombs_s(0, st, wcslen(str) * MB_CUR_MAX + 1,str, wcslen(str));
		*log.stream<<st;
	}

	void WriteLog(LOG log)
	{
		std::time_t raw_time;
		tm time_info;
		char time_buf[80];
		std::time(&raw_time);
		localtime_s(&time_info, &raw_time);
		strftime(time_buf, sizeof(time_buf), "%c", &time_info);
		*log.stream << " ---- Протокол ------ " << time_buf<<" ---- \n";
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char ins[300], logs[300], outs[300];
		wcstombs_s(0, ins, wcslen(parm.in) * MB_CUR_MAX + 1, parm.in, wcslen(parm.in));
		wcstombs_s(0, logs, wcslen(parm.log) * MB_CUR_MAX + 1, parm.log, wcslen(parm.log));
		wcstombs_s(0, outs, wcslen(parm.out) * MB_CUR_MAX + 1, parm.out, wcslen(parm.out));
		*log.stream << " ---- Параметры ------ \n";
		*log.stream << ins << "\n";
		*log.stream << outs << "\n";
		*log.stream << logs << "\n";
	}

	void WriteIn(LOG log, In::INP in)
	{
		*log.stream << " ---- Исходные данные ------ \n";
		*log.stream << "Количество символов: " << in.size << "\n";
		*log.stream << "Количество строк: " << in.lines << "\n";
		*log.stream << "Проигнорировано: " << in.ignore << "\n";
	}

	void WriteError(LOG log,Out::OUTFILE out, Error::Error e)
	{
		if (log.stream!=nullptr)
		{
			*log.stream << "Error " << e.id << ": " << e.message << std::endl;
			if(e.inext.col!=-1)
			{
				*log.stream << "Строка " << e.inext.line << " Позиция " << e.inext.col << std::endl;
			}
		}
		else
		{
			std::cout << "Error " << e.id << ": " << e.message << std::endl;
			if (e.inext.col != -1)
			{
				std::cout << "Строка " << e.inext.line << " Позиция " << e.inext.col << std::endl;
			}
		}
		if (out.stream!=nullptr)
		{
			*out.stream << "Error " << e.id << ": " << e.message << std::endl;
			if (e.inext.col != -1)
			{
				*out.stream << "Строка " << e.inext.line << " Позиция " << e.inext.col << std::endl;
			}
		}
	}

	void Close(LOG log)
	{
		log.stream->close();
	}

}