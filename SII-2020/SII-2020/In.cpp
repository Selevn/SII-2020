#include "Error.h"
#include "In.h"
#include <fstream>
#include "FST.h"

#define SEP_LENGTH 8
namespace In
{
	IN getin(wchar_t* infile)
	{

		char separators[SEP_LENGTH] = { ' ',';','(',')','-','+','=',','};

		
		IN out;
		out.lines = 1;
		out.size = 0;
		out.ignor = 0;
		out.oneQuoteOpened = false;
		out.doubleQuoteOpened = false;
		out.tildaQuoteOpened = false;

		bool spaceFlag = false;

		out.lexemPos = 0;


		std::ifstream file(infile);
		if (!file)
		{
			throw ERROR_THROW(110)//файл не открыт
		}
		else
		{
			unsigned int chars[] = IN_CODE_TABLE;
			file >> std::noskipws;
			file.seekg(0, std::ios_base::end);
			int size = file.tellg();
			file.seekg(0, std::ios_base::beg);

			out.text = new unsigned char[sizeof(char) * size];

			unsigned char word[500];
			int wordPosCount = 0;

			unsigned char tmp;
			int counter = 0; //счетчик символов
			int line_counter = 1; //счетчик строки
			while (!file.eof())
			{
				//Почему последний символ читает дважды?
				file >> tmp;
				

				switch (chars[(int)tmp])
				{
				case IN::T://out.T://IN::T //введен
				{
					if (tmp == '\'')
					{
						if (!out.doubleQuoteOpened && !out.tildaQuoteOpened) //кавычки в кавычках
							out.oneQuoteOpened = !out.oneQuoteOpened;
					}
					if (tmp == L'"')
					{
						if (!out.oneQuoteOpened && !out.tildaQuoteOpened)//кавычки в кавычках
							out.doubleQuoteOpened = !out.doubleQuoteOpened;
					}
					if (tmp == L'`')
					{
						if (!out.oneQuoteOpened && !out.doubleQuoteOpened)//кавычки в кавычках
							out.tildaQuoteOpened = !out.tildaQuoteOpened;
					}
					if ((tmp == ' ' || tmp == '\n' || tmp == '\t'))//встретили первый пробел
					{
						if (out.doubleQuoteOpened || out.tildaQuoteOpened || out.oneQuoteOpened)
							word[wordPosCount++] = tmp;
						if (!spaceFlag)
						{
							spaceFlag = true;
							out.text[out.size++] = tmp;
							line_counter++;
						}
						if (wordPosCount != 0 && ((!out.oneQuoteOpened) && (!out.doubleQuoteOpened) && (!out.tildaQuoteOpened)))
						{
			
							word[wordPosCount] = '\0';
							out.lexems[out.lexemPos].line = out.lines;
							out.lexems[out.lexemPos].col = line_counter;
							out.lexems[out.lexemPos].lexem = new unsigned char[sizeof(char) * wordPosCount];
							for (int j = 0; j < wordPosCount; j++)
							{
								out.lexems[out.lexemPos].lexem[j] = word[j];
							}
							out.lexems[out.lexemPos].lexem[wordPosCount] = '\0';
							out.lexems[out.lexemPos].col = line_counter - wordPosCount;

							out.lexemPos++;
							wordPosCount = 0;
						}

						
					}
					
					if (tmp != ' ')
					{
						spaceFlag = false;

						line_counter++;
						if (tmp != '\t' && tmp != '\n')
						{
							out.text[out.size++] = tmp;
							word[wordPosCount++] = tmp; //нашли лексему начинаем писать
						}

					}

					break;
				}
				case IN::I://out.I://IN::T //введен
				{
					out.ignor++;
					//line_counter++;
					break;
				}
				case IN::L:// одиночная лексема
				{
					//нужно сохранить предыдущую и сделать новую
					if (wordPosCount == 0)//если нет прошлой лексемы
					{
						out.text[out.size++] = tmp;
						line_counter++;

						out.lexems[out.lexemPos].col = line_counter;
						out.lexems[out.lexemPos].line = out.lines;
						out.lexems[out.lexemPos].lexem = new unsigned char[2];
						out.lexems[out.lexemPos].lexem[0] = tmp;
						out.lexems[out.lexemPos].lexem[1] = '\0';
						out.lexemPos++;
					}
					else
					{

						out.text[out.size++] = tmp;
						line_counter++;

						word[wordPosCount] = '\0';
						out.lexems[out.lexemPos].line = out.lines;
						out.lexems[out.lexemPos].col = line_counter;
						out.lexems[out.lexemPos].lexem = new unsigned char[sizeof(char) * wordPosCount];
						for (int j = 0; j < wordPosCount; j++)
						{
							out.lexems[out.lexemPos].lexem[j] = word[j];
						}
						out.lexems[out.lexemPos].lexem[wordPosCount] = '\0';
						out.lexems[out.lexemPos].col = line_counter - wordPosCount;

						out.lexemPos++;
						wordPosCount = 0;


						out.lexems[out.lexemPos].col = line_counter;
						out.lexems[out.lexemPos].line = out.lines;
						out.lexems[out.lexemPos].lexem = new unsigned char[2];
						out.lexems[out.lexemPos].lexem[0] = tmp;
						out.lexems[out.lexemPos].lexem[1] = '\0';
						out.lexemPos++;
					}

					break;
				}
				case IN::F://out.F://IN::T //введен
				{
					if ((!out.oneQuoteOpened) && (!out.doubleQuoteOpened) && (!out.tildaQuoteOpened)) //если все кавычки закрыты
					{
					throw ERROR_THROW_IN(111, out.lines, line_counter)
						break;
					}
					else
					{
					
						word[wordPosCount++] = tmp;
						out.text[out.size++] = tmp;
						line_counter++;
						break;
					}
				}
				default:
				{
					out.text[out.size++] = (unsigned char)chars[tmp];
					line_counter++;
					break;
				}
				}
				if (tmp == IN_CODE_ENDL)
				{
					line_counter = 1;
					out.lines++;
				}

			}
			out.text[out.size--] = '\0';
			file.close();

		}

		return out;
	}
}