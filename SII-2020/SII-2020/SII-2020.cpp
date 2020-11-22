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
	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	Log::Close(log);
}