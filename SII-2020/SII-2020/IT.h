#pragma once

#define ID_MAXSIZE		25 //���� ���-�� �������� � �������
#define	TI_MAXSIZE		4096 //���� ���-�� ����� � ���� ���������������
#define TI_INT_DEFAULT	0x00000000	//�������� int �� �������
#define	TI_STR_DEFAULT	0x00		//�������� string �� �������
#define	TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define	TI_STR_MAXSIZE	255

#define FALSYNUMBER 17//��������� ��� ����

namespace IT	//������� ���������������
{
	enum IDDATATYPE { INT = 1, STR = 2 };//������� ������ ��������������� fls - empty
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4 };//���� ��������������� - ���������� ������� �������� �������

	struct Entry //������ ������� ���������������
	{
		int idxfirstLE; //������ ������ ������ � ������� ������
		char id[ID_MAXSIZE]; //�������������
		bool isExternal; //�������������
		IDDATATYPE iddatatype; //��� ������
		IDTYPE idtype; //��� ��������������
		union {
			int vint; //�������� integer
			char vchar;//�������� sting
		} value; //�������� ��������������

		Entry(int idxfirstLE, const char* id, IDDATATYPE iddatatype, IDTYPE idtype) {
			this->isExternal = false;
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
			if (iddatatype == STR)
			{
				this->value.vchar = '\0';
			}
			if (iddatatype == INT)
			{
				this->value.vint = 0;
			}


#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->id[i] = id[i];
			}
			if (len >= ID_MAXSIZE)
				this->id[ID_MAXSIZE - 1] = '\0';
			else
			{
				this->id[len] = '\0';
			}
#pragma endregion

		};
		Entry(int idxfirstLE, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, bool e) {
			this->isExternal = e;
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
			if (iddatatype == STR)
			{
				this->value.vchar = '\0';
			}
			if (iddatatype == INT)
			{
				this->value.vint = 0;
			}

#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->id[i] = id[i];
			}
			if (len >= ID_MAXSIZE)
				this->id[ID_MAXSIZE - 1] = '\0';
			else
			{
				this->id[len] = '\0';
			}
#pragma endregion

		};
		Entry(int idxfirstLE, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int data) {
			this->isExternal = false;
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
			this->value.vint = data;
#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->id[i] = id[i];
			}
			if (len >= ID_MAXSIZE)
				this->id[ID_MAXSIZE - 1] = '\0';
			else
			{
				this->id[len] = '\0';
			}
#pragma endregion

		};
		Entry(int idxfirstLE, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, int data,bool e) {
			this->isExternal = e;
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
			this->value.vint = data;
#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->id[i] = id[i];
			}
			if (len >= ID_MAXSIZE)
				this->id[ID_MAXSIZE - 1] = '\0';
			else
			{
				this->id[len] = '\0';
			}
#pragma endregion

		};

		Entry(int idxfirstLE, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, char data, bool e) {
			this->isExternal = e;
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->id[i] = id[i];
			}
			if (len >= ID_MAXSIZE)
				this->id[ID_MAXSIZE - 1] = '\0';
			else
			{
				this->id[len] = '\0';
			}
#pragma endregion

			this->value.vchar = '\0';
			//if (len > TI_STR_MAXSIZE)
			//{
			//	//error
			//	//std::cout << "TI STR MAXSIZE ERROR" << std::endl;
			//}
			//else
			//{
			//	//this->value.vstr.str = new char[len];
			//	for (int i = 1; i < len; i++)
			//	{
			//		this->value.vstr.str[i - 1] = data[i];
			//	}
			//	this->value.vstr.str[len - 1] = '\0';
			//}
		};
		Entry(int idxfirstLE, const char* id, IDDATATYPE iddatatype, IDTYPE idtype, char data) {
			this->isExternal = false;
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->id[i] = id[i];
			}
			if (len >= ID_MAXSIZE)
				this->id[ID_MAXSIZE - 1] = '\0';
			else
			{
				this->id[len] = '\0';
			}
#pragma endregion

			this->value.vchar = '\0';
			//if (len > TI_STR_MAXSIZE)
			//{
			//	//error
			//	//std::cout << "TI STR MAXSIZE ERROR" << std::endl;
			//}
			//else
			//{
			//	//this->value.vstr.str = new char[len];
			//	for (int i = 1; i < len; i++)
			//	{
			//		this->value.vstr.str[i - 1] = data[i];
			//	}
			//	this->value.vstr.str[len - 1] = '\0';
			//}
		};

		Entry() = default;
	};

	struct IdTable		//��������� ������� ��
	{
		int maxsize;	//������� �������
		int size;		//������� ������
		Entry* table;	//������ ����� ������� ���������������
	};
	IdTable Create(	//������� ������� ID
		int size	//�������
	);
	void Add(
		IdTable& idtable,	//��������� ������� ���������������
		Entry entry			//������ ������� ���������������
	);
	Entry GetEntry(	//�������� ������ ������� ���������������
		IdTable& idtable,	//��������� ������� ���������������
		int n				//������ ������� ���������������
	);
	int IsId(
		IdTable& idtable,	//�������: ����� ������(���� ����) TI_NULLID(���� ���)
		char id[ID_MAXSIZE] //�������������
	);
	bool isUniq(IdTable& idtable,	//�������: ����� ������(���� ����) TI_NULLID(���� ���)
		char id[ID_MAXSIZE]);
	void Delete(IdTable& idtable);	//������� ������� ���������������
}