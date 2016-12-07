﻿//---------------------------------------------------------------------------
// File: packcage.h
// By:   SnipGhost
//                                                         Библиотека функций
//---------------------------------------------------------------------------
#pragma once
#ifndef PACKCAGE_H
#define PACKCAGE_H
//---------------------------------------------------------------------------
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
const bool DEBUG = 1; // Вывоод отладочной информации - да/нет (1/0)
const int MAX_TEXT_LEN = 1024; // 
const char END_OF_TEXT = 0x04;
//---------------------------------------------------------------------------
struct Word 
{
	char *symbols;    // Массив символов слова
	int len;          // Длина слова
	~Word();          // Очистка памяти
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Классическая перегрузка оператора <<
	friend ostream& operator <<(ostream &os, const Word &n)
	{
		os << n.symbols;
		return os;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Удобная перегрузка оператора << (для указателей)
	friend ostream& operator <<(ostream &os, const Word *n)
	{
		os << n->symbols;
		return os;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};
//---------------------------------------------------------------------------
struct Sentence
{
	Word **word;      // Массив указателей на слова
	int size;         // Кол-во слов в предложении
	~Sentence();      // Очистка памяти
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	friend ostream& operator <<(ostream &os, const Sentence &n)
	{
		for (int i = 0; i < n.size; ++i)
		{
			os << *(n.word[i]);
			if (i != n.size-1) os << " ";
			else os << ".";
		}
		return os;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};
//---------------------------------------------------------------------------
struct Text
{
	Sentence **sent; // Массив указателей на предложения
	int size;        // Кол-во предложений в тексте
	~Text();         // Очистка памяти
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	friend ostream& operator <<(ostream &os, const Text &n)
	{
		for (int i = 0; i < n.size; ++i)
		{
			os << *(n.sent[i]);
			if (i != n.size-1) os << " ";
			else os << "\n";
		}
		return os;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
};
//---------------------------------------------------------------------------
char* inputText(istream &input);        // Ввод и проверка текста
Text* getText(const char *txt);         // Формирование текста
Sentence* getSentence(const char *txt); // Формирование предложения
Word* getWord(const char *txt);         // Формирование слова
//---------------------------------------------------------------------------
void say(const char *msg);              // Вспомогательная функция вывода
//---------------------------------------------------------------------------
#endif /* PACKCAGE_H */
//---------------------------------------------------------------------------