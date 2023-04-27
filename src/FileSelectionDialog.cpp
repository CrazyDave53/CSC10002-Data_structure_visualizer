#include "FileSelectionDialog.h"


FileDialog::FileDialog()
{

}

bool FileDialog::ShowOpenFileDialog(std::string& fileContent) {
    std::cout << "I wanna die \n";
    char cwd[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, cwd);

    TCHAR szFileName[MAX_PATH] = { 0 };

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    // ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = _T("txt");

    if (GetOpenFileName(&ofn) == TRUE) {
        // User selected a file
        // selectedFile = std::string(szFileName);
        std::ifstream file(ofn.lpstrFile);
        std::string line;
        std::getline(file, line);
        fileContent = line;

        SetCurrentDirectory(cwd);
        return true;
    }
    else {
        // User cancelled the dialog
        return false;
    }
}