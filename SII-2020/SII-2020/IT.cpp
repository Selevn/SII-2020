#include "IT.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdarg>
#include "Error.h"



namespace IT
{
	IdTable Create(	//������� ������� ID
		int size	//�������
	) {
		if (size > TI_MAXSIZE)
		{
			throw ERROR_THROW(130);
		}
		IdTable out;
		out.maxsize = size;
		out.size = 0;
		out.table = new Entry[size];
		return out;
	};
	void Add(
		IdTable& idtable,	//��������� ������� ���������������
		Entry entry			//������ ������� ���������������
	) {
		if (idtable.size + 1 > idtable.maxsize)
			throw ERROR_THROW(133);
		idtable.table[idtable.size++] = entry;
		//add error maxsize
	};
	Entry GetEntry(	//�������� ������ ������� ���������������
		IdTable& idtable,	//��������� ������� ���������������
		int n				//������ ������� ���������������
	) {
		if (idtable.size + 1 > idtable.maxsize)
			throw ERROR_THROW(134);
		//add error with n
		return idtable.table[n];
	};
	int IsId(
		IdTable& idtable,	//�������: ����� ������(���� ����) TI_NULLIDX(���� ���)
		char id[ID_MAXSIZE], //�������������
		char scope[ID_MAXSIZE]
	) {
		int flag = -1;
		bool isRightScope = false;
		bool bflag = true;
		for (int i = 0; i < idtable.size; i++)
		{
			//checkScope
			if (idtable.table[i].idtype != F) {
			for (int j = 0; j < strlen(scope) && j < ID_MAXSIZE; j++)
			{
					if (idtable.table[i].scope[j] != scope[j])
					{
						isRightScope = false;
						break;
					}
					isRightScope = true;
				}
			}
			else
			{
				isRightScope = true;
			}
			////////////

			if (isRightScope)
			{
				for (int j = 0; j < strlen(id) && j < ID_MAXSIZE; j++)
				{

					if (idtable.table[i].id[j] != id[j])
					{
						bflag = false;
						break;
					}
					else {
						bflag = true;
					}

				}
				if (bflag)
					return i;
			}
		}
		return TI_NULLIDX;
	};

	void Delete(IdTable& idtable) {
		delete &idtable;
	};

}