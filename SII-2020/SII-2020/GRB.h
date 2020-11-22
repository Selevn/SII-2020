#pragma once
#include "Error.h"
#include <iomanip>
typedef short GRBALPHABET; //символы алфавита грамматики терминалы>0. нетерминалы<0

#define MFST_TRACE_START(LOG) *log.stream << std::setw( 4)<<std::left<<"Шаг"<<":" \
	<< std::setw(20) << std::left << "Правило"  \
	<< std::setw(30) << std::left << "Входная лента" \
	<< std::setw(20) << std::left << "Стек" \
	<< std::endl;

#define NS(n)GRB::Rule::Chain::N(n)
#define TS(n)GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)

#define MFST_TRACE1(LOG) *log.stream <<std::setw( 4)<<std::left<<++FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << rule.getCRule(rbuf, nrulechain)  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE2(LOG)    *log.stream <<std::setw( 4)<<std::left<<FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE3(LOG)     *log.stream<<std::setw( 4)<<std::left<<++FST_TRACE_n<<":" \
	<< std::setw(20) << std::left << " "  \
	<< std::setw(30) << std::left << getCLenta(lbuf, lenta_position) \
	<< std::setw(20) << std::left << getCSt(sbuf) \
	<< std::endl;

#define MFST_TRACE4(LOG, c) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;
#define MFST_TRACE5(LOG, c) *log.stream<<std::setw(4)<<std::left<<  FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<std::endl;

#define MFST_TRACE6(LOG,c,k) *log.stream<<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(20)<<std::left<<c<<k<<std::endl;

#define MFST_TRACE7(LOG)  *log.stream<<std::setw(4)<<std::left<<state.lenta_position<<": "\
	<< std::setw(20) << std::left << rule.getCRule(rbuf, state.nrulechain) \
	<< std::endl;

namespace GRB
{
	struct Rule
	{
		GRBALPHABET  nn;
		int iderror;
		short size;
		struct Chain
		{
			short size;
			GRBALPHABET* nt;
			Chain() { size = 0; nt = 0; };
			Chain(short psize, GRBALPHABET s, ...);
			char* getCChain(char* b);
			static GRBALPHABET T(char t) { return GRBALPHABET(t); }
			static GRBALPHABET N(char n) { return -GRBALPHABET(n); };
			static bool isT(GRBALPHABET s) { return s > 0; }
			static bool isN(GRBALPHABET s) { return !isT(s); }
			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };
		}*chains;

		Rule();
		Rule(GRBALPHABET pnn, int iderror, short psize, Chain c, ...);
		char* getCRule(char* b, short nchain);
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j);
	};
	struct Greibach
	{
		short size;
		GRBALPHABET startN;
		GRBALPHABET stbottomT;
		Rule* rules;
		Greibach() { size = 0; startN = 0; stbottomT = 0; rules = 0; };
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbootomT, short psize, Rule r, ...);
		short getRule(GRBALPHABET pnn, Rule& prule);
		Rule getRule(short n);
	};
	Greibach getGreibach();
};
//
//
//namespace GRB
//{
//
//
//	struct Rule //правило грамматики Грейбах
//	{
//		GRBALPHABET nn; //нетерминал (левый символ прафила) <0
//		int iderror;	//идентификатор диагностического сообщения
//		short size;		//количество цепочек - правых частей правила
//		struct Chain	//цепочка(правая часть правила)
//		{
//			short size;						//длинна цепочки
//			GRBALPHABET* nt;				//цепочка терминалов(>0) и нетерминалов(<0)
//			Chain() { size = 0; nt = 0; };	
//			Chain(
//				short psize,			//количество символов в цепочке
//				GRBALPHABET s, ...		//символы(т и не т)
//			) {
//				nt = new GRBALPHABET[size = psize];
//				int* p = (int*)&s;
//				for (short i = 0; i < psize; ++i)nt[i] = (GRBALPHABET)p[i];
//			};
//
//			char* getCCHain(char* b) {
//				for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
//				b[size] = 0x00;
//				return b;
//			};	//получить правую сторону правила
//			static GRBALPHABET T(char t) { return GRBALPHABET(T); };	//терминал
//			static GRBALPHABET N(char t) { return -GRBALPHABET(T); };	//нетерминал
//			static bool isT(GRBALPHABET s) { return s > 0; };			//терминал?
//			static bool isN(GRBALPHABET s) { return !isT(s); };			//нетерминал?
//			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };
//		}* chains;	//массив цепочек - правых частей правила
//		Rule() { nn = 0x00; size = 0; }
//		Rule(
//			GRBALPHABET pnn, //нетерминал (< 0)
//			int piderror,	 //итендификатор диагностического сообщения(ERROR)	
//			short psize,	 //количество цепочек - правых частей правила
//			Chain c, ...	 //множество цепочек - правых частей правила
//		) {
//			nn = pnn;
//			iderror = piderror;
//			chains = new Chain[size = psize];
//			Chain* p = &c;
//			for (int i = 0; i < size; i++)chains[i] = p[i];
//		};
//		char* getCRule(		//получить правило в виде n->цепочка(для распечатки)
//			char* b,		//буфер
//			short nchain	//номер цепочки (правой части) в правиле
//		);
//		short getNextChain(	//получить следующую за J подходящую цепочку, вернуть её номер или -1
//			GRBALPHABET t,	//первый символ цепочки
//			Rule::Chain& pchain,		//возвращенная цепочка
//			short j						//номер цепочки
//		);
//	};
//
//	struct Greibach			//грамматика Грейбах
//	{
//		short size;			//количество правил
//		GRBALPHABET startN;	//стартовый символ
//		GRBALPHABET stbottomT;	//дно стека
//		Rule* rules;			//сножество правил
//		Greibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; };
//		Greibach(
//			GRBALPHABET pstartN,	//стартовый символ
//			GRBALPHABET pstbottomT,	//дно стека
//			short psize,			//количество правил
//			Rule r, ...			//правила
//		) {
//			startN = pstartN;
//			stbottomT = pstbottomT;
//			rules = new Rule[size = psize];
//			Rule* p = &r;
//			for (int i = 0; i < size; i++)rules[i] = p[i];
//		};
//		short getRule( //получить номеп правила или -1
//			GRBALPHABET pnn, //левый символ правила
//			Rule& prule		//возвращаемое слово грамматики
//		);
//		Rule getRule(short n); //получить правило по номеру
//	};
//	Greibach getGreibach(); //получить грамматику
//}