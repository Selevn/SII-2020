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
		In::IN in = In::getin(parm.in);

#pragma region "Инициализация таблиц"
		LT::LexTable lextable = LT::Create(in.lexemPos);
		IT::IdTable idtable = IT::Create(in.lexemPos);
#pragma endregion

		FST::check_chain(in, out, log, lextable, idtable);
		LEX::LEX tables(lextable, idtable);

		MFST_TRACE_START(log)
			MFST::Mfst mfst(tables, GRB::getGreibach());
		mfst.start(log);


		[&] {
			std::cout << "+-+-+-+-+-+-+-+-+-+ Таблица идентификаторов +-+-+-+-+-+-+-+-+-+\n";
			for (int i = 0; i < idtable.size; i++) {
				std::cout << i << "\t| " << idtable.table[i].scope << idtable.table[i].id << " | " << idtable.table[i].idxfirstLE;
				std::cout << " | " << type(idtable.table[i].idtype) << " | " << datatype(idtable.table[i].iddatatype);
				std::cout << " | ";
				if (idtable.table[i].idtype == IT::IDTYPE::L)
					if (idtable.table[i].iddatatype == IT::IDDATATYPE::INT)
						std::cout << idtable.table[i].value.vint << std::endl;
					else
						std::cout << idtable.table[i].value.vstr.str << std::endl;
				else
					std::cout << std::endl;
			}
			std::cout << "+-+-+-+-+-+-+-+-+-+ Таблица идентификаторов +-+-+-+-+-+-+-+-+-+\n";
		};

		[&] {
			std::cout << "+-+-+-+-+-+-+-+-+-+ Таблица лексем +-+-+-+-+-+-+-+-+-+\n";
			for (int i = 0; i < lextable.size; i++) {
				std::cout << i << '\t' << lextable.table[i].idxTI << '\t' << lextable.table[i].lexema;
				std::cout << '\t' << lextable.table[i].sn << std::endl;
			}
			std::cout << "+-+-+-+-+-+-+-+-+-+ Таблица лексем +-+-+-+-+-+-+-+-+-+\n";
		};

		Log::Close(log);
		Out::Close(out);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}

	
	Log::Close(log);


	
	system("pause");
}