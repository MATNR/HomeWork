//---------------------------------------------------------------------------
// File: interface.cpp
// By:   HeliSRaiN
//                                                Файл визуализации программы
//---------------------------------------------------------------------------
#include "interface.h"
#include "packcage.h"
//---------------------------------------------------------------------------
HWND hwnd = FindWindow("ConsoleWindowClass", NULL); //Вызываем хэндлер
HDC dc = GetDC(hwnd);
int point = 0;
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
	while (point >= 5 || point == 0){
	drawImageToDisplay("image//Black.bmp", 1000, 1000, 0, 0);
	drawImageToDisplay("image//Menu.bmp", 190, 250, 15, 15);
	drawImageToDisplay("image//FailComand.bmp", 50, 250, 195, 15);
	system("CLS");
	for (int t = 0; t < 21; t++) cout << "\n";
	cin >> point;
	}
}
//---------------------------------------------------------------------------
//ТУТ ПРОИЗВОДИТСЯ ПРИВЯЗКА К ДЕЙСТВИЮ ПОСЛЕ ВВОДА КОМАНДЫ
int menuDo()
{
	menuDesign();
	switch (point){
	case 1: 
		say("КОМАНДА 1");
	break;
	case 2: 
		say("КОМАНДА 2");
	break;
	case 3: 
		say("КОМАНДА 3");
	break;
	case 4: 
		return 0;
	break;
	}
	return 0;
}
//---------------------------------------------------------------------------
void returnToMenu()
{
	system("CLS");
	menuDo();
}
 //---------------------------------------------------------------------------
int menuRun () 
{
	system("chcp 1251 > nul"); // Русифицируем
	animationLogo();           // Выводим лого
	system("CLS");             // Выносим все текстовые из консольки
	menuDo(); 
	return 0;
}
//---------------------------------------------------------------------------