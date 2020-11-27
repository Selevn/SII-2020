#include "GRB.h"
#include <string.h>
#include "stdarg.h"
#include "Lt.h"
#define GRB_ERROR_SERIES 600


namespace GRB
{

	Greibach greibach(NS('S'), TS('$'),
		6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0,
			4, //todo m{NrE;};     tfi(F){NrE;};S     m{NrE;};S           tfi(F){NrE;};
			Rule::Chain(8, TS(LEX_MAIN), TS('{'), NS('N'), TS(LEX_RETURN), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(15,TS(LEX_DECLARE), TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS(LEX_RETURN), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS(LEX_MAIN), TS('{'), NS('N'), TS(LEX_RETURN), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(14, TS(LEX_DECLARE), TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS(LEX_RETURN), NS('E'), TS(';'), TS('}'), TS(';'))
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 1,
			15, //todo dti;   rE;   i=E;   dtfi(F);   dti;N   rE;N   i=E;N   dtfi(F);N pl;N pi;N pl; pi; pi(W);
			Rule::Chain(4, TS(LEX_DECLARE), TS(LEX_TYPE), TS(LEX_ID), TS(';')),
			Rule::Chain(3, TS(LEX_RETURN), NS('E'), TS(';')),
			Rule::Chain(4, TS(LEX_ID), TS('v'), NS('E'), TS(';')),
			Rule::Chain(8, TS(LEX_DECLARE), TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(8, TS(LEX_EXPORT), TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS(';')),

			Rule::Chain(5, TS(LEX_DECLARE), TS(LEX_TYPE), TS(LEX_ID), TS(';'), NS('N')),
			Rule::Chain(4, TS(LEX_RETURN), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS(LEX_ID), TS('v'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(9, TS(LEX_DECLARE), TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(9, TS(LEX_EXPORT), TS(LEX_TYPE), TS(LEX_FUNCTION), TS(LEX_ID), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),

			Rule::Chain(4, TS('p'), TS(LEX_ID), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS(LEX_LITERAL), TS(';'), NS('N')),

			Rule::Chain(3, TS('p'), TS(LEX_ID), TS(';')),
			Rule::Chain(3, TS('p'), TS(LEX_LITERAL), TS(';')),

			Rule::Chain(6, TS('p'), TS(LEX_ID), TS('('), NS('W'), TS(')'), TS(';'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2,
			8, //todo i   l   (E)   i(W)   iM   lM   (E)M   i(W)M
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS(LEX_ID), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS(LEX_ID), NS('M')),
			Rule::Chain(2, TS(LEX_LITERAL), NS('M')),
			Rule::Chain(4, TS(')'), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS(LEX_ID), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 3,
			4, //todo vE    vEM   v(E) v(E)M
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(4, TS('v'), TS('('), NS('E'), TS(')')),
			Rule::Chain(5, TS('v'), TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 4,
			2, //todo ti   ti,F
			Rule::Chain(2, TS(LEX_TYPE), TS(LEX_ID)),
			Rule::Chain(4, TS(LEX_TYPE), TS(LEX_ID), TS(','), NS('F'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5,
			4, //todo i   l   i,W   l,W
			Rule::Chain(1, TS(LEX_ID)),
			Rule::Chain(1, TS(LEX_LITERAL)),
			Rule::Chain(3, TS(LEX_ID), TS(','), NS('W')),
			Rule::Chain(3, TS(LEX_LITERAL), TS(','), NS('W'))
		)
	);



	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)
		: size(psize)
	{
		nt = new GRBALPHABET[psize];
		va_list params;
		va_start(params, psize);
		for (short i = 0; i < psize; ++i)
			nt[i] = va_arg(params, GRBALPHABET);
	};
	Rule::Rule() : chains(NULL), size(0), nn(0), iderror(NULL) {}
	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
		: nn(pnn), iderror(piderror), size(psize)
	{
		chains = new Chain[psize];
		va_list params;
		va_start(params, psize);
		for (int i = 0; i < size; i++)
			chains[i] = va_arg(params, Chain);
	};
	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)
		: startN(pstartN), stbottomT(pstbottom), size(psize)
	{
		rules = new Rule[psize];
		va_list params;
		va_start(params, psize);
		for (int i = 0; i < size; i++)
			rules[i] = va_arg(params, Rule);
	};
	Greibach getGreibach() { return greibach; };
	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1, i = 0;
		while (i < size && rules[i].nn != pnn)
			i++;
		rc = i < size ? i : -1;
		prule = rules[rc];
		return rc;
	};
	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	};
	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn);
		b[1] = '-';
		b[2] = '>';
		b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	};
	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t)
			++j;
		rc = j < size ? j : -1;
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	};
	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};


	


}


