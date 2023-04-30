#ifndef CSC10002_DATA_STRUCTURE_VISUALIZER_FILESELECTIONDIALOG_H
#define CSC10002_DATA_STRUCTURE_VISUALIZER_FILESELECTIONDIALOG_H

#include <string>
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>

class FileDialog {
public:
    explicit FileDialog(HWND hwnd = nullptr);
    std::string ShowOpenFileDialog();

private:
    HWND hwnd_;
    TCHAR szFileName_[MAX_PATH];
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_FILESELECTIONDIALOG_H
