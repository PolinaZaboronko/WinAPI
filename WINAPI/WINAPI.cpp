#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR mainMessage1[] = L"Послушайте!";//символьный тип данных-аналог char и wchar_t(UNICODE)
TCHAR mainMessage2[] = L"кто-то называет эти плевочки жемчужиной?";
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
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE-12);//кисть фона, цвет для рисования клиентской области
	wc.lpszMenuName = NULL;//для создания меню(у нас его нет)
	wc.lpfnWndProc = WndProc;//оконная процедура для оконного класса
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//установка курсора
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);//иконка для приложения

	RegisterClassW(&wc);//функция регистрации класса окна в системе
	hwnd = CreateWindowW(wc.lpszClassName, L"Маяковский",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		250, 50, 750, 650, NULL, NULL, hInstance, NULL);//параметры окна

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
	RECT rect;//структура определения размера клиентской области
	COLORREF colorText = RGB(0x81, 0x03, 0xff);//цвет текста
	COLORREF colorBackground = RGB(0, 0, 0);//цвет фона
	HWND textbox1;//текстовое окно
	HWND textbox2;
	HWND textbox3;
	static HWND button;//кнопка
	HINSTANCE hlnst;
	WNDCLASSW wc;
	wc.lpszClassName = L"Моя новая форма";
		
	switch (msg) {
	
	case WM_PAINT://если нужно нарисовать, то:
		hDC = BeginPaint(hwnd, &ps);//инициалирует контекст устройсва
		GetClientRect(hwnd, &rect);//ширина и высота поля для рисования
		SetTextColor(hDC, colorText);//цвет контекстного устройства
		DrawText(hDC, mainMessage1, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);//рисование текста 
	break;

	case WM_CREATE://сообщение создания окна
		textbox1 = CreateWindow(L"EDIT", L"Ведь, если звезды зажигают -", WS_BORDER | WS_CHILD | WS_VISIBLE, 215, 350, 280, 20, hwnd, NULL, NULL, NULL);//создаем текстовое поле
		textbox2 = CreateWindow(L"EDIT", L"значит - это кому-нибудь нужно?", WS_BORDER | WS_CHILD | WS_VISIBLE, 215, 370, 280, 20, hwnd, NULL, NULL, NULL);
		textbox3 = CreateWindow(L"EDIT", L"Значит - кто-то хочет, чтобы они были?", WS_BORDER | WS_CHILD | WS_VISIBLE, 215, 390, 280, 20, hwnd, NULL, NULL, NULL);
		button = CreateWindow(L"Button", L"Значит -", WS_BORDER | WS_CHILD | WS_VISIBLE, 550, 500, 120, 35, hwnd, 0, 0, NULL);//создаем кнопку
		ShowWindow(button, SW_NORMAL);//выводим кнопку на экран
	break;

	case WM_COMMAND://когда выбирается командный пункт из меню (уведомительное сообщение)
		if (lParam == (LPARAM)button) {//сообщение при нажатии на кнопку
			MessageBox(hwnd, mainMessage2, L"Значит -", MB_APPLMODAL);//вывод сообщения
		}
	break;

	case WM_DESTROY:
		SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
		PostQuitMessage(0);
		break;
	}
	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

