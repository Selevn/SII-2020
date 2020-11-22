#pragma once
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0XFFFFFFFF
#define LEX_INTEGER 't'
#define LEX_STRING	't'
//#define LEX_STRING	't'
#define LEX_ID		'i'
#define LEX_MAIN	'm'
#define LEX_LITERAL	'l'
#define LEX_FUNCTION 'f'
#define LEX_DECLARE	'd'
#define LEX_RETURN	'r'
#define LEX_PRINT	'p'
#define LEX_SEMICOLON ';'
#define LEX_COMMA	','
#define LEX_LEFTBRACE '{'
#define LEX_RIGHTBRACE	'}'
#define LEX_LEFTHESIS	'('
#define LEX_RIGHTHESIS	')'
#define LEX_PLUS		'v'
#define LEX_MINUS		'v'
#define LEX_STAR		'v'
#define LEX_DIRSLASH	'v'
#define LEX_EQUAL		'v'

#define EMPTY_DATA		'\0'

namespace LT
{
	struct Entry //������ ������� ������
	{
		char lexema;//�������
		int sn; //����� ������ � �������� ������
		int idxTI;	//������ �������������� � �������
		char data;

		Entry(
			char lexema,
			int sn, //����� ������ � �������� ������
			int idxTI,	//������ �������������� � �������
			char symbol = EMPTY_DATA
		) {
			this->lexema = lexema;
			this->sn = sn;
			this->idxTI = idxTI;
			this->data = data;
		};

		Entry() = default;
	};
	struct LexTable //��������� ������� ������
	{
		int maxsize; //������� <LT_MAXSIZE
		int size; //������� ������ ������� ������
		Entry* table;	//������ �����
	};
	LexTable Create(//������� ������� ������
		int size//������� ������� ������ < ��_�������
	);
	void Add(	//�������� ������ � ������� ������
		LexTable& lextable,		//��������� ������� ������
		Entry entry	//������ ������� ������
	);
	Entry GetEntry(	//�������� ������ ������� ������
		LexTable& lextable, //���������
		int n //����� ���������� ������
	);

	
	void Delete(LexTable& lextable);	//������� ������� ������
}