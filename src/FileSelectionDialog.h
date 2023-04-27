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
    FileDialog();
    bool ShowOpenFileDialog(std::string& fileContent);
};

#endif //CSC10002_DATA_STRUCTURE_VISUALIZER_FILESELECTIONDIALOG_H
