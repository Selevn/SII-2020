#include "CodeGeneration.h"
#include <stack>


//TODO: Offset строк
namespace CG {

	void InvokeExpressions(std::ofstream* stream, LEX::LEX t, int start, int end)
	{
		for (int i = start; i < end; i++) {
			//разобрать строку выражения
			if (t.lextable.table[i].lexema == LEX_EQUAL && t.lextable.table[i].data == '=')
			{
				*stream << '\n' << "; String #" << t.lextable.table[i].sn << " :";

				for (int j = -1; t.lextable.table[i + j].lexema != LEX_SEMICOLON; j++) {
					*stream << t.lextable.table[i + j].lexema;
				}
				*stream << '\n';
				int pos = 0;
				bool isArguments = false;
				IT::Entry* func, *save = nullptr;//
				//полячка записывает в lexema знак, пофиксил УЖЕ!
				IT::Entry* recipent = &t.idtable.table[t.lextable.table[i - 1].idxTI];
				while (true)
				{
					pos++;
					if (t.lextable.table[i + pos].lexema == LEX_SEMICOLON || t.lextable.table[i + pos].lexema == '!')
					{
						if(recipent->iddatatype != IT::CHR)
							*stream << "pop " << recipent->id << '\n';
						else
							*stream << "pop eax\nmov " << recipent->id <<", al" << '\n';
						break;
					}
					else if (t.lextable.table[i + pos].lexema == LEX_LITERAL || t.lextable.table[i + pos].lexema == LEX_ID)
					{
						if (t.idtable.table[t.lextable.table[i + pos].idxTI].idtype != IT::F)
						{
							switch (t.idtable.table[t.lextable.table[i + 1].idxTI].iddatatype)
							{
							case (IT::CHR): {
								*stream << "push DWORD ptr " << t.idtable.table[t.lextable.table[i + pos].idxTI].id << '\n';
								break;
							}
							case (IT::STR): {
								*stream << "push offset " << t.idtable.table[t.lextable.table[i + 1].idxTI].id << '\n';
								break;
							}
							case (IT::INT): {
								*stream << "push " << t.idtable.table[t.lextable.table[i + pos].idxTI].id << '\n';
								break;
							}
							}
							//if (t.idtable.table[t.lextable.table[i + pos].idxTI].iddatatype != IT::CHR)
							//{
							//	*stream << "push " << t.idtable.table[t.lextable.table[i + pos].idxTI].id << '\n';// << ";" << t.lextable.table[i + pos].idxTI;
							//}
							//else {
							//	*stream << "push DWORD ptr " << t.idtable.table[t.lextable.table[i + pos].idxTI].id << '\n';// << ";" << t.lextable.table[i + pos].idxTI;
							//}
							save = &t.idtable.table[t.lextable.table[i + pos].idxTI];
						}
						else
						{
							isArguments = true;
							*stream << "invoke " << t.idtable.table[t.lextable.table[i + pos].idxTI].id;
							pos++;
							while (t.lextable.table[i + pos].lexema != '@'){
								*stream << ", " << t.idtable.table[t.lextable.table[i + pos].idxTI].id;
								pos++;
							}
							*stream << '\n';
							*stream << "push eax ;результат функции";
							*stream << '\n';
						}
					}
					else if (t.lextable.table[i + pos].lexema == LEX_OPERATOR) {
						*stream << "pop ebx" << '\n';
						*stream << "pop eax" << '\n';
						switch (t.lextable.table[i + pos].data)
						{
						case '+': {
							*stream << "add eax, ebx " << '\n';
							break;
						}
						case '-': {
							*stream << "sub eax, ebx" << '\n';
							break;
						}
						case '*': {
							*stream << "imul ebx" << '\n';
							break;
						}
						case '~': {
							*stream << "push edx ; сохраняем данные регистра edx" << '\n';
							*stream << "mov edx, 0" << '\n';
							*stream << "div ebx" << '\n';
							*stream << "pop edx" << '\n';
							break;
						}
						case '%': {
							*stream << "push edx ; сохраняем данные регистра edx" << '\n';
							*stream << "mov edx, 0" << '\n';
							*stream << "div ebx" << '\n';
							*stream << "mov eax, edx" << '\n';
							*stream << "pop edx" << '\n';
							break;
						}

						case '/': {
							*stream << "push ecx ; сохраняем данные регистра ecx"<<'\n';
							*stream << "mov ecx, ebx" << '\n';
							*stream << "SHL eax, cl"<< '\n';
							*stream << "pop ecx" << '\n';
							break;
						}
						case '\\': {
							*stream << "push ecx ; сохраняем данные регистра ecx" << '\n';
							*stream << "mov ecx, ebx" << '\n';
							*stream << "SHR eax, cl" << '\n';
							*stream << "pop ecx" << '\n';
							break;
						}

						}
						*stream << "push eax" << '\n';
					}
				}
			}
			//разобрать ретурн
			else if (t.lextable.table[i].lexema == LEX_RETURN) {
				*stream << "mov eax, ";
				//pos++;
				if (t.idtable.table[t.lextable.table[i + 1].idxTI].iddatatype != IT::CHR)
					*stream << t.idtable.table[t.lextable.table[i + 1].idxTI].id << '\n';
				else
					*stream <<"DWORD ptr "<< t.idtable.table[t.lextable.table[i + 1].idxTI].id << '\n'; 
			}
			else if (t.lextable.table[i].lexema == LEX_PRINTI) {
				*stream << "push ";
				//pos++;
				switch (t.idtable.table[t.lextable.table[i + 1].idxTI].iddatatype)
				{
					case (IT::CHR): {
						*stream << "DWORD ptr " << t.idtable.table[t.lextable.table[i + 1].idxTI].id << '\n';
					
						*stream << "CALL outputchar" << '\n';
						break;
					}
					case (IT::STR): {
						*stream << t.idtable.table[t.lextable.table[i + 1].idxTI].id << '\n';
						*stream << "CALL outputstr" << '\n';
						break;
					}
					case (IT::INT): {
						*stream << t.idtable.table[t.lextable.table[i + 1].idxTI].id << '\n';
						*stream << "CALL outputuint" << '\n';
						break;
					}
				}
			}
			//TODO: разобрать цикл
		}
	}


