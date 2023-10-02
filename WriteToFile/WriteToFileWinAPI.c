// WriteToFileWinAPI.c : This file contains the 'main' function. Program execution begins and ends there.
//

/*
Developer: Ahmed abdel Haleem Ahmed
Date:30-09-2023
Purpose: Win32 api file Access example.
*/


#define _CRT_SECURE_NO_WARNINGS

#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>


#define IDC_TEXT    1000
#define MAX_STRINGS 256
#define MAX_LENGTH 63


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreveInstance, LPSTR lpCmdLine, int nCmdShow)
{

    OPENFILENAME ofn;       // common dialog box structure
    wchar_t szFile[260];       // buffer for file name
    HWND hwnd = NULL;              // owner window
    HANDLE hf = NULL;              // file handle

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    //
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    //
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = (LPCWSTR)L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Display the Open dialog box. 

    if (GetOpenFileName(&ofn) == TRUE) {
        hf = CreateFile(ofn.lpstrFile, GENERIC_WRITE,
            0, (LPSECURITY_ATTRIBUTES)NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
            (HANDLE)NULL);

        wchar_t HString[] = L"Hello World! in a file !!! مرحبا أيها العالم";

        // Write data to the file
        DWORD bytesWritten;
        WriteFile(
            hf,                 // Handle to the file
            HString,            // Buffer to write
            sizeof(HString),    // Buffer size
            &bytesWritten,      // Bytes written
            NULL);              // Overlapped

        // Close the handle once we don't need it.
        if (hf)
            CloseHandle(hf);


        MessageBox(NULL, ofn.lpstrFile, (LPCWSTR)L"File Name", MB_ICONEXCLAMATION | MB_OK);

    }

    if (!hf) {
        MessageBox(NULL, L"لم تقم باختيار الملف المطلوب للكتابة عليه", (LPCWSTR)L"ملف غير موجود!", MB_ICONEXCLAMATION | MB_OK);
        return 1;

    }

    return 0;
}
