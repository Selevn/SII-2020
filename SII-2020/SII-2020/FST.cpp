#include "FST.h"
#include "Error.h"
#include <cstdlib>
#include <iomanip>
#include <vector>
#include "LT.h"
#include "IT.h"
#include <stack>
//polish
//получить приотритет для польской нотации
short getPriority(char a)
{
	switch (a)
	{
	case '(':
		return 0;
	case ')':
		return 0;
	case ',':
		return 1;
	case '-':
		return 2;
	case '+':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	case '[':
		return 4;
	case ']':
		return 4;
	default: {
		return 0;
	}
	}
}

std::stack<LT::Entry> EntryStack;

//bool PolishNotation(
//	int lextablePos,
//	LT::LexTable& lextable,
//	IT::IdTable& idtable
//) {
//	char inString[256];
//	LT::Entry resultString[256];
//	struct stack* stk;
//	
//	short inStringLength = 0;
//	short resultStringLength = 0;
//
//	short vCount = 0;
//	short lCount = 0;
//	short counter = 0;
//	for (short i = lextablePos; i < lextable.size; i++)
//	{
//		counter++;
//		switch (lextable.table[i].lexema)
//		{
//		case LEX_LEFTHESIS:
//		{
//			push(stk, lextable.table[i]);
//			break;
//		}
//		case LEX_RIGHTHESIS:
//		{
//			if (!find(stk, LEX_LEFTHESIS))
//				return false;
//			while (!isEmpty(stk) || get(stk).lexema == lextable.table[i].lexema)
//			{
//				if (get(stk).lexema != LEX_LEFTHESIS)
//					resultString[resultStringLength++] = pop(stk);
//				else if (get(stk).lexema == LEX_LEFTHESIS)
//					pop(stk);
//			}
//			break;
//		}
//		case LEX_PLUS:
//		{
//			vCount++;
//			//char tmp = get(stk).lexema[0];
//			
//			short currentPrior = getPriority(lextable.table[i].data);
//			if (getPriority(get(stk).data) >= currentPrior)
//				while (!isEmpty(stk))
//				{
//					if (getPriority(get(stk).data) >= currentPrior)
//						resultString[resultStringLength++] = pop(stk);
//					else 
//						break;
//				}
//			push(stk, lextable.table[i]);
//			
//			break;
//		}
//		case LEX_SEMICOLON:
//		{
//			while (!isEmpty(stk))
//			{
//				if (get(stk).lexema == LEX_LEFTHESIS || get(stk).lexema == LEX_RIGHTHESIS || lCount - vCount != 1)
//					return false;
//				resultString[resultStringLength++] = pop(stk);
//			}
//			std::cout << std::endl;
//			for (int pos = lextablePos; pos < resultStringLength; pos++)
//			{
//				if(resultString[pos].lexema == LEX_PLUS)
//					std::cout << resultString[pos].data;
//				else
//					std::cout << resultString[pos].lexema;
//				lextable.table[pos] = resultString[pos];
//			}
//			std::cout << std::endl;
//			LT::Entry empty;
//			empty.lexema = '\0';
//			empty.sn = 0;
//			empty.idxTI = 0;
//			empty.data = '\0';
//			for (int pos = resultStringLength; pos < counter; pos++)
//			{
//				lextable.table[pos] = empty;
//			}
//
//			return true;
//			break;
//		}
//		case LEX_COMMA:
//		{
//			while (!isEmpty(stk))
//			{
//				resultString[resultStringLength++] = pop(stk);
//			}
//		}
//
//		default:
//		{
//			if (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_LITERAL)
//				lCount++;
//			resultString[resultStringLength++] = lextable.table[i];
//			break;
//		}
//		}
//	}
//}

FST::RELATION::RELATION(char c, short ns)
{
	symbol = c;
	nnode = ns;
}

