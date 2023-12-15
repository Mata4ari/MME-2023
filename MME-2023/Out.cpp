#include "stdafx.h"

namespace Out
{
	OUTFILE::OUTFILE(const wchar_t outfile[])
	{
		auto ofile = new std::ofstream;
		ofile->open(outfile);
		if (!ofile->is_open())
			throw ERROR_THROW(113);

		this->stream = ofile;
	}

	void writeOutFile(OUTFILE out, unsigned char *text)
	{
		*out.stream << text;
		out.stream->close();
	}
}