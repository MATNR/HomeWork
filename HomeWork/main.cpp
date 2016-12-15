//---------------------------------------------------------------------------
// File: main.cpp
// By:   HeliSRaiN 
//       SnipGhost  
//                                                        Главный файл работы
//---------------------------------------------------------------------------
#include "packcage.h"  // Содержит все необходимые библиотеки и функции
#include "interface.h" // Содержит расширенный графический интерфейс
//#include "../Personal/mywork.h"
//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
int main()
{
	system("chcp 1251 > nul");

	//menuRun(); //Визуализированное меню

	Text *text = getText(inputText());
	if (text == NULL) {
		cout << "Ошибка ввода текста" << endl;
		return 0;
	}
	//if (text != NULL) doMyHomeWork(text);

	for (int i = 0; i < text->size; ++i)
	{
		Sentence *s = text->sent[i];
		if (s == NULL) continue;
		cout << "\nПредложение #" << i << " " << s << endl;
		for (int j = 0; j < s->size; ++j)
		{
			Word *w = s->word[j];
			if (w == NULL) continue;
			cout << "\tСлово #" << j << " " << *w << endl;
			if (DEBUG) {
				cout << "\t\tАтрибут = ";
				cout << ((w->attr) ? ((char)w->attr) : ('0'));
				cout << "\tФ.О.Н. = " << ((w->flag) ? "true" : "false");
				cout << endl;
			}
		}
	}

	say("Завершение работы ...");
	delete text;

	return 0;
}
//---------------------------------------------------------------------------