#pragma once

namespace Out
{
	struct OUTFILE
	{
		std::ofstream* stream;
		OUTFILE() { this->stream = nullptr; }
		OUTFILE(wchar_t outfile[]);

	};

	void writeOutFile( OUTFILE out,unsigned char* text);
}