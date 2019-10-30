#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//HWND hwnd, дескриптор окна(описатель окна, от которого пришло сообщение)
//UINT message, номер сообщения;
//WPARAM wParam,  дополнительная информация о сообщении
//LPARAM IParam);  дополнительная информация о сообщении

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {//значение содержит желаемый вид окна (например, свернутый или развернутый)

	MSG  msg;
	HWND hwnd;
	WNDCLASSW wc;

	wc.style = CS_HREDRAW | CS_VREDRAW;//стиль класса окна(внутренняя область окна д.б. перерисована при изменении размеров окна)
	wc.cbClsExtra = 0;//число дополнительных байт, которые размещаются вслед за структурой класса
	wc.cbWndExtra = 0;
	wc.lpszClassName = L"Window";//подкласс окна
	wc.hInstance = hInstance;//установка экземпляра программы
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE - 4);//кисть фона, цвет для рисования клиентской области
	wc.lpszMenuName = NULL;//для создания меню(у нас его нет)
	wc.lpfnWndProc = WndProc;//оконная процедура для оконного класса
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//установка курсора
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//иконка для приложения

	RegisterClassW(&wc);//функция регистрации класса окна в системе
	hwnd = CreateWindowW(wc.lpszClassName, L"Графика",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		250, 50, 800, 650, NULL, NULL, hInstance, NULL);//параметры окна

	ShowWindow(hwnd, nCmdShow);//показ окна
	UpdateWindow(hwnd);//если область обновления непуста, то функция посылает сообщение прямо оконной функции данного окна

	while (GetMessage(&msg, NULL, 0, 0)) {
		DispatchMessage(&msg);//данные строки показывают окно на экране
	}
	return (int)msg.wParam;//код завершения возвращается в систему
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {//оконная процедура
	HDC hDC;//дескриптор ориентации текста на экране
	PAINTSTRUCT ps;//структура, в которой содержится информация о клиенской области(размеры, цвет и т.д.)
	HFONT hFont;
	COLORREF colorText = RGB(0x81, 0x03, 0xff);//цвет текста
	COLORREF colorBackground = RGB(0, 0, 0);//цвет фона
	HPEN hPen1, hPen2, hPen3, hPen4, hPen5, hPen6;
	HBRUSH hBrush;//создание объекта-кисти
	WNDCLASSW wc;
	wc.lpszClassName = L"Моя новая форма";

	switch (msg) {

	case WM_PAINT://если нужно нарисовать, то:
		hDC = BeginPaint(hwnd, &ps);//инициалирует контекст устройсва
		hPen1 = CreatePen(PS_DASHDOT, 4, RGB(186, 7, 40));//задет стиль пера
		hPen2 = CreatePen(PS_DASHDOT, 4, RGB(217, 24, 59));
		hPen3 = CreatePen(PS_DASHDOT, 4, RGB(237, 9, 51));
		hPen4 = CreatePen(PS_DASHDOT, 4, RGB(247, 87, 87));
		SelectObject(hDC, hPen1);
		MoveToEx(hDC, 15, 45, NULL);
		LineTo(hDC, 115, 10);
		SelectObject(hDC, hPen2);
		MoveToEx(hDC, 15, 65, NULL);
		LineTo(hDC, 115, 30);
		SelectObject(hDC, hPen3);
		MoveToEx(hDC, 15, 85, NULL);
		LineTo(hDC, 115, 50);
		SelectObject(hDC, hPen4);
		MoveToEx(hDC, 15, 105, NULL);
		LineTo(hDC, 115, 70);

		SelectObject(hDC, hPen1);
		MoveToEx(hDC, 125, 10, NULL);
		LineTo(hDC, 225, 45);
		DeleteObject(hPen1);
		SelectObject(hDC, hPen2);
		MoveToEx(hDC, 125, 30, NULL);
		LineTo(hDC, 225, 65);
		DeleteObject(hPen2);
		SelectObject(hDC, hPen3);
		MoveToEx(hDC, 125, 50, NULL);
		LineTo(hDC, 225, 85);
		DeleteObject(hPen3);
		SelectObject(hDC, hPen4);
		MoveToEx(hDC, 125, 70, NULL);
		LineTo(hDC, 225, 105);
		DeleteObject(hPen4);
		hPen5 = CreatePen(PS_DASHDOT, 3, RGB(255, 247, 3));
		SelectObject(hDC, hPen5);
		Ellipse(hDC, 65, 90, 170, 190);
		DeleteObject(hPen5);
		hPen6 = CreatePen(PS_DASHDOT, 2, RGB(76, 49, 247));
		SelectObject(hDC, hPen6);
		hBrush = CreateSolidBrush(RGB(58, 28, 255));//задает кисть
		SelectObject(hDC, hBrush);
		Ellipse(hDC, 20, 205, 223, 260);
		DeleteObject(hPen6);
		DeleteObject(hBrush);

		static LOGFONT lf1; //создаём экземпляр LOGFONT
		lf1.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
		lf1.lfPitchAndFamily = DEFAULT_PITCH; //значения по умолчанию
		lf1.lfHeight = 20; //высота
		lf1.lfWidth = 10; //ширина
		lf1.lfWeight = 40; //толщина
		lf1.lfEscapement = 0; //шрифт без поворота

		static LOGFONT lf2; //создаём экземпляр LOGFONT
		lf2.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
		lf2.lfHeight = 20; //высота
		lf2.lfWidth = 11; //ширина
		lf2.lfWeight = 40; //толщина
		lf2.lfEscapement = 0; //шрифт без поворота

		static LOGFONT lf3; //создаём экземпляр LOGFONT
		lf3.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
		lf3.lfHeight = 22; //высота
		lf3.lfWidth = 10; //ширина
		lf3.lfWeight = 40; //толщина
		lf3.lfEscapement = 0; //шрифт без поворота

		static LOGFONT lf4; //создаём экземпляр LOGFONT
		lf4.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
		lf4.lfItalic = 1;
		lf4.lfHeight = 20; //высота
		lf4.lfWidth = 10; //ширина
		lf4.lfWeight = 40; //толщина
		lf4.lfEscapement = 0; //шрифт без поворота

		hFont = CreateFontIndirect(&lf1); //Cоздали шрифт
		SelectObject(hDC, hFont); //Он будет иметь силу только когда мы его выберем
		SetTextColor(hDC, RGB(102, 0, 92)); //зададим цвет текста
		SetBkColor(hDC, RGB(240, 255, 253)); //зададим цвет фона
		SelectObject(hDC, hFont);
		::TextOut(hDC, 25, 300, L"По вечерам над ресторанами", 26);

		hFont = CreateFontIndirect(&lf2); //Cоздали шрифт
		SelectObject(hDC, hFont); //Он будет иметь силу только когда мы его выберем
		SetTextColor(hDC, RGB(102, 0, 92)); //зададим цвет текста
		SetBkColor(hDC, RGB(240, 255, 253)); //зададим цвет фона
		SelectObject(hDC, hFont);
		::TextOut(hDC, 25, 330, L"Горячий воздух дик и глух,", 26);

		hFont = CreateFontIndirect(&lf3); //Cоздали шрифт
		SelectObject(hDC, hFont); //Он будет иметь силу только когда мы его выберем
		SetTextColor(hDC, RGB(102, 0, 92)); //зададим цвет текста
		SetBkColor(hDC, RGB(240, 255, 253)); //зададим цвет фона
		SelectObject(hDC, hFont);
		::TextOut(hDC, 25, 360, L"И правит окриками пьяными", 26);

		hFont = CreateFontIndirect(&lf4); //Cоздали шрифт
		SelectObject(hDC, hFont); //Он будет иметь силу только когда мы его выберем
		SetTextColor(hDC, RGB(102, 0, 92)); //зададим цвет текста
		SetBkColor(hDC, RGB(240, 255, 253)); //зададим цвет фона
		SelectObject(hDC, hFont);
		::TextOut(hDC, 25, 390, L"Весенний и тлетворный дух.", 26);

		ValidateRect(hwnd, NULL);//пpовеpяет достовеpность области пользователя, удаляя Rect из области обновления окна
		EndPaint(hwnd, &ps);//закончили рисовать
		break;

	case WM_DESTROY:
		SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}