	void Initialize(IT::Entry wher, IT::Entry from, std::ofstream* stream) {
		*stream << '\n';
		*stream << "push" << from.id;


		*stream << "pop" << wher.id;
	}

	void Head(std::ofstream *stream, LEX::LEX t) {
		
		*stream << ".586\n";
		*stream << "\t.model flat, stdcall\n";
		*stream << "\tincludelib libucrt.lib\n";
		*stream << "\tincludelib kernel32.lib\n";
		*stream << "\tincludelib ../Debug/SII-2020LIB.lib\n";

		*stream << "\tExitProcess PROTO :DWORD\n\n";
		for (int i = 0; i < t.idtable.size; i++)
		{
			if (t.idtable.table[i].idtype == IT::F)
			{	//Если библиотечная
				if (t.idtable.table[i].isExternal == true)
				{
					*stream << "\n\t" << t.idtable.table[i].id << " PROTO";
					int pos = 1;
					bool commaFlag = false;
					while (true)
					{
						if (t.lextable.table[t.idtable.table[i].idxfirstLE + pos].lexema == LEX_ID
							&&
							t.idtable.table[t.lextable.table[t.idtable.table[i].idxfirstLE + pos].idxTI].idtype == IT::P)
						{
							if (commaFlag)
							{
								*stream << ',';
							}
							commaFlag = true;
							switch (t.idtable.table[t.lextable.table[t.idtable.table[i].idxfirstLE + pos].idxTI].iddatatype)
							{
							case IT::INT: {
								*stream << " :DWORD ";
								break;
							}
							case IT::CHR: {
								*stream << " :BYTE";
								break;
							}
							case IT::STR: {
								*stream << " :DWORD";
								break;
							}
							}
						}
						if (t.lextable.table[t.idtable.table[i].idxfirstLE + pos].lexema == LEX_RIGHTHESIS)
							break;
						pos++;
					}
				}
			}
		}
		*stream << "\noutputuint PROTO :DWORD";
		*stream << "\noutputchar PROTO :BYTE";
		*stream << "\noutputstr PROTO :DWORD\n";

		*stream << "\n.stack 4096\n";
	}
	void Constants(std::ofstream *stream, LEX::LEX t) {
		*stream << ".const\n";
		for (int i = 0; i < t.idtable.size; i++)
		{
			if (t.idtable.table[i].idtype == IT::L)
			{
				*stream << "\t" << t.idtable.table[i].id;
				switch (t.idtable.table[i].iddatatype) {
					case IT::INT: {
						*stream << " DWORD " << t.idtable.table[i].value.vint <<" ;INT";
						break;
					}
					case IT::CHR: {
						*stream << " BYTE '" << t.idtable.table[i].value.vchar << "' ;CHR";
						break;
					}
					case IT::STR: {
						*stream << " BYTE " << t.idtable.table[i].value.vstr.str << ", 0 " <<" ;STR";
						break;
					}
				}
				*stream << '\n';
			}
		}
	}
	void Data(std::ofstream *stream, LEX::LEX t) {
		*stream << ".data\n";
		for (int i = 0; i < t.idtable.size; i++) {
			if (t.idtable.table[i].idtype == IT::V)
			{
				*stream << "\t" << t.idtable.table[i].id;
				switch (t.idtable.table[i].iddatatype) {
				case IT::INT: {
					*stream << " DWORD ? ;INT";
					break;
				}
				case IT::CHR: {
					*stream <<  " BYTE ? ;CHR";
					break;
				}
				case IT::STR: {
					*stream << " DWORD ? ;STR";
					break;
				}
				}
				*stream << '\n';
			}
		}
	}

