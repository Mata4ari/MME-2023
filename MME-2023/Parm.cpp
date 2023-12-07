#include "stdafx.h"


namespace Parm
{
	PARM getparm(int argc, _TCHAR* argv[])
	{
		PARM inputParms;
		wchar_t temp[PARM_MAX_SIZE];
		bool findIn = 0;
		bool findLog = 0;
		bool findOut = 0;
		
		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(argv[i], PARM_IN) != NULL)
			{
				if (wcslen(argv[i]) > PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				findIn = 1;
				wcscpy_s(inputParms.in, &(argv[i])[4]);
				break;
			}
		}
		if(!findIn)
			throw ERROR_THROW(100);

		for (int i = 1; i < argc; i++)
		{
			if (wcsstr(argv[i], PARM_IN) != NULL)
			{

			}
			else if (wcsstr(argv[i], PARM_LOG) != NULL)
			{
				if (wcslen(argv[i]) > PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				findLog = 1;
				wcscpy_s(inputParms.log, &(argv[i])[5]);
				wcscat_s(inputParms.log, PARM_LOG_DEFAULT_EXT);
			}
			else if (wcsstr(argv[i], PARM_OUT) != NULL)
			{
				if (wcslen(argv[i]) > PARM_MAX_SIZE)
					throw ERROR_THROW(104);
				findOut = 1;
				wcscpy_s(inputParms.out, &(argv[i])[5]);
				wcscat_s(inputParms.out, PARM_OUT_DEFAULT_EXT);
			}
			else
			{
				throw ERROR_THROW(101);
			}
		}
		if (!findLog)
		{
			wcscpy_s(inputParms.log,inputParms.in);
			wcscat_s(inputParms.log, PARM_LOG_DEFAULT_EXT);
		}
		if (!findOut)
		{
			wcscpy_s(inputParms.out, inputParms.in);
			wcscat_s(inputParms.out, PARM_OUT_DEFAULT_EXT);
		}

		return inputParms;
	}
}