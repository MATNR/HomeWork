//---------------------------------------------------------------------------
// File: interface.cpp
// By:   HeliSRaiN
//                                                Файл визуализации программы
//---------------------------------------------------------------------------
#include "interface.h"
//---------------------------------------------------------------------------
HWND hwnd = FindWindow("ConsoleWindowClass", NULL); //Вызываем хэндлер
HDC dc = GetDC(hwnd);
int point = 0;
bool checkFirstAct = false; //Переменная для проверки 
//---------------------------------------------------------------------------
enum color { //А - более светлый вариант, B - более тёмный
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
		HDC hdcB = CreateCompatibleDC(hdcA); //"Помогатор" для правильного рисования. Он создаёт контекст памяти. Вроде усё.
		HBITMAP hbmB = (HBITMAP)SelectObject(hdcB, hbmA); //Оператор, который помогает загружать изображение в память
		if (hbmB){ //Если ошибок нема, то продолжает
			SetMapMode(hdcB, GetMapMode(hdcA));
			GetObject(hbmA, sizeof(BITMAP), (LPSTR) &bm); // Определяем размеры нашего изображения
			ptSize.x = bm.bmWidth; //Тута ширина
			ptSize.y = bm.bmHeight; //Тута высота
			DPtoLP(hdcA, &ptSize, 1); //Перевод с одних координат на другие.. тут не понял, нафига? Умные штуки
			ptOrg.x = 0; //Обнуляем
			ptOrg.y = 0; //Обнуляем
			DPtoLP(hdcB, &ptOrg, 1); //Перевод с одних координат на другие.. опять, но переводит значение hdcB в другую
			BitBlt(hdcA, x, y, ptSize.x, ptSize.y, hdcB, ptOrg.x, ptOrg.y, SRCCOPY); //ВОООТ, сам процесс рисовки!
			SelectObject(hdcB, hbmB); //Возвращаем начальные значения контекста памяти
		}
		DeleteDC(hdcB); //И к херам его удаляем (контекст памяти)
}
//---------------------------------------------------------------------------
void drawImageToDisplay(char *logoDir, int height, int width, int x, int y)
{
	static HBITMAP hBitmap;
	PAINTSTRUCT ps;  
	static char MyName[260]={0};
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
void animationLogo()
{
	drawImageToDisplay("image//LogoImage.bmp", 175, 500, 30, 30); //Выводим наше распрекрасное лого
	Sleep(WAIT_TIME_TO_LOGO);

	for (int t = 0; t < 18; t++) cout << "\n";
	SetColor(YELLOW, BLACK);
	cout << SMALL_SPACE << "ДЗ ПО ОСНОВАМ ПРОГРАММИРОВАНИЯ" << endl;
	SetColor(WHITE, BLACK);
	Sleep(WAIT_TIME_TO_PRINT);
	SetColor(RED_A, BLACK);
	cout << SMALL_SPACE << "КОМАНДА 2: "; 
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
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); //По простунски прикрываем всё "чёрной шапочкой"
}
//---------------------------------------------------------------------------
void menuDesign()
{
	drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
	drawImageToDisplay("image//EnterComands.bmp", 50, 250, 195, 15);
	for (int t = 0; t < 21; t++) cout << "\n";
	cin >> point;
	while (point >= 4 || point == 0){
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0);
	drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
	drawImageToDisplay("image//FailComand.bmp", 50, 250, 195, 15);
	system("CLS");
	for (int t = 0; t < 21; t++) cout << "\n";
	cin >> point;
	}
}
//---------------------------------------------------------------------------
//ИНТЕРФЕЙС СТРАНИЦЫ "ВВОД ТЕКСТА"
void entryTextInter(Text *&text) 
{
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); //Замазываем предыдущее
	system("CLS"); //Очищаем от текста
	drawImageToDisplay("image//EnterText.bmp", 50, 250, 15, 15); //Вывод картинки "Ввод текста"
	int checkEntry = 0;
	do { 
		cout << "\n\n\n\n\n\n"; // Отступ подправлен под картинку

		// <<<<<< SnipGhost
		text = getText(inputText());   // Вводим текст
		if (text == NULL) {            // Проверяем его
			checkEntry = 0; 
			system("CLS");
			drawImageToDisplay("image//RewriteText.bmp", 50, 250, 15, 15); //Вывод картинки "ПЛОХОЙ ТЕКСТ, ПОПРОБУЙТЕ СНОВА"
		} else {
			checkEntry = 1;
		}
		// >>>>>> SnipGhost

	} while (checkEntry == 0);

	if (checkEntry == 1) { //Если этап с проверкой правильности текста прошёл на ОК
		checkFirstAct = true; //Первый этап пройден, теперь нам открыт второй пункт меню!
	}
}
//---------------------------------------------------------------------------
//ИНТЕРФЕЙС СТРАНИЦЫ "ИНДИВИДУАЛЬНОЕ ЗАДАНИЕ"
void indivTaskInter(Text *&text) 
{
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); //Замазываем предыдущее
	system("CLS"); //Очищаем от текста
	bool checkExit = 0;
	if (checkFirstAct == false){ //Если не прошли первый пункт "ВВОД ТЕКСТА"
		drawImageToDisplay("image//iTNotAvailable.bmp", 50, 250, 15, 15); //Вывод картинки "Индивидуальные задания НЕДОСТУПНЫ!"
		while (checkExit == 0) {
			 cout << "\n\n\n\n\n\n\n"; //Отступ подправлен под картинку
			 cout << "Выйти в меню? 1/0" << endl;
			 cin >> checkExit;
		}
		returnToMenu(text);
	} else {
		drawImageToDisplay("image//indivTask.bmp", 50, 250, 15, 15); //Вывод картинки "Индивидуальные задания НЕДОСТУПНЫ!"

		cout << "\n\n\n\n\n\n\n"; //Отступ подправлен под картинку
		//ВЫВОД КАЖДОГО ИНДИВИДУАЛЬНОГО ЗАДАНИЯ И ЕГО ОТВЕТА
		//doMyHomeWork(text); // Функция выполнения домашнего задания [:SG:]
		printText(text);

		while (checkExit == 0) {
			
			cout << "Выйти в меню? 1/0" << endl;
			cin >> checkExit;
		}
		returnToMenu(text);
	}
}
//---------------------------------------------------------------------------
//ТУТ ПРОИЗВОДИТСЯ ПРИВЯЗКА К ДЕЙСТВИЮ ПОСЛЕ ВВОДА КОМАНДЫ
int menuDo(Text *&text)
{
	menuDesign();
	switch (point)
	{
		case 1: //ВВОД ТЕКСТА
			entryTextInter(text); 
			returnToMenu(text);
		break;
		case 2: //ИНДИВИДУАЛЬНЫЕ ЗАДАНИЯ
			indivTaskInter(text);
			returnToMenu(text);
		break;
		case 3: 
			return 0; //Выход
		break;
	}
	return 0;
}
//---------------------------------------------------------------------------
void returnToMenu(Text *&text)
{
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0); //Замазываем чёрной шапкой
	system("CLS");
	menuDo(text);
}
 //---------------------------------------------------------------------------
int menuRun(Text *&text) 
{
	system("chcp 1251 > nul"); // Русифицируем
	animationLogo();           // Выводим лого
	system("CLS");             // Выносим все текстовые из консольки
	menuDo(text); 
	return 0;
}
//---------------------------------------------------------------------------