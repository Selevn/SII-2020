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