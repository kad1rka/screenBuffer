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





int main()
{
    bufferCreationActivation();
}

