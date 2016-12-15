//---------------------------------------------------------------------------
// File: packcage.cpp
// By:   SnipGhost
//                                                         Библиотека функций
//---------------------------------------------------------------------------
#include "packcage.h"
//---------------------------------------------------------------------------
// Ввод и проверка текста
//---------------------------------------------------------------------------
char* inputText()
{
	char *text = new char[MAX_TEXT_LEN], ch;
	int count = 0;
	do {	
		if (count >= MAX_TEXT_LEN-1) {
			cout << "\nПревышен максимальный размер текста\n";
			text[MAX_TEXT_LEN-1] = '\0';
			return text;
		}
		ch = getch(); // Ввод символов "налету" по нажатию клавиш
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		// Проверка введенного символа
		bool isLowerLatin = (ch >= 'a' && ch <= 'z');
		bool isUpperLatin = (ch >= 'A' && ch <= 'Z');
		bool isPunctMarks = (ch == ' '||ch == ','||ch == '.'||ch == '-');
		if ( isLowerLatin || isUpperLatin || isPunctMarks)
			text[count++] = ch;
		else if (ch == BACK_SYMBOL)
			count--;
		else if (ch == END_OF_TEXT)
			text[count++] = '\0';
		else
			ch = BEEP_SYMBOL; // Аналогично: Beep(1000, 400);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		cout << ch; // Выводим, чтобы пользователь видел, что он вводит
	} while (ch != END_OF_TEXT);
	return text;
}
//---------------------------------------------------------------------------
// Формирование текста
//---------------------------------------------------------------------------
Text* getText(const char *txt)
{
	if (txt == NULL) return NULL;
	Text *text = new Text;
	const char *ptr = txt;
	text->size = 1;          // Учитываем, что у нас должно быть хотя бы одно
	while (*ptr != '\0')     // Считаем кол-во предложений (по точкам)
	{
		bool pass = (*(ptr+1) == ' ' && *(ptr+2) == '\0');
		bool isPoint = (*ptr == '.' && *(ptr+1) != '.');
		if (isPoint && *(ptr+1) != '\0' && !pass) text->size++; 
		ptr++;
	}
	text->sent = new Sentence *[text->size];
	char *token, *next_token, *delim = ".";
	token = new char[strlen(txt)+1];
	strcpy(token, txt);
	int count = 0;
	token = strtok_s(token, delim, &next_token); 
	while (token != NULL && count < text->size)
	{
		text->sent[count++] = getSentence(token);
		token = strtok_s(NULL, delim, &next_token);
	}
	return text;
}
//---------------------------------------------------------------------------
Text::~Text()
{
	if (DEBUG) cout << "[..] Удаление текста (" << size << " предложений)\n";
	for (int i = 0; i < size; i++)
		delete sent[i];
	delete [] sent;
	if (DEBUG) cout << "[OK] Текст удален\n";
}
//---------------------------------------------------------------------------
// Формирование педложения
//---------------------------------------------------------------------------
Sentence* getSentence(const char *txt)
{
	if (txt == NULL) return NULL;
	Sentence *sent = new Sentence;
	const char *ptr = txt;
	sent->size = 1;          // Учитываем, что у нас должно быть хотя бы одно
	while (*ptr != '\0')     // Считаем кол-во слов (по пробелам)
	{
		bool isSpace = *ptr == ' ' && *(ptr+1) != ' ';
		if (isSpace && *(ptr+1) != '\0' && ptr != txt) sent->size++;
		ptr++;
	}
	sent->word = new Word *[sent->size];
	char *token, *next_token, *delim = " ";
	token = new char[strlen(txt)+1];
	strcpy(token, txt);
	int count = 0;
	token = strtok_s(token, delim, &next_token);
	while (token != NULL && count < sent->size)
	{
		sent->word[count++] = getWord(token);
		token = strtok_s(NULL, delim, &next_token);
	}
	return sent;
}
//---------------------------------------------------------------------------
Sentence::~Sentence()
{
	if (DEBUG) cout << "[..] Удаление предложения (" << size << " слов)\n";
	for (int i = 0; i < size; i++)
		delete word[i];
	delete [] word;
	if (DEBUG) cout << "[OK] Предложение удалено\n";
}
//---------------------------------------------------------------------------
// Формирование слова
//---------------------------------------------------------------------------
Word* getWord(const char *txt)
{
	if (txt == NULL) return NULL;
	Word *word = new Word;
	unsigned len = strlen(txt);
	word->symbols = new char[len+1];
	strcpy(word->symbols, txt);
	if (txt[len-1] == ',') {
		word->attr = 1;
		word->symbols[len-1] = '\0';
	} else {
		word->attr = 0;
	}
	return word;
}
//---------------------------------------------------------------------------
Word::~Word()
{
	if (DEBUG) cout << "[..] Удаление слова " << symbols << endl;
	delete [] symbols;
	if (DEBUG) cout << "[OK] Слово удалено\n";
}
//---------------------------------------------------------------------------
// Вспомогательная функция вывода
//---------------------------------------------------------------------------
void say(const char *msg)
{
	cout << msg << endl;
	system("pause");
}
//---------------------------------------------------------------------------