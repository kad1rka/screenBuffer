// screenBuffer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <windows.h>
#include <conio.h>

int bufferCreationActivation() {
    // 1. Создание и активания буфера экрана
    
    HANDLE hStdOutOld, hStdOutNew;
    DWORD dwWritten;
    hStdOutNew = CreateConsoleScreenBuffer(
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        CONSOLE_TEXTMODE_BUFFER,
        NULL);
    if (hStdOutNew == INVALID_HANDLE_VALUE)
    {
        _cputs("Create console screen buffer failed.\n");
        return GetLastError();
    }
    hStdOutOld = GetStdHandle(STD_OUTPUT_HANDLE);
    _cputs("Press any key to set new screen buffer active.\n");
    _getch();

    if (!SetConsoleActiveScreenBuffer(hStdOutNew))
    {
        _cputs("Set new console active screen buffer failed.\n");
        return GetLastError();
    }
    char text[] = "This is a new screen buffer.";
    if (!WriteConsole(hStdOutNew,
        text,
        sizeof(text),
        &dwWritten,
        NULL))
        _cputs("Write console output character failed.\n");
    char str[] = "\nPress any key to set old screen buffer.";
    if (!WriteConsole(
        hStdOutNew,
        str,
        sizeof(str),
        &dwWritten,
        NULL))
        _cputs("Write console output character failed");
    _getch();

    if (!SetConsoleActiveScreenBuffer(hStdOutOld))
    {
        _cputs("Set old console active screen buffer failed.\n");
        return GetLastError();
    }
    _cputs("This is an old console screen buffer.\n");
    CloseHandle(hStdOutNew);
    _cputs("Press any key to finish.\n");
    _getch();
    return 0;
       
}


int OutOnScreen() {
    // 2. Вывод на экран информации о буфере экрана
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        std::cout << "Console screen buffer info failed.\n";
    std::cout << "Console screen buffer info: " << std::endl << std::endl;

    std::cout << "A number of columns = " << csbi.dwSize.X << std::endl;
    std::cout << "A number of rows = " << csbi.dwSize.Y << std::endl;
    std::cout << "X cursor coordinate = " << csbi.dwCursorPosition.X << std::endl;
    std::cout << "Y cursor coordinate = " << csbi.dwCursorPosition.Y << std::endl;
    std::cout << "Attributes = " << std::hex << csbi.wAttributes << std::dec << std::endl;
    std::cout << "Window upper corner = " << csbi.srWindow.Left << "," << csbi.srWindow.Top << std::endl;
    std::cout << "Window lower corner = " << csbi.srWindow.Right << "," << csbi.srWindow.Bottom << std::endl;
    std::cout << "Maximum number of columns = " << csbi.dwMaximumWindowSize.X << std::endl;
    std::cout << "Maximum number of rows = " << csbi.dwMaximumWindowSize.Y << std::endl << std::endl;
    return 0;

}

int newScreenBuffer() {

    // 3. Установка новых размеров буфера экрана

    COORD coord;
    HANDLE hStdOut;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "Enter new screen buffer size." << std::endl;
    std::cout << "A number of columns: ";
    std::cin >> coord.X;
    std::cout << "A number of rows: ";
    std::cin >> coord.Y;

    if (!SetConsoleScreenBufferSize(hStdOut, coord))
    {
        std::cout << "Set console screen buffer size failed." << std::endl;
        return GetLastError();

    }
    return 0;
}


int main()
{
    newScreenBuffer();
}

