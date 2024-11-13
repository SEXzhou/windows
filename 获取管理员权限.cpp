#include <iostream>  
#include <string>  
#include <windows.h>  
#include <shellapi.h>  
  
bool IsRunningAsAdmin() {  
    DWORD dwPrivilege = 0;  
    HANDLE hToken;  
    TOKEN_PRIVILEGES tkp;  
  
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &hToken))  
        return false;  
  
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);  
  
    tkp.PrivilegeCount = 1;  // ����һ��Ȩ��  
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
  
    // ��ȡ�ػ�Ȩ��  
    AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL);  
  
    if (GetLastError() != ERROR_SUCCESS)  
        return false;  
  
    if (!GetTokenInformation(hToken, TokenElevation, &dwPrivilege, sizeof(dwPrivilege), (PDWORD)NULL))  
        return false;  
  
    if (dwPrivilege)  
        return true;  
  
    return false;  
}  
  
bool RestartAsAdmin(const std::string& filePath) {  
    SHELLEXECUTEINFOA sei = { 0 };  
    sei.cbSize = sizeof(sei);  
    sei.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_INVOKEIDLIST | SEE_MASK_NOCLOSEPROCESS;  
    sei.hwnd = NULL;  
    sei.lpVerb = "runas"; // �������ԱȨ��  
    sei.lpFile = filePath.c_str();  
    sei.nShow = SW_SHOWNORMAL;  
  
    if (ShellExecuteExA(&sei) != TRUE) {  
        std::cerr << "�������ԱȨ��ʧ��" << std::endl;  
        return false;  
    }  
  
    // �ȴ��½��̽���  
    WaitForSingleObject(sei.hProcess, INFINITE);  
    CloseHandle(sei.hProcess);  
  
    return true;  
}  
  
int main() {  
    std::string filePath;  
    std::cout << "�������ļ�·��: ";  
    std::getline(std::cin, filePath);  
  
    if (!IsRunningAsAdmin()) {  
        if (RestartAsAdmin(filePath)) {  
            std::cout << "�����Թ���ԱȨ������������" << std::endl;  
            return 0; // ��ǰʵ���˳�  
        } else {  
            std::cerr << "�޷��Թ���ԱȨ��������������" << std::endl;  
            return 1; // ���ش������  
        }  
    } else {  
        // �����Ѿ��Թ���ԱȨ�����У�ִ����Ĵ���...  
        std::cout << "�����Թ���ԱȨ�����У�����ִ�в���..." << std::endl;  
        // ���������Ĵ�����ִ���ļ������  
    }  
    
    system("pause");
  
    return 0;  
}
