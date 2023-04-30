#include "FileSelectionDialog.h"

FileDialog::FileDialog(HWND hwnd) : hwnd_(hwnd) {}

std::string FileDialog::ShowOpenFileDialog() {
    // Save the current working directory
    char currentDir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentDir);

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd_;
    ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    ofn.lpstrFile = szFileName_;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = _T("txt");
    std::string content;
    if (GetOpenFileName(&ofn) == TRUE) {
        // User selected a file
        std::ifstream file(ofn.lpstrFile);
        getline(file, content);
        file.close();
        OutputDebugString(content.c_str());
    } else {
        // User cancelled the dialog
        content = "";
    }
    // Restore the current working directory
    SetCurrentDirectory(currentDir);

    return content;
}