FST::NODE::NODE() //по умолчанию
{
	n_relation = 0;
	RELATION* relations = NULL;
};
FST::NODE::NODE(short n, RELATION rel, ...) //с параметрами
{
	n_relation = n;
	RELATION* p = &rel;
	relations = new RELATION[n];
	for (short i = 0; i < n; i++)
		relations[i] = p[i];
};
FST::FST::FST(char* s, short ns, NODE n, ...)
{
	string = s;
	nstates = ns;
	nodes = new NODE[ns];
	NODE* p = &n;
	for (int k = 0; k < ns; k++)
		nodes[k] = p[k];
	rstates = new short[nstates];
	rstates[0] = 0;
	position = -1;
};
bool step(FST::FST& fst, short*& rstates, int length) //один шаг автомата
{
	bool rc = false;
	bool contFlag = false;
	std::swap(rstates, fst.rstates); // смена массивов
	for (short i = 0; i < fst.nstates; i++) //цикл по всем состояниям
	{
		if (rstates[i] == fst.position) //если возможная позиция текущая равна текущей позиции
			for (short j = 0; j < fst.nodes[i].n_relation; j++) //до количеста инцендентных ребер
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) //если нашли такой символ
				{
					if (fst.position == length)//если последний символ в строке, то ищем есть ли второй узел(второй узел для выхода)
					{
						contFlag = true;
						continue;
					}
					else
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					}
				};
			};
		if ((rc == false) && contFlag) //если не нашли второй узел то возвращаемся к первому
		{
			for (short j = 0; j < fst.nodes[i].n_relation; j++) //до количеста инцендентных ребер
			{
				if (fst.nodes[i].relations[j].symbol == fst.string[fst.position]) //если нашли такой символ
				{

					fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
					rc = true;
				};
			};
		}
	};
	return rc;
}
struct col
{

public:
	col(void)
	{
		column = 1;
	}
	void reset_col()
	{
		column = 1;
	}
	void set_col(int a)
	{
		column = a;
	}
	int get_col()
	{
		return column;
	}
private:
	int column;
} colum;
bool FST::execute(FST& fst) //выполнить распознование цепочки
{

	fst.rstates[0] = 0;
	fst.position = -1;
	colum.reset_col();
	short* rstates = new short[fst.nstates];//выделяем память по размеру
	memset(rstates, 0xff, sizeof(short) * fst.nstates); //инициализируем пустотой (ff)
	short lstring = strlen(fst.string); //длина цепочки
	bool rc = true;
	for (short i = 0; i < lstring && rc; i++) //по длине цепочки
	{
		fst.position++;			//продвинули позицию
		rc = step(fst, rstates, lstring); //один шаг автомата
		colum.set_col(i);
	}
	delete[] rstates;
	return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
}
void FST::check_chain(In::IN in, Out::OUT out, Log::LOG log, LT::LexTable& lextable, IT::IdTable& idtable) //выполнить распознование цепочки
{
	char* str = new char[255];

#pragma region "FSTS"

	FST l_integer(
		str,
		8, //количество состояний
		NODE(1, RELATION('i', 1)),
		NODE(1, RELATION('n', 2)),
		NODE(1, RELATION('t', 3)),
		NODE(1, RELATION('e', 4)),
		NODE(1, RELATION('g', 5)),
		NODE(1, RELATION('e', 6)),
		NODE(1, RELATION('r', 7)),
		NODE()
	);
	FST l_numberLiteral(
		str,
		2, //количество состояний
		NODE(20,
			RELATION('0', 0),
			RELATION('1', 0),
			RELATION('2', 0),
			RELATION('3', 0),
			RELATION('4', 0),
			RELATION('5', 0),
			RELATION('6', 0),
			RELATION('7', 0),
			RELATION('8', 0),
			RELATION('9', 0),

			RELATION('0', 1),
			RELATION('1', 1),
			RELATION('2', 1),
			RELATION('3', 1),
			RELATION('4', 1),
			RELATION('5', 1),
			RELATION('6', 1),
			RELATION('7', 1),
			RELATION('8', 1),
			RELATION('9', 1)
		),
		NODE()
	);
	FST l_stringLiteral(
		str,
		3, //количество состояний
		NODE(1, RELATION('\'', 1)),
		NODE(256,
			RELATION('\'', 2),
			RELATION((char)0, 1),
			RELATION((char)1, 1),
			RELATION((char)2, 1),
			RELATION((char)3, 1),
			RELATION((char)4, 1),
			RELATION((char)5, 1),
			RELATION((char)6, 1),
			RELATION((char)7, 1),
			RELATION((char)8, 1),
			RELATION((char)9, 1),
			RELATION((char)10, 1),
			RELATION((char)11, 1),
			RELATION((char)12, 1),
			RELATION((char)13, 1),
			RELATION((char)14, 1),
			RELATION((char)15, 1),
			RELATION((char)16, 1),
			RELATION((char)17, 1),
			RELATION((char)18, 1),
			RELATION((char)19, 1),
			RELATION((char)20, 1),
			RELATION((char)21, 1),
			RELATION((char)22, 1),
			RELATION((char)23, 1),
			RELATION((char)24, 1),
			RELATION((char)25, 1),
			RELATION((char)26, 1),
			RELATION((char)27, 1),
			RELATION((char)28, 1),
			RELATION((char)29, 1),
			RELATION((char)30, 1),
			RELATION((char)31, 1),
			RELATION((char)32, 1),
			RELATION((char)33, 1),
			RELATION((char)34, 1),
			RELATION((char)35, 1),
			RELATION((char)36, 1),
			RELATION((char)37, 1),
			RELATION((char)38, 1),
			RELATION((char)40, 1),
			RELATION((char)41, 1),
			RELATION((char)42, 1),
			RELATION((char)43, 1),
			RELATION((char)44, 1),
			RELATION((char)45, 1),
			RELATION((char)46, 1),
			RELATION((char)47, 1),
			RELATION((char)48, 1),
			RELATION((char)49, 1),
			RELATION((char)50, 1),
			RELATION((char)51, 1),
			RELATION((char)52, 1),
			RELATION((char)53, 1),
			RELATION((char)54, 1),
			RELATION((char)55, 1),
			RELATION((char)56, 1),
			RELATION((char)57, 1),
			RELATION((char)58, 1),
			RELATION((char)59, 1),
			RELATION((char)60, 1),
			RELATION((char)61, 1),
			RELATION((char)62, 1),
			RELATION((char)63, 1),
			RELATION((char)64, 1),
			RELATION((char)65, 1),
			RELATION((char)66, 1),
			RELATION((char)67, 1),
			RELATION((char)68, 1),
			RELATION((char)69, 1),
			RELATION((char)70, 1),
			RELATION((char)71, 1),
			RELATION((char)72, 1),
			RELATION((char)73, 1),
			RELATION((char)74, 1),
			RELATION((char)75, 1),
			RELATION((char)76, 1),
			RELATION((char)77, 1),
			RELATION((char)78, 1),
			RELATION((char)79, 1),
			RELATION((char)80, 1),
			RELATION((char)81, 1),
			RELATION((char)82, 1),
			RELATION((char)83, 1),
			RELATION((char)84, 1),
			RELATION((char)85, 1),
			RELATION((char)86, 1),
			RELATION((char)87, 1),
			RELATION((char)88, 1),
			RELATION((char)89, 1),
			RELATION((char)90, 1),
			RELATION((char)91, 1),
			RELATION((char)92, 1),
			RELATION((char)93, 1),
			RELATION((char)94, 1),
			RELATION((char)95, 1),
			RELATION((char)96, 1),
			RELATION((char)97, 1),
			RELATION((char)98, 1),
			RELATION((char)99, 1),
			RELATION((char)100, 1),
			RELATION((char)101, 1),
			RELATION((char)102, 1),
			RELATION((char)103, 1),
			RELATION((char)104, 1),
			RELATION((char)105, 1),
			RELATION((char)106, 1),
			RELATION((char)107, 1),
			RELATION((char)108, 1),
			RELATION((char)109, 1),
			RELATION((char)110, 1),
			RELATION((char)111, 1),
			RELATION((char)112, 1),
			RELATION((char)113, 1),
			RELATION((char)114, 1),
			RELATION((char)115, 1),
			RELATION((char)116, 1),
			RELATION((char)117, 1),
			RELATION((char)118, 1),
			RELATION((char)119, 1),
			RELATION((char)120, 1),
			RELATION((char)121, 1),
			RELATION((char)122, 1),
			RELATION((char)123, 1),
			RELATION((char)124, 1),
			RELATION((char)125, 1),
			RELATION((char)126, 1),
			RELATION((char)127, 1),
			RELATION((char)128, 1),
			RELATION((char)129, 1),
			RELATION((char)130, 1),
			RELATION((char)131, 1),
			RELATION((char)132, 1),
			RELATION((char)133, 1),
			RELATION((char)134, 1),
			RELATION((char)135, 1),
			RELATION((char)136, 1),
			RELATION((char)137, 1),
			RELATION((char)138, 1),
			RELATION((char)139, 1),
			RELATION((char)140, 1),
			RELATION((char)141, 1),
			RELATION((char)142, 1),
			RELATION((char)143, 1),
			RELATION((char)144, 1),
			RELATION((char)145, 1),
			RELATION((char)146, 1),
			RELATION((char)147, 1),
			RELATION((char)148, 1),
			RELATION((char)149, 1),
			RELATION((char)150, 1),
			RELATION((char)151, 1),
			RELATION((char)152, 1),
			RELATION((char)153, 1),
			RELATION((char)154, 1),
			RELATION((char)155, 1),
			RELATION((char)156, 1),
			RELATION((char)157, 1),
			RELATION((char)158, 1),
			RELATION((char)159, 1),
			RELATION((char)160, 1),
			RELATION((char)161, 1),
			RELATION((char)162, 1),
			RELATION((char)163, 1),
			RELATION((char)164, 1),
			RELATION((char)165, 1),
			RELATION((char)166, 1),
			RELATION((char)167, 1),
			RELATION((char)168, 1),
			RELATION((char)169, 1),
			RELATION((char)170, 1),
			RELATION((char)171, 1),
			RELATION((char)172, 1),
			RELATION((char)173, 1),
			RELATION((char)174, 1),
			RELATION((char)175, 1),
			RELATION((char)176, 1),
			RELATION((char)177, 1),
			RELATION((char)178, 1),
			RELATION((char)179, 1),
			RELATION((char)180, 1),
			RELATION((char)181, 1),
			RELATION((char)182, 1),
			RELATION((char)183, 1),
			RELATION((char)184, 1),
			RELATION((char)185, 1),
			RELATION((char)186, 1),
			RELATION((char)187, 1),
			RELATION((char)188, 1),
			RELATION((char)189, 1),
			RELATION((char)190, 1),
			RELATION((char)191, 1),
			RELATION((char)192, 1),
			RELATION((char)193, 1),
			RELATION((char)194, 1),
			RELATION((char)195, 1),
			RELATION((char)196, 1),
			RELATION((char)197, 1),
			RELATION((char)198, 1),
			RELATION((char)199, 1),
			RELATION((char)200, 1),
			RELATION((char)201, 1),
			RELATION((char)202, 1),
			RELATION((char)203, 1),
			RELATION((char)204, 1),
			RELATION((char)205, 1),
			RELATION((char)206, 1),
			RELATION((char)207, 1),
			RELATION((char)208, 1),
			RELATION((char)209, 1),
			RELATION((char)210, 1),
			RELATION((char)211, 1),
			RELATION((char)212, 1),
			RELATION((char)213, 1),
			RELATION((char)214, 1),
			RELATION((char)215, 1),
			RELATION((char)216, 1),
			RELATION((char)217, 1),
			RELATION((char)218, 1),
			RELATION((char)219, 1),
			RELATION((char)220, 1),
			RELATION((char)221, 1),
			RELATION((char)222, 1),
			RELATION((char)223, 1),
			RELATION((char)224, 1),
			RELATION((char)225, 1),
			RELATION((char)226, 1),
			RELATION((char)227, 1),
			RELATION((char)228, 1),
			RELATION((char)229, 1),
			RELATION((char)230, 1),
			RELATION((char)231, 1),
			RELATION((char)232, 1),
			RELATION((char)233, 1),
			RELATION((char)234, 1),
			RELATION((char)235, 1),
			RELATION((char)236, 1),
			RELATION((char)237, 1),
			RELATION((char)238, 1),
			RELATION((char)239, 1),
			RELATION((char)240, 1),
			RELATION((char)241, 1),
			RELATION((char)242, 1),
			RELATION((char)243, 1),
			RELATION((char)244, 1),
			RELATION((char)245, 1),
			RELATION((char)246, 1),
			RELATION((char)247, 1),
			RELATION((char)248, 1),
			RELATION((char)249, 1),
			RELATION((char)250, 1),
			RELATION((char)251, 1),
			RELATION((char)252, 1),
			RELATION((char)253, 1),
			RELATION((char)254, 1),
			RELATION((char)255, 1)
		),
		NODE()
	);


	FST l_itendificator(
		str,
		3, //количество состояний
		NODE(106,
			RELATION('a', 1),
			RELATION('b', 1),
			RELATION('c', 1),
			RELATION('d', 1),
			RELATION('e', 1),
			RELATION('f', 1),
			RELATION('g', 1),
			RELATION('h', 1),
			RELATION('i', 1),
			RELATION('j', 1),
			RELATION('k', 1),
			RELATION('l', 1),
			RELATION('m', 1),
			RELATION('n', 1),
			RELATION('o', 1),
			RELATION('p', 1),
			RELATION('q', 1),
			RELATION('r', 1),
			RELATION('s', 1),
			RELATION('t', 1),
			RELATION('u', 1),
			RELATION('v', 1),
			RELATION('w', 1),
			RELATION('x', 1),
			RELATION('y', 1),
			RELATION('z', 1),
			RELATION('A', 1),
			RELATION('B', 1),
			RELATION('C', 1),
			RELATION('D', 1),
			RELATION('E', 1),
			RELATION('F', 1),
			RELATION('G', 1),
			RELATION('H', 1),
			RELATION('I', 1),
			RELATION('J', 1),
			RELATION('K', 1),
			RELATION('L', 1),
			RELATION('M', 1),
			RELATION('N', 1),
			RELATION('O', 1),
			RELATION('P', 1),
			RELATION('Q', 1),
			RELATION('R', 1),
			RELATION('S', 1),
			RELATION('T', 1),
			RELATION('U', 1),
			RELATION('V', 1),
			RELATION('W', 1),
			RELATION('X', 1),
			RELATION('Y', 1),
			RELATION('Z', 1),
			RELATION('_', 1),

			RELATION('a', 2),
			RELATION('b', 2),
			RELATION('c', 2),
			RELATION('d', 2),
			RELATION('e', 2),
			RELATION('f', 2),
			RELATION('g', 2),
			RELATION('h', 2),
			RELATION('i', 2),
			RELATION('j', 2),
			RELATION('k', 2),
			RELATION('l', 2),
			RELATION('m', 2),
			RELATION('n', 2),
			RELATION('o', 2),
			RELATION('p', 2),
			RELATION('q', 2),
			RELATION('r', 2),
			RELATION('s', 2),
			RELATION('t', 2),
			RELATION('u', 2),
			RELATION('v', 2),
			RELATION('w', 2),
			RELATION('x', 2),
			RELATION('y', 2),
			RELATION('z', 2),
			RELATION('A', 2),
			RELATION('B', 2),
			RELATION('C', 2),
			RELATION('D', 2),
			RELATION('E', 2),
			RELATION('F', 2),
			RELATION('G', 2),
			RELATION('H', 2),
			RELATION('I', 2),
			RELATION('J', 2),
			RELATION('K', 2),
			RELATION('L', 2),
			RELATION('M', 2),
			RELATION('N', 2),
			RELATION('O', 2),
			RELATION('P', 2),
			RELATION('Q', 2),
			RELATION('R', 2),
			RELATION('S', 2),
			RELATION('T', 2),
			RELATION('U', 2),
			RELATION('V', 2),
			RELATION('W', 2),
			RELATION('X', 2),
			RELATION('Y', 2),
			RELATION('Z', 2),
			RELATION('_', 2)
		),
		NODE(126,
			RELATION('a', 1),
			RELATION('b', 1),
			RELATION('c', 1),
			RELATION('d', 1),
			RELATION('e', 1),
			RELATION('f', 1),
			RELATION('g', 1),
			RELATION('h', 1),
			RELATION('i', 1),
			RELATION('j', 1),
			RELATION('k', 1),
			RELATION('l', 1),
			RELATION('m', 1),
			RELATION('n', 1),
			RELATION('o', 1),
			RELATION('p', 1),
			RELATION('q', 1),
			RELATION('r', 1),
			RELATION('s', 1),
			RELATION('t', 1),
			RELATION('u', 1),
			RELATION('v', 1),
			RELATION('w', 1),
			RELATION('x', 1),
			RELATION('y', 1),
			RELATION('z', 1),
			RELATION('A', 1),
			RELATION('B', 1),
			RELATION('C', 1),
			RELATION('D', 1),
			RELATION('E', 1),
			RELATION('F', 1),
			RELATION('G', 1),
			RELATION('H', 1),
			RELATION('I', 1),
			RELATION('J', 1),
			RELATION('K', 1),
			RELATION('L', 1),
			RELATION('M', 1),
			RELATION('N', 1),
			RELATION('O', 1),
			RELATION('P', 1),
			RELATION('Q', 1),
			RELATION('R', 1),
			RELATION('S', 1),
			RELATION('T', 1),
			RELATION('U', 1),
			RELATION('V', 1),
			RELATION('W', 1),
			RELATION('X', 1),
			RELATION('Y', 1),
			RELATION('Z', 1),
			RELATION('0', 1),
			RELATION('1', 1),
			RELATION('2', 1),
			RELATION('3', 1),
			RELATION('4', 1),
			RELATION('5', 1),
			RELATION('6', 1),
			RELATION('7', 1),
			RELATION('8', 1),
			RELATION('9', 1),


			RELATION('a', 2),
			RELATION('b', 2),
			RELATION('c', 2),
			RELATION('d', 2),
			RELATION('e', 2),
			RELATION('f', 2),
			RELATION('g', 2),
			RELATION('h', 2),
			RELATION('i', 2),
			RELATION('j', 2),
			RELATION('k', 2),
			RELATION('l', 2),
			RELATION('m', 2),
			RELATION('n', 2),
			RELATION('o', 2),
			RELATION('p', 2),
			RELATION('q', 2),
			RELATION('r', 2),
			RELATION('s', 2),
			RELATION('t', 2),
			RELATION('u', 2),
			RELATION('v', 2),
			RELATION('w', 2),
			RELATION('x', 2),
			RELATION('y', 2),
			RELATION('z', 2),
			RELATION('A', 2),
			RELATION('B', 2),
			RELATION('C', 2),
			RELATION('D', 2),
			RELATION('E', 2),
			RELATION('F', 2),
			RELATION('G', 2),
			RELATION('H', 2),
			RELATION('I', 2),
			RELATION('J', 2),
			RELATION('K', 2),
			RELATION('L', 2),
			RELATION('M', 2),
			RELATION('N', 2),
			RELATION('O', 2),
			RELATION('P', 2),
			RELATION('Q', 2),
			RELATION('R', 2),
			RELATION('S', 2),
			RELATION('T', 2),
			RELATION('U', 2),
			RELATION('V', 2),
			RELATION('W', 2),
			RELATION('X', 2),
			RELATION('Y', 2),
			RELATION('Z', 2),
			RELATION('_', 2),
			RELATION('0', 2),
			RELATION('1', 2),
			RELATION('2', 2),
			RELATION('3', 2),
			RELATION('4', 2),
			RELATION('5', 2),
			RELATION('6', 2),
			RELATION('7', 2),
			RELATION('8', 2),
			RELATION('9', 2)
		),
		NODE()
	);

	FST l_string(
		str,
		7, //количество состояний
		NODE(1, RELATION('s', 1)),
		NODE(1, RELATION('t', 2)),
		NODE(1, RELATION('r', 3)),
		NODE(1, RELATION('i', 4)),
		NODE(1, RELATION('n', 5)),
		NODE(1, RELATION('g', 6)),
		NODE()
	);

	FST l_function(
		str,
		9, //количество состояний
		NODE(1, RELATION('f', 1)),
		NODE(1, RELATION('u', 2)),
		NODE(1, RELATION('n', 3)),
		NODE(1, RELATION('c', 4)),
		NODE(1, RELATION('t', 5)),
		NODE(1, RELATION('i', 6)),
		NODE(1, RELATION('o', 7)),
		NODE(1, RELATION('n', 8)),
		NODE()
	);
	FST l_declare(
		str,
		8, //количество состояний
		NODE(1, RELATION('d', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('c', 3)),
		NODE(1, RELATION('l', 4)),
		NODE(1, RELATION('a', 5)),
		NODE(1, RELATION('r', 6)),
		NODE(1, RELATION('e', 7)),
		NODE()
	);
	FST l_return(
		str,
		7, //количество состояний
		NODE(1, RELATION('r', 1)),
		NODE(1, RELATION('e', 2)),
		NODE(1, RELATION('t', 3)),
		NODE(1, RELATION('u', 4)),
		NODE(1, RELATION('r', 5)),
		NODE(1, RELATION('n', 6)),
		NODE()
	);
	FST l_print(
		str,
		6, //количество состояний
		NODE(1, RELATION('p', 1)),
		NODE(1, RELATION('r', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE(1, RELATION('t', 5)),
		NODE()
	);
	FST l_main(
		str,
		5, //количество состояний
		NODE(1, RELATION('m', 1)),
		NODE(1, RELATION('a', 2)),
		NODE(1, RELATION('i', 3)),
		NODE(1, RELATION('n', 4)),
		NODE()
	);
	FST l_semicolon(
		str,
		2, //количество состояний
		NODE(1, RELATION(';', 1)),
		NODE()
	);
	FST l_comma(
		str,
		2, //количество состояний
		NODE(1, RELATION(',', 1)),
		NODE()
	);
	FST l_braceleft(
		str,
		2, //количество состояний
		NODE(1, RELATION('{', 1)),
		NODE()
	);
	FST l_braceright(
		str,
		2, //количество состояний
		NODE(1, RELATION('}', 1)),
		NODE()
	);
	FST l_lefthesis(
		str,
		2, //количество состояний
		NODE(1, RELATION('(', 1)),
		NODE()
	);
	FST l_righthesis(
		str,
		2, //количество состояний
		NODE(1, RELATION(')', 1)),
		NODE()
	);

	FST l_verb(
		str,
		2, //количество состояний
		NODE(5, RELATION('+', 1), RELATION('-', 1), RELATION('*', 1), RELATION('/', 1), RELATION('=', 1)),
		NODE()
	);

#pragma endregion

#pragma region "Структура checker и её массив автоматов"
	struct Checker {
		FST* chain;
		IT::IDDATATYPE iddatatype;
		int position;
		char lexName;
		Checker(FST* f, char c, IT::IDDATATYPE t, int pos) {
			chain = f;
			lexName = c;
			iddatatype = t;
			position = pos;
		}
	};

	Checker checkArr[] = {
		Checker(&l_integer,LEX_INTEGER,IT::INT,0xffffffff),
		Checker(&l_string,LEX_STRING,IT::STR,0xffffffff),
		Checker(&l_function,LEX_FUNCTION,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_declare,LEX_DECLARE,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_return,LEX_RETURN,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_main,LEX_MAIN,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_print,LEX_PRINT,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_braceleft,LEX_LEFTBRACE,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_braceright,LEX_RIGHTBRACE,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_lefthesis,LEX_LEFTHESIS,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_righthesis,LEX_RIGHTHESIS,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_comma,LEX_COMMA,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_semicolon,LEX_SEMICOLON,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_verb,LEX_PLUS,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_itendificator,LEX_ID,(IT::IDDATATYPE)FALSYNUMBER,0xffffffff),
		Checker(&l_numberLiteral,LEX_LITERAL,IT::INT,0xffffffff),
		Checker(&l_stringLiteral,LEX_LITERAL,IT::STR,0xffffffff),
		//len = 17
	};
	const int checkArrLen = 17;


#pragma endregion

#pragma region "Флаги"
	std::string scopeName;
	std::vector <std::string> scopeStack;
	scopeStack.push_back("\0");
	int scopeCount = 0;
	int scopeNumber = 0; // aka currentScope
	int openedBrace = 0;
	bool isDeclare = false;
	bool isRequireBodyFunc = false;
	bool isMain = false;
	bool isFunction = false;
	bool isFunctionName = false;
	bool isFunctionParam = false;
	bool isParametr = false;
	bool isLiteral = false;
	IT::IDDATATYPE dataType = (IT::IDDATATYPE)FALSYNUMBER;
	IT::IDTYPE type = (IT::IDTYPE)FALSYNUMBER;
#pragma endregion

#pragma region "перебор"
	for (int i = 0; i < in.lexems.size(); i++)
	{
		In::lexem lex = in.lexems.front();
		in.lexems.pop_front();

		int len = strlen((const char*)(lex.lexem)); //длина строки ktrctvs
#pragma region "запись лексемы в str"
		for (int k = 0; k < len; k++)
		{
			str[k] = lex.lexem[k];
		}
		str[len] = '\0';
#pragma endregion

		bool executedFlag = false;	// флаг окончания перебора цепочек

		for (int j = 0; j < checkArrLen; j++)
		{
			if (execute(*checkArr[j].chain))
			{
				executedFlag = true;


#pragma region "Установка флага"


				LT::Entry tmp(checkArr[j].lexName, lex.line, checkArr[j].position);
				switch (checkArr[j].lexName)
				{
				case LEX_INTEGER:
					if (checkArr[j].iddatatype == IT::INT)
					{
						dataType = IT::INT;
					}
					else if (checkArr[j].iddatatype == IT::STR)
					{
						dataType = IT::STR;
					}
					else
					{
						//дропай ошибку
						dataType = (IT::IDDATATYPE)FALSYNUMBER;
					}
					break;

				case LEX_FUNCTION:
					type = IT::F;
					break;

				case LEX_LEFTHESIS:
					if (lextable.size!=0
						&&
						lextable.table[lextable.size - 1].idxTI != LT_TI_NULLIDX //если предыдущий - имя функции
						&&
						idtable.table[lextable.table[lextable.size - 1].idxTI].idtype == IT::F)
					{
						isFunctionParam = true; //проверили что это все параметры функции
						scopeStack.push_back(idtable.table[lextable.table[lextable.size - 1].idxTI].id);
						scopeName = idtable.table[lextable.table[lextable.size - 1].idxTI].id;
						type = IT::P;
					}
					break;
				case LEX_RIGHTHESIS:
					if (isFunctionParam)
					{
						scopeStack.pop_back();
						isFunctionParam = false;
						isRequireBodyFunc = true;//закончили смотреть параметры, сейчас ожидаем тело функции
						type = (IT::IDTYPE)FALSYNUMBER;
					}
					break;

				case LEX_LEFTBRACE:
					if (lextable.table[lextable.size - 1].lexema == LEX_RIGHTHESIS && isRequireBodyFunc)//точная проверка на функцию
					{
						scopeStack.push_back(scopeName.c_str());
					}
					else if (lextable.table[lextable.size - 1].lexema == LEX_MAIN){
						scopeStack.push_back("main\0");
					}
					else
					{
						isRequireBodyFunc = false;
					}
					break;
				case LEX_RIGHTBRACE:
					if (isRequireBodyFunc)
					{
						scopeStack.pop_back();
						isRequireBodyFunc = false;
					}
					break;

				case LEX_DECLARE:
					isDeclare = true;
					type = IT::V;
					break;

				case LEX_LITERAL:
					tmp.idxTI = idtable.size;
					if (checkArr[j].iddatatype == IT::INT)
					{
						int out = atoi(str);
						IT::Entry ttmp(lextable.size - 1, (char*)"\0", scopeStack.back().c_str(), checkArr[j].iddatatype, IT::L, out);
						IT::Add(idtable, ttmp);
					}
					if (checkArr[j].iddatatype == IT::STR)
					{
						IT::Entry ttmp(lextable.size - 1, (char*)"\0", scopeStack.back().c_str(), checkArr[j].iddatatype, IT::L, str);
						IT::Add(idtable, ttmp);
					}
					break;
				}
#pragma endregion
#pragma region "Если итендификатор"
				if (tmp.lexema == LEX_ID)
				{
					if (IT::IsId(idtable, str, (char*)scopeStack.back().c_str()) == TI_NULLIDX)
					{
						if (dataType != (IT::IDDATATYPE)FALSYNUMBER && type != (IT::IDTYPE)FALSYNUMBER)
						{
							isDeclare = false;
							IT::Entry ttmp(lextable.size, str, scopeStack.back().c_str(), dataType, type);
							IT::Add(idtable, ttmp);
							tmp.idxTI = idtable.size - 1;
							dataType = (IT::IDDATATYPE)FALSYNUMBER;
							if (!isFunctionParam)
								type = (IT::IDTYPE)FALSYNUMBER;
							bool onceFlag = false;
						}
						else
						{
							std::cout << "";//
						}
					}
					else {
						tmp.idxTI = IT::IsId(idtable, str, (char*)scopeStack.back().c_str());
					}
				}
#pragma endregion

#pragma region "Если знаковая лексема"
				if (tmp.lexema == LEX_MINUS || tmp.lexema == LEX_LEFTBRACE || tmp.lexema == LEX_RIGHTBRACE || tmp.lexema == LEX_LEFTHESIS ||tmp.lexema == LEX_RIGHTHESIS)
				{
					tmp.data = str[0];
				}
#pragma endregion

				LT::Add(lextable, tmp);
				break;
			}
		}
		if (!executedFlag) {
			throw ERROR_THROW_IN(120, lex.line, lex.col);
		}
	}
#pragma endregion


	/*if (PolishNotation(0, lextable, idtable))
		std::cout << "Польская запись успешно составлена!" << std::endl;
	else
		std::cout << "Польская запись не составлена!" << std::endl;*/
	/*
on itendificator->
if (! in Itendificators -> error) else -> create Entry
->
if -1 == n - integer
if -1 == s - string
Entry in buf

next if literal ->
on literal ->
if -1 == IT -> add
if -1 == v -> pass
else -> error;
*/
	int prevline = 1;
	Out::WriteLine(out, " ", "");
	for (int i = 0; i < lextable.size; i++)
	{
		char* tmpChar = new char[2];
		tmpChar[0] = lextable.table[i].lexema;
		tmpChar[1] = '\0';
		if (lextable.table[i].sn == prevline)
		{
			Out::WriteLine(out, tmpChar, "");
		}
		else
		{
			prevline = lextable.table[i].sn;
			char* intStr = new char[4];
			_itoa_s(lextable.table[i].sn, intStr, 4, 10);
			Out::WriteLine(out, "\n", "");
			Out::WriteLine(out, intStr, "");
			Out::WriteLine(out, " ", "");
			Out::WriteLine(out, tmpChar, "");
		}
	}


	/*Out::WriteLine(out, "\n", "");
	Out::WriteLine(out, "Itendificators:\n", "");
	prevline = 1;
	for (int i = 0; i < idtable.size; i++)
	{
		IT::Entry a = IT::GetEntry(idtable, i);
		char* intStr = new char[4];
		_itoa_s(a.idxfirstLE, intStr, 4, 10);
		Out::WriteLine(out, intStr, " ", a.id, "\n", "");
	}*/


#pragma region "вывод в консоль итендификаторов"
	std::cout << "\n\n\n______ITENDIFICATORS_____\n";
	std::cout << "Number   |Name     |Scope     |IdTYPE     |IdDATATYPE     |Value\n";
	for (int i = 0; i < idtable.size; i++)
	{
		IT::Entry a = IT::GetEntry(idtable, i);
		char* intStr = new char[4];
		_itoa_s(a.idxfirstLE, intStr, 4, 10);
		std::cout << std::setw(9) << a.idxfirstLE << std::setw(9) << a.id << std::setw(9) << a.scope << std::setw(9) << a.idtype << std::setw(9) << a.iddatatype<< std::setw(9) << a.value.vint<<" | "<<a.value.vstr.str<<" | " << std::endl;
		//std::cout <<  << "        " << a.id << "     " << a.scope << "     " << a.idtype << "     " << a.iddatatype<<'\n';
	}
#pragma endregion

#pragma region "вывод в консоль лексем"
	std::cout << "\n\n\n______LEXEMS_____\n";
	std::cout << "Position   |StringNumber     |lexema     |idxTI\n";
	for (int i = 0; i < lextable.size; i++)
	{
		LT::Entry a = LT::GetEntry(lextable, i);
		char* intStr = new char[4];

		std::cout << std::setw(9) << i << std::setw(9) << a.sn << std::setw(19) << a.lexema << std::setw(19) << a.idxTI << std::endl;
		//std::cout <<  << "        " << a.id << "     " << a.scope << "     " << a.idtype << "     " << a.iddatatype<<'\n';
	}
#pragma endregion


}