//---------------------------------------------------------------------------
// File: interface.cpp
// By:   HeliSRaiN
//                                                Файл визуализации программы
//---------------------------------------------------------------------------
#include "interface.h"
//---------------------------------------------------------------------------
enum keys {           // Ключи для интерфейса меню
	KEY_CMD1 = '1',
	KEY_CMD2,
	KEY_CMD3,
	KEY_EXIT = 'q'
};
//---------------------------------------------------------------------------
#ifdef NDEBUG
//===========================================================================
//============================= КРАСИВОЕ МЕНЮ ===============================
//===========================================================================
#define SMALL_SPACE ("                     ")
#define LONG_SPACE ("                                  ")
//---------------------------------------------------------------------------
enum color {          // А - более светлый вариант, B - более тёмный
	BLACK = 0,
	BLUE_B,
	GREEN_B,
	Cyan,
	Red_B,
	Magenta,
	Brown,
	GRAY_A,
	GRAY_B,
	BLUE_A,
	GREEN_A,
	LightCyan,
	RED_A,
	LightMagenta,
	YELLOW,
	WHITE  
};
//---------------------------------------------------------------------------
HWND hwnd = FindWindow("ConsoleWindowClass", NULL); //Вызываем хэндлер
HDC dc = GetDC(hwnd);
//---------------------------------------------------------------------------
void SetColor(color text, color background) 
{
   HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
//---------------------------------------------------------------------------
void drawBitmap(HDC hdcA, int x, int y, HBITMAP hbmA)
{
	BITMAP bm; //Технология хранения граф. файлов - BMP
	POINT ptSize, ptOrg;
	HDC hdcB = CreateCompatibleDC(hdcA); 
	//"Помогатор" для правильного рисования. Он создаёт контекст памяти.
	HBITMAP hbmB = (HBITMAP)SelectObject(hdcB, hbmA); 
	//Оператор, который помогает загружать изображение в память
	if (hbmB) { //Если ошибок нема, то продолжает
		SetMapMode(hdcB, GetMapMode(hdcA));
		GetObject(hbmA, sizeof(BITMAP), (LPSTR) &bm); 
		// Определяем размеры нашего изображения
		ptSize.x = bm.bmWidth; // Тута ширина
		ptSize.y = bm.bmHeight; // Тута высота
		DPtoLP(hdcA, &ptSize, 1); // Перевод с одних координат на другие..
		ptOrg.x = 0; //Обнуляем
		ptOrg.y = 0; //Обнуляем
		DPtoLP(hdcB, &ptOrg, 1); // переводит значение hdcB в другую
		BitBlt(hdcA, x, y, ptSize.x, ptSize.y, hdcB, ptOrg.x, ptOrg.y, SRCCOPY); 
		//ВОООТ, сам процесс рисовки!
		SelectObject(hdcB, hbmB); 
		//Возвращаем начальные значения контекста памяти
	}
	DeleteDC(hdcB); //И к херам его удаляем (контекст памяти)
}
//---------------------------------------------------------------------------
void drawImageToDisplay(char *logoDir, int height, int width, int x, int y)
{
	static HBITMAP hBitmap;
	PAINTSTRUCT ps;  
	static char MyName[260] = { 0 }; // :SG: Классное имя переменной ...
	GetModuleFileNameA(NULL, MyName, sizeof(MyName));
	HWND hwnd = FindWindow(NULL, MyName); //Вызываем хандлер
	HDC hdc;
	hdc = GetWindowDC(hwnd);
	hBitmap = (HBITMAP)LoadImage(NULL, logoDir, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	InvalidateRect(hwnd,NULL,TRUE);
	hdc = BeginPaint(hwnd,&ps);
	drawBitmap(hdc, y, x, hBitmap);
	EndPaint(hwnd,&ps);
}
//---------------------------------------------------------------------------
void showLogo()
{
	drawImageToDisplay("image//LogoImage.bmp", 175, 500, 30, 30); 
	//Выводим наше распрекрасное лого
	Sleep(WAIT_TIME_TO_LOGO);
	for (int t = 0; t < 18; t++) cout << "\n";
	SetColor(YELLOW, BLACK);
	cout << SMALL_SPACE << "ДЗ ПО ОСНОВАМ ПРОГРАММИРОВАНИЯ" << endl;
	SetColor(WHITE, BLACK);
	Sleep(WAIT_TIME_TO_PRINT);
	SetColor(RED_A, BLACK);
	cout << SMALL_SPACE << "КОМАНДА 2.0: "; 
	SetColor(WHITE, BLACK);
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "Михаил Кучеренко" << endl;
	Sleep(WAIT_TIME_TO_PRINT);
	cout << LONG_SPACE << "Артём Сахаров" << endl;
	Sleep(WAIT_TIME_TO_PRINT);
	cout << LONG_SPACE << "Тагир Ханмурзин" << endl;
	Sleep(WAIT_TIME_TO_PRINT);
	cout << LONG_SPACE << "Никита Москальцов" << endl;
	Sleep(WAIT_TIME_TO_PRINT);
	cout << LONG_SPACE << "Роман Мирзоян" << endl;
	Sleep(WAIT_TIME_TO_HIDE);
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); 
	//По простунски прикрываем всё "чёрной шапочкой"
}
//---------------------------------------------------------------------------
int Menu()
{
	system("cls");
	drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
	drawImageToDisplay("image//EnterComands.bmp", 50, 250, 195, 15);
	for (int t = 0; t < 21; t++) cout << "\n";
	char point;
	cin >> point;
	while (point < KEY_CMD1 && point > KEY_CMD3 && point != KEY_EXIT) 
	{
		drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0);
		drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
		drawImageToDisplay("image//FailComand.bmp", 50, 250, 195, 15);
		system("cls");
		for (int t = 0; t < 21; t++) cout << "\n";
		cin >> point;
	}
	return (int)point;
}
//---------------------------------------------------------------------------
//ИНТЕРФЕЙС СТРАНИЦЫ "ВВОД ТЕКСТА"
Text *entryTextInter(Text *text) 
{
	if (text != NULL) delete text; // Если уже было создано
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); 
	//Замазываем предыдущее
	system("cls"); //Очищаем от текста (ЧЕГО БЛТ?)
	// :SG: Коментарии не должны оскорблять интеллект читателя
	drawImageToDisplay("image//EnterText.bmp", 50, 250, 15, 15); 
	//Вывод картинки "Ввод текста"

	cout << "\n\n\n\n\n\n"; // Отступ подправлен под картинку
	text = getText(inputText());

	while (text == NULL)
	{
		system("cls");
		//Вывод картинки "ПЛОХОЙ ТЕКСТ, ПОПРОБУЙТЕ СНОВА"
		drawImageToDisplay("image//RewriteText.bmp", 50, 250, 15, 15); 
		cout << "\n\n\n\n\n\n"; // Отступ подправлен под картинку
		text = getText(inputText());   // Вводим текст
	}
	return text;
}
//---------------------------------------------------------------------------
//ИНТЕРФЕЙС СТРАНИЦЫ "ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ"
Text *indivTaskInter(Text *text) 
{
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0);
	system("cls");
	bool checkExit = 0;
	if (text == NULL) { //Если не прошли первый пункт "ВВОД ТЕКСТА"
		drawImageToDisplay("image//iTNotAvailable.bmp", 50, 250, 15, 15); 
		//Вывод картинки "Индивидуальные задания НЕДОСТУПНЫ!"
		system("pause");
		return NULL;
	}

	drawImageToDisplay("image//indivTask.bmp", 50, 250, 15, 15); 
	//Вывод картинки "Индивидуальные задания НЕДОСТУПНЫ!"

	cout << "\n\n\n\n\n\n\n"; //Отступ подправлен под картинку
	// ВЫВОД КАЖДОГО ИНДИВИДУАЛЬНОГО ЗАДАНИЯ И ЕГО ОТВЕТА
	// doMyHomeWork(text); // Функция выполнения домашнего задания :SG:
	printText(text);

	system("pause");
	return text;
}
#else
//===========================================================================
//=========================== КЛАССИЧЕСКОЕ МЕНЮ =============================
//===========================================================================
void showLogo()
{
	cout << "ДЗ ПО ОСНОВАМ ПРОГРАММИРОВАНИЯ\n\n";
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "КОМАНДА 2.0: \n"; 
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "\tМихаил Кучеренко\n";
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "\tАртём Сахаров\n";
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "\tТагир Ханмурзин\n";
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "\tНикита Москальцов\n";
	Sleep(WAIT_TIME_TO_PRINT);
	cout << "\tРоман Мирзоян\n";
	Sleep(WAIT_TIME_TO_HIDE);
}
//---------------------------------------------------------------------------
void showMenu()
{
	system("cls");
	cout << "----------= Меню =----------\n";
	cout << (char)KEY_CMD1 << ". Ввести текст.\n";
	cout << (char)KEY_CMD2 << ". Индивидуальное задание.\n";
	cout << (char)KEY_EXIT << ". Заверешение программы.\n";
	cout << "----------------------------\n";
}
//---------------------------------------------------------------------------
int Menu()
{
	showMenu();
	char point;
	cin >> point;
	while (point < KEY_CMD1 && point > KEY_CMD3 && point != KEY_EXIT) 
	{
		showMenu();
		cout << " Неверная команда, попробуйте еще раз: ";	
		cin >> point;
	}
	return (int)point;
}
//---------------------------------------------------------------------------
//ИНТЕРФЕЙС СТРАНИЦЫ "ВВОД ТЕКСТА"
Text *entryTextInter(Text *text) 
{
	if (text != NULL) delete text;
	system("cls");

	cout << "Введите текст, ";
	cout << "звуковой сигнал означает что символ недопустим.\n\n";

	text = getText(inputText());

	while (text == NULL)
	{
		system("cls");
		cout << "Некорректный текст, попробуйте снова.\n\n";
		text = getText(inputText());
	}
	return text;
}
//---------------------------------------------------------------------------
//ИНТЕРФЕЙС СТРАНИЦЫ "ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ"
Text *indivTaskInter(Text *text) 
{
	system("cls");
	bool checkExit = 0;
	if (text == NULL) { //Если не прошли первый пункт "ВВОД ТЕКСТА"
		cout << "Текст еще не введен! Сначала введите текст.\n";
		system("pause");
		return NULL;
	}
	printText(text);
	system("pause");
	return text;
}
//===========================================================================
#endif
//---------------------------------------------------------------------------
int menuRun(Text *&text) 
{
	system("chcp 1251 > nul");
	showLogo();
	while (true) {
		int c = Menu(); // Вернет значения ТОЧНО из keys
		switch (c)
		{
			case KEY_CMD1: // ВВОД ТЕКСТА
				text = entryTextInter(text); 
			break;
			case KEY_CMD2: // ИНДИВИДУАЛЬНЫЕ ЗАДАНИЯ
				text = indivTaskInter(text);
			break;
			case KEY_CMD3: // ВЫХОД
			case KEY_EXIT: // АЛЬТЕРНАТИВНЫЙ ВЫХОД
				say("Завершение работы ...");
				delete text;
				return 0;
			break;
		}
	}
}
//---------------------------------------------------------------------------