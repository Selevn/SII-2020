#include "tchar.h"
#include <iostream>
#include <locale>
#include <cwchar>

#include "MFST.h"
#include "Error.h"
#include "Parm.h"
#include "Log.h"
#include "In.h"
#include "FST.h"
#include "IT.h"
#pragma region "Для вывода в консоль"

std::string type(IT::IDTYPE type) {
	switch (type) {
	case IT::IDTYPE::F: return "Function"; break;
	case IT::IDTYPE::V: return "Variable"; break;
	case IT::IDTYPE::P: return "Parameter"; break;
	case IT::IDTYPE::L: return "Literal"; break;
	default: return "ERROR"; break;
	}
}

std::string datatype(IT::IDDATATYPE type) {
	switch (type) {
	case IT::IDDATATYPE::INT: return "INT"; break;
	case IT::IDDATATYPE::STR: return "STRING"; break;
	default: return "ERROR"; break;
	}
}

#pragma endregion

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "rus");
	system("chcp 1251");

	Log::LOG log = Log::INITLOG;
	Out::OUT out = Out::INITOUT;
	try
	{
		Parm::PARM parm = Parm::getparm(argc, argv);
		log = Log::getlog(parm.log);
		out = Out::getout(parm.out);
		Log::WriteParm(log,parm);
		Log::WriteLog(log);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);

		LEX::LEX tables(LT::Create(in.lexems.size()), IT::Create(in.lexems.size()));
		FST::LexAnalyzer(in,out,log, tables.lextable,tables.idtable);
		
		MFST_TRACE_START(log)
			MFST::Mfst mfst(tables, GRB::getGreibach());
		mfst.start(log);
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	Log::Close(log);
}