//---------------------------------------------------------------------------
// File: main.cpp
// By:   HeliSRaiN 
//       SnipGhost  
//                                                        Главный файл работы
//---------------------------------------------------------------------------
#include "packcage.h"
#include "Interface.h"
//#include "../Personal/mywork.h"
//---------------------------------------------------------------------------
int main()
{
	system("chcp 1251 > nul");

	menuRun(); //Визуализированное меню

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// ПРОСТО ПРИМЕР!
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Word *w = new Word;
	w->len = 5;
	w->symbols = new char[w->len];
	w->symbols = "hell";

	Sentence *s = new Sentence;
	s->size = 3;
	s->word = new Word*[s->size];
	s->word[0] = w;
	s->word[1] = w;
	s->word[2] = w;

	Text *t = new Text;
	t->size = 2;
	t->sent = new Sentence*[t->size];
	t->sent[0] = s;
	t->sent[1] = s;
	cout << *t;
  
	cout << t->sent[1]->word[2]->symbols[2] << endl; 
	// Без разыменования (есть оператор)
  
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Text *text = getText(inputText());
	//if (text != NULL) doMyHomeWork(text);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	char *text = inputText();
	cout << endl << text << endl;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	say("Завершение работы ...");
	return 0;
}
//---------------------------------------------------------------------------