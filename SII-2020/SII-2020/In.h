#pragma once
#include "LT.h"
#define IN_MAX_LEN_TEXT 1024*1024 //���� ������ ��������� ���� 1 ��
#define IN_CODE_ENDL '\n' //������ ����� ������
#define DIVIDE ';' //�����������
//������� �������� ������� ����������, ������ = ���(Windows-1251) �������
//�������� IN::F - ����������� ������, IN::T - ����������� ������, IN::I - ������������(�� �������),
// ���� 0�= �������� 256 - �� �������� ������ ��������

#define IN_CODE_TABLE {\
IN::T,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::T,/* */\
IN::T,/*newline*/\
IN::F,/**/\
IN::F,/**/\
IN::T,/*newline*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*left-arrow*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::T,/* */\
IN::T,/*!*/\
IN::T,/*"*/\
IN::T,/*#*/\
IN::T,/*$*/\
IN::T,/*%*/\
IN::T,/*&*/\
IN::T,/*'*/\
IN::L,/*(*/\
IN::L,/*)*/\
IN::L,/***/\
IN::L,/*+*/\
IN::L,/*,*/\
IN::L,/*-*/\
IN::T,/*.*/\
IN::L,/*/*/\
IN::T,/*0*/\
IN::T,/*1*/\
IN::T,/*2*/\
IN::T,/*3*/\
IN::T,/*4*/\
IN::T,/*5*/\
IN::T,/*6*/\
IN::T,/*7*/\
IN::T,/*8*/\
IN::T,/*9*/\
IN::L,/*:*/\
IN::L,/*;*/\
IN::L,/*<*/\
IN::L,/*=*/\
IN::L,/*>*/\
IN::L,/*?*/\
IN::T,/*@*/\
IN::T,/*A*/\
IN::T,/*B*/\
IN::T,/*C*/\
IN::T,/*D*/\
IN::T,/*E*/\
IN::T,/*F*/\
IN::T,/*G*/\
IN::T,/*H*/\
IN::T,/*I*/\
IN::T,/*J*/\
IN::T,/*K*/\
IN::T,/*L*/\
IN::T,/*M*/\
IN::T,/*N*/\
IN::T,/*O*/\
IN::T,/*P*/\
IN::T,/*Q*/\
IN::T,/*R*/\
IN::T,/*S*/\
IN::T,/*T*/\
IN::T,/*U*/\
IN::T,/*V*/\
IN::T,/*W*/\
IN::T,/*X*/\
IN::T,/*Y*/\
IN::T,/*Z*/\
IN::L,/*[*/\
IN::T,/*\*/\
IN::L,/*]*/\
IN::L,/*^*/\
IN::T,/*_*/\
IN::T,/*`*/\
IN::T,/*a*/\
IN::T,/*b*/\
IN::T,/*c*/\
IN::T,/*d*/\
IN::T,/*e*/\
IN::T,/*f*/\
IN::T,/*g*/\
IN::T,/*h*/\
IN::T,/*i*/\
IN::T,/*j*/\
IN::T,/*k*/\
IN::T,/*l*/\
IN::T,/*m*/\
IN::T,/*n*/\
IN::T,/*o*/\
IN::T,/*p*/\
IN::T,/*q*/\
IN::T,/*r*/\
IN::T,/*s*/\
IN::T,/*t*/\
IN::T,/*u*/\
IN::T,/*v*/\
IN::T,/*w*/\
IN::T,/*x*/\
IN::T,/*y*/\
IN::T,/*z*/\
IN::L,/*{*/\
IN::T,/*|*/\
IN::L,/*}*/\
IN::T,/*~*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/* */\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/*�*/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
IN::F,/**/\
}


namespace In
{
	struct lexems
	{
		int line;
		int col;
		unsigned char* lexem;
	};

	struct IN //�������� ������
	{
		enum { T = 1024, F = 2048, I = 4096, L = 256, S = 0 }; //S - space t - ���������� ������ F- ������������ I- ������������, ����� �������� L - Single lexem
		int size;		//������ ��������� ����
		int lines;		//���������� �����
		int ignor;		//���-�� ����������������� ��������
		unsigned char* text;		//�������� ��� (Windows - 1251)
		int code[256];		//������� �������� T, F, I ����� ��������

		//UPD

		bool oneQuoteOpened;
		bool doubleQuoteOpened;
		bool tildaQuoteOpened;

		//UPD 2
		lexems lexems[4096];
		int lexemPos;

	};
	IN getin(wchar_t infile[]);  //������ � ��������� ������� �����
}