#pragma once

#define ID_MAXSIZE		5 //макс кол-во символов в итендиф
#define	TI_MAXSIZE		4096 //макс кол-во строк в табл итендификаторов
#define TI_INT_DEFAULT	0x00000000	//значение int по дефолту
#define	TI_STR_DEFAULT	0x00		//значение string по дефолту
#define	TI_NULLIDX		0xffffffff	//нет элемента таблицы итендификаторов
#define	TI_STR_MAXSIZE	255

#define FALSYNUMBER 17//используй как нуль

namespace IT	//таблица итендификаторов
{
	enum IDDATATYPE {INT=1, STR=2};//таблица данных итендификаторов fls - empty
	enum IDTYPE		{V=1, F=2, P=3, L=4};//типы итендификаторов - переменная функция параметр литерал

	struct Entry //строка таблицы итендификаторов
	{
		int idxfirstLE; //индекс первой строки в таблице лексем
		char id[ID_MAXSIZE]; //итендификатор
		char scope[ID_MAXSIZE]; //итендификатор
		IDDATATYPE iddatatype; //тип данных
		IDTYPE idtype; //тип итендификатора
		union {
			int vint; //значение integer
			struct
			{
				char len;//кол-во символов в string
				char str[TI_STR_MAXSIZE];//символы стринг
			} vstr;//значение sting
		} value; //значение итендификатора
		
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

	struct IdTable		//экземпляр таблицы ид
	{
		int maxsize;	//ёмкость таблицы
		int size;		//текущий размер
		Entry* table;	//массив строк таблицы итендификаторов
	};
	IdTable Create(	//создать таблицу ID
		int size	//ёмкость
	);
	void Add(
		IdTable& idtable,	//экземпляр таблицы итендификаторов
		Entry entry			//строка таблицы итендификаторов
	);
	Entry GetEntry(	//получить строку таблицы итендификаторов
		IdTable& idtable,	//экземпляр таблицы итендификаторов
		int n				//строка таблицы итендификаторов
	);
	int IsId(
		IdTable& idtable,	//возврат: номер строки(если есть) TI_NULLID(если нет)
		char id[ID_MAXSIZE], //итендификатор
		char scope[ID_MAXSIZE]
	);

	void Delete(IdTable& idtable);	//удалить таблицу итендификаторов
}