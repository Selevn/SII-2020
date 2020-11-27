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
#include "Semantic.h"
#include "NotaciaPolska.h"
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

		//лексический анализатор
		FST::LexAnalyzer(in,out,log, tables.lextable,tables.idtable);
		
		//синтаксический анализ
		MFST_TRACE_START(log)
			MFST::Mfst mfst(tables, GRB::getGreibach());
		mfst.start(log);
		//семантический анализ
		Semantic::doAnalyse(tables);
		//польская запись
		NotaciaPolska::Wykonac(tables);
		//генерация кода
		std::cout << "\n\n\n______LEXEMS_____\n";
		std::cout << "Position   |StringNumber     |lexema     |idxTI\n";
		for (int i = 0; i < tables.lextable.size; i++)
		{
			LT::Entry a = LT::GetEntry(tables.lextable, i);
			char* intStr = new char[4];

			std::cout << std::setw(9) << i << std::setw(9) << a.sn << std::setw(19) << a.lexema << std::setw(19) << a.idxTI << std::endl;
			//std::cout <<  << "        " << a.id << "     " << a.scope << "     " << a.idtype << "     " << a.iddatatype<<'\n';
		}




		std::cout << "\n\n\n______ITENDIFICATORS_____\n";
		std::cout << "Number   |Name    |IdTYPE     |IdDATATYPE     |Value\n";
		for (int i = 0; i < tables.idtable.size; i++)
		{
			std::string type, datatype;
			IT::Entry a = IT::GetEntry(tables.idtable, i);
			char* intStr = new char[4];
			_itoa_s(a.idxfirstLE, intStr, 4, 10);
			switch (a.idtype) {
			case IT::V:
				type = "var";
				break;
			case IT::F:
				type = "func";
				break;
			case IT::L:
				type = "Lit";
				break;
			case IT::P:
				type = "Parm";
				break;
			}
			switch (a.iddatatype) {
			case IT::INT:
				datatype = "INT";
				break;
			case IT::STR:
				datatype = "CHR";
				break;
			}

			std::cout << std::setw(9) << a.idxfirstLE << std::setw(9) << a.id << std::setw(9) << type << std::setw(9) << datatype << std::setw(9) << a.value.vint << " | " << a.value.vchar << " | " << std::endl;
			//std::cout <<  << "        " << a.id << "     " << a.scope << "     " << a.idtype << "     " << a.iddatatype<<'\n';
		}
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	Log::Close(log);
}