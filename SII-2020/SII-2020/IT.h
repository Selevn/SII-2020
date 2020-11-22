#pragma once

#define ID_MAXSIZE		5 //���� ���-�� �������� � �������
#define	TI_MAXSIZE		4096 //���� ���-�� ����� � ���� ���������������
#define TI_INT_DEFAULT	0x00000000	//�������� int �� �������
#define	TI_STR_DEFAULT	0x00		//�������� string �� �������
#define	TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define	TI_STR_MAXSIZE	255

#define FALSYNUMBER 17//��������� ��� ����

namespace IT	//������� ���������������
{
	enum IDDATATYPE {INT=1, STR=2};//������� ������ ��������������� fls - empty
	enum IDTYPE		{V=1, F=2, P=3, L=4};//���� ��������������� - ���������� ������� �������� �������

	struct Entry //������ ������� ���������������
	{
		int idxfirstLE; //������ ������ ������ � ������� ������
		char id[ID_MAXSIZE]; //�������������
		char scope[ID_MAXSIZE]; //�������������
		IDDATATYPE iddatatype; //��� ������
		IDTYPE idtype; //��� ��������������
		union {
			int vint; //�������� integer
			struct
			{
				char len;//���-�� �������� � string
				char str[TI_STR_MAXSIZE];//������� ������
			} vstr;//�������� sting
		} value; //�������� ��������������
		
		Entry(int idxfirstLE, char* id, const char* scope, IDDATATYPE iddatatype, IDTYPE idtype) {
			this->idxfirstLE = idxfirstLE;
			this->iddatatype = iddatatype;
			this->idtype = idtype;
			//this->scope = scope;
			if (iddatatype == STR)
			{
				this->value.vstr.str[0] = '\0';
				this->value.vstr.len = 0;
			}
			if (iddatatype == INT)
			{
				this->value.vint = 0;
			}

				
#pragma region "Writedown id name"
			int len = 0;
			for (int i = 0; id[i]!='\0' && i< ID_MAXSIZE; i++)
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

#pragma region "Writedown scope name"
			len = 0;
			for (int i = 0; scope[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->scope[i] = scope[i];
			}

			for (int i = 0; i < len && i< ID_MAXSIZE; i++)
			{
				this->scope[i] = scope[i];
			}
			if (len >= ID_MAXSIZE)
				this->scope[ID_MAXSIZE - 1] = '\0';
			else
				this->scope[len] = '\0';
#pragma endregion

		};
		Entry(int idxfirstLE, char* id, const char* scope, IDDATATYPE iddatatype, IDTYPE idtype, int data) {
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

#pragma region "Writedown scope name"
			len = 0;
			for (int i = 0; scope[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->scope[i] = scope[i];
			}

			for (int i = 0; i < len && i < ID_MAXSIZE; i++)
			{
				this->scope[i] = scope[i];
			}
			if (len >= ID_MAXSIZE)
				this->scope[ID_MAXSIZE - 1] = '\0';
			else
				this->scope[len] = '\0';
#pragma endregion

		};
		Entry(int idxfirstLE, char* id, const char* scope, IDDATATYPE iddatatype, IDTYPE idtype, char* data) {
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

#pragma region "Writedown scope name"
			len = 0;
			for (int i = 0; scope[i] != '\0' && i < ID_MAXSIZE; i++)
			{
				len++;
				this->scope[i] = scope[i];
			}

			for (int i = 0; i < len && i < ID_MAXSIZE; i++)
			{
				this->scope[i] = scope[i];
			}
			if (len >= ID_MAXSIZE)
				this->scope[ID_MAXSIZE - 1] = '\0';
			else
				this->scope[len] = '\0';
#pragma endregion

			len = 0;
			for (int i = 1; data[i] != '\''; i++)
			{
				len++;
			}
			this->value.vstr.len = len;
			if (len > TI_STR_MAXSIZE)
			{
				//error
				//std::cout << "TI STR MAXSIZE ERROR" << std::endl;
			}
			else
			{
				//this->value.vstr.str = new char[len];
				for (int i = 1; i < len; i++)
				{
					this->value.vstr.str[i-1] = data[i];
				}
				this->value.vstr.str[len-1] = '\0';
			}
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
		char id[ID_MAXSIZE], //�������������
		char scope[ID_MAXSIZE]
	);

	void Delete(IdTable& idtable);	//������� ������� ���������������
}