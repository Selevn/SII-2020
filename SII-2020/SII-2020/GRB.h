#pragma once
#include "Error.h"
#include <iomanip>
typedef short GRBALPHABET; //������� �������� ���������� ���������>0. �����������<0

#define MFST_TRACE_START(LOG) *log.stream << std::setw( 4)<<std::left<<"���"<<":" \
	<< std::setw(20) << std::left << "�������"  \
	<< std::setw(30) << std::left << "������� �����" \
	<< std::setw(20) << std::left << "����" \
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
//	struct Rule //������� ���������� �������
//	{
//		GRBALPHABET nn; //���������� (����� ������ �������) <0
//		int iderror;	//������������� ���������������� ���������
//		short size;		//���������� ������� - ������ ������ �������
//		struct Chain	//�������(������ ����� �������)
//		{
//			short size;						//������ �������
//			GRBALPHABET* nt;				//������� ����������(>0) � ������������(<0)
//			Chain() { size = 0; nt = 0; };	
//			Chain(
//				short psize,			//���������� �������� � �������
//				GRBALPHABET s, ...		//�������(� � �� �)
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
//			};	//�������� ������ ������� �������
//			static GRBALPHABET T(char t) { return GRBALPHABET(T); };	//��������
//			static GRBALPHABET N(char t) { return -GRBALPHABET(T); };	//����������
//			static bool isT(GRBALPHABET s) { return s > 0; };			//��������?
//			static bool isN(GRBALPHABET s) { return !isT(s); };			//����������?
//			static char alphabet_to_char(GRBALPHABET s) { return isT(s) ? char(s) : char(-s); };
//		}* chains;	//������ ������� - ������ ������ �������
//		Rule() { nn = 0x00; size = 0; }
//		Rule(
//			GRBALPHABET pnn, //���������� (< 0)
//			int piderror,	 //������������� ���������������� ���������(ERROR)	
//			short psize,	 //���������� ������� - ������ ������ �������
//			Chain c, ...	 //��������� ������� - ������ ������ �������
//		) {
//			nn = pnn;
//			iderror = piderror;
//			chains = new Chain[size = psize];
//			Chain* p = &c;
//			for (int i = 0; i < size; i++)chains[i] = p[i];
//		};
//		char* getCRule(		//�������� ������� � ���� n->�������(��� ����������)
//			char* b,		//�����
//			short nchain	//����� ������� (������ �����) � �������
//		);
//		short getNextChain(	//�������� ��������� �� J ���������� �������, ������� � ����� ��� -1
//			GRBALPHABET t,	//������ ������ �������
//			Rule::Chain& pchain,		//������������ �������
//			short j						//����� �������
//		);
//	};
//
//	struct Greibach			//���������� �������
//	{
//		short size;			//���������� ������
//		GRBALPHABET startN;	//��������� ������
//		GRBALPHABET stbottomT;	//��� �����
//		Rule* rules;			//��������� ������
//		Greibach() { short size = 0; startN = 0; stbottomT = 0; rules = 0; };
//		Greibach(
//			GRBALPHABET pstartN,	//��������� ������
//			GRBALPHABET pstbottomT,	//��� �����
//			short psize,			//���������� ������
//			Rule r, ...			//�������
//		) {
//			startN = pstartN;
//			stbottomT = pstbottomT;
//			rules = new Rule[size = psize];
//			Rule* p = &r;
//			for (int i = 0; i < size; i++)rules[i] = p[i];
//		};
//		short getRule( //�������� ����� ������� ��� -1
//			GRBALPHABET pnn, //����� ������ �������
//			Rule& prule		//������������ ����� ����������
//		);
//		Rule getRule(short n); //�������� ������� �� ������
//	};
//	Greibach getGreibach(); //�������� ����������
//}