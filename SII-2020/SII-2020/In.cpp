#include "Error.h"
#include "In.h"
#include <fstream>
#include "FST.h"

namespace In
{
	IN getin(wchar_t infile[])
	{
		IN out;
		out.lines = 1;
		out.size = 0;
		out.ignor = 0;
		std::ifstream file(infile);
		if (!file)
			throw ERROR_THROW(110)//файл не открыт
		else
		{
			unsigned int chars[] = IN_CODE_TABLE;
			file >> std::noskipws;
			file.seekg(0, std::ios_base::end);
			int size = file.tellg();
			file.seekg(0, std::ios_base::beg);
			if(size > IN_MAX_LEN_TEXT)
				throw ERROR_THROW(112)
			unsigned char tmp;
			int line_counter = 0; //счетчик символов строки
			lexem currentLex;
			unsigned char * lexContainer= new unsigned char[MAX_LEXEM_LENGTH];
			int lexContainerLen = 0;
			bool Cflag = false;
			//WriteLine(log, "Начало чтения файла!");
			while (file >> tmp)
			{
				switch (chars[(int)tmp])
				{
				case IN::T://out.T://IN::T //введен
				{
					line_counter++;
					out.size++;
					if (lexContainerLen == 0) {
						currentLex.line = out.lines;
						currentLex.col = line_counter;
					}
					if (lexContainerLen > MAX_LEXEM_LENGTH)
						throw ERROR_THROW_IN(113, out.lines, line_counter);
					lexContainer[lexContainerLen++] = tmp;
					break;
				}
				case IN::C: //кавычка
				{
					line_counter++;
					out.size++;
					char data, commaAgain;
					file >> data;
					line_counter++;
					out.size++;
					if(!data)
						throw ERROR_THROW_IN(114,out.lines,line_counter)
					file >> commaAgain;
					line_counter++;
					out.size++;
					if (!commaAgain || commaAgain != '\'')
						throw ERROR_THROW_IN(114, out.lines, line_counter)
					
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete[]lexContainer;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainerLen = 0;
					}

					if (lexContainerLen == 0) {
						currentLex.line = out.lines;
						currentLex.col = line_counter;
					}
					currentLex.lexem = new unsigned char[lexContainerLen];
					currentLex.lexem[0] = '\'';
					currentLex.lexem[1] = data;
					currentLex.lexem[2] = '\'';
					currentLex.lexem[3] = '\0';
					out.lexems.push_back(currentLex);

					if (lexContainerLen > MAX_LEXEM_LENGTH)
						throw ERROR_THROW_IN(113, out.lines, line_counter);
					break;
				}
				case IN::D: //кавычка
				{
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete[]lexContainer;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainerLen = 0;
					}

					line_counter++;
					out.size++;
					int pos = 1;
					char* data = new char[TI_STR_MAXSIZE];
					data[0] = '\"';
					char t;
					int strlinelen = 2;
					file >> t;
					while (t != '\"') {
						strlinelen++;
						line_counter++;
						out.size++;
						if(pos-2 > TI_STR_MAXSIZE)
							throw ERROR_THROW_IN(115, out.lines, line_counter)
						data[pos] = t;
						pos++;
						file >> t;
					}
					data[pos] = t;
					line_counter++;
					out.size++;
					if (!data)
						throw ERROR_THROW_IN(114, out.lines, line_counter)

					if (lexContainerLen == 0) {
						currentLex.line = out.lines;
						currentLex.col = line_counter;
					}
					currentLex.lexem = new unsigned char[lexContainerLen];
					for (int i = 0; i < strlinelen; i++)
						currentLex.lexem[i] = data[i];
					
					out.lexems.push_back(currentLex);

					if (lexContainerLen > MAX_LEXEM_LENGTH)
						throw ERROR_THROW_IN(113, out.lines, line_counter);
					break;
				}
				case IN::S://space
				{
					out.size++;
					line_counter++;
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete []lexContainer;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
						lexContainerLen = 0;
					}
					break;
				}
				case IN::I://out.I://IN::T //введен
				{
					line_counter++;
					out.ignor++;
					break;
				}
				case IN::L:// одиночная лексема
				{
					out.size++;
					line_counter++;
					if (lexContainerLen != 0) {
						//line_counter++;
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete []lexContainer;
						lexContainerLen = 0;
					}
					lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
					lexContainer[0] = tmp;
					lexContainer[1] = '\0';
					lexContainerLen = 2;
					currentLex.line = out.lines;
					currentLex.col = line_counter;
					currentLex.lexem = new unsigned char[lexContainerLen];
					for (int i = 0; i < lexContainerLen; i++)
						currentLex.lexem[i] = lexContainer[i];
					out.lexems.push_back(currentLex);
					delete []lexContainer;
					lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
					lexContainerLen = 0;
					break;
				}
				case IN::F://out.F://IN::T //введен
				{
					line_counter++;
					throw ERROR_THROW_IN(111, out.lines, line_counter)
						break;
				}
				case IN::O: {
					do {
						line_counter++;
						out.ignor++;
						file >> tmp;
					} while (chars[(int)tmp] != IN::N);
				}
				case IN::N://out.F://IN::T //введен
				{
					out.size++;
					out.lines++;
					line_counter = 0;
					if (lexContainerLen != 0) {
						lexContainer[lexContainerLen++] = '\0';
						currentLex.lexem = new unsigned char[lexContainerLen];
						for (int i = 0; i < lexContainerLen; i++)
							currentLex.lexem[i] = lexContainer[i];
						out.lexems.push_back(currentLex);
						delete []lexContainer;
						lexContainerLen = 0;
						lexContainer = new unsigned char[MAX_LEXEM_LENGTH];
					}
					break;
				}
				default:
				{
					std::cout << "Default input: " << tmp;
					break;
				}
				}
			}
			delete []lexContainer;
			file.close();
			//WriteLine(log, "Конец чтения файла!");
			//for (lexem n : out.lexems) std::cout << n.lexem << "\n";
		}

		return out;
	}
}