	void WriteFunctions(std::ofstream* stream, LEX::LEX t) 
	{
		for (int i = 0; i < t.idtable.size; i++) 
		{
			if (t.idtable.table[i].idtype == IT::F)
			{	//если не библиотечная
				if (t.idtable.table[i].isExternal == false)
				{
					*stream  << t.idtable.table[i].id << " PROC uses ebx ecx edi esi, ";
					int pos = 1;
					int retsize = 0;
					bool commaFlag = false;
					while (true)
					{
						//запись параметров
						if (t.lextable.table[t.idtable.table[i].idxfirstLE + pos].lexema == LEX_ID
							&&
							t.idtable.table[t.lextable.table[t.idtable.table[i].idxfirstLE + pos].idxTI].idtype == IT::P)
						{
							if (commaFlag)
							{
								*stream << ',';
							}
							commaFlag = true;
							*stream << "\t" << t.idtable.table[t.lextable.table[t.idtable.table[i].idxfirstLE + pos].idxTI].id;
							switch (t.idtable.table[t.lextable.table[t.idtable.table[i].idxfirstLE + pos].idxTI].iddatatype)
							{
							case IT::INT: {
								*stream << ": DWORD ";
								retsize += 4;
								break;
							}
							case IT::CHR: {
								*stream << ": BYTE";
								retsize += 1;
								break;
							}
							case IT::STR: {
								*stream << ": DWORD";
								retsize += 4;
								break;
							}
							}
						}
						if (t.lextable.table[t.idtable.table[i].idxfirstLE + pos].lexema == LEX_RIGHTHESIS)
							break;
						pos++;
					}
					int start = t.idtable.table[i].idxfirstLE + pos, end;
					while (t.lextable.table[t.idtable.table[i].idxfirstLE + pos].lexema != LEX_RETURN)
						pos++;
					pos += 4;
					end = t.idtable.table[i].idxfirstLE + pos;
					InvokeExpressions(stream, t, start, end);

					*stream << "ret ";//<< retsize;
					*stream << "\n" << t.idtable.table[i].id << " ENDP\n\n";
				}
			}
		}
	}



	void Code(std::ofstream *stream, LEX::LEX t) {
		*stream << "\n.code\n";

		WriteFunctions(stream, t);

		*stream << "main PROC\n";
		int i = 0, st;
		while (t.lextable.table[i].lexema != LEX_MAIN)
			i++;
		st = i;
		while (t.lextable.table[i].lexema != LEX_RETURN)
			i++;
		i += 4;
		InvokeExpressions(stream, t, st, i);


		*stream << "\tinvoke\t\tExitProcess, eax\n";
		*stream << "main ENDP\n";
		*stream << "end main";
	}

	
	

	void Generate(LEX::LEX t) {
		std::ofstream out = std::ofstream("../SII-2020ASM/SII-2020ASM.asm");
		Head(&out, t);
		Constants(&out, t);
		Data(&out,t);
		Code(&out,t);

	}
	
}