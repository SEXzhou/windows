#include <windows.h>  
#include <iostream>  
  
bool IsRunningAsAdmin() {  
    HANDLE hToken;  
    TOKEN_ELEVATION Elevation;  
    DWORD cbTokenElevation = sizeof(TOKEN_ELEVATION);  
  
    // ��ȡ��ǰ���̵����ƾ��  
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken)) {  
        return false;  
    }  
  
    // ��ѯ���Ƶ�������Ϣ  
    if (!GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbTokenElevation)) {  
        CloseHandle(hToken);  
        return false;  
    }  
  
    // ��������Ƿ�������  
    if (Elevation.TokenIsElevated) {  
        CloseHandle(hToken);  
        return true;  
    } else {  
        CloseHandle(hToken);  
        return false;  
    }  
}  
  
int main() {  
    if (IsRunningAsAdmin()) {  
        std::cout << "�����Թ���ԱȨ�����С�" << std::endl;  
    } else {  
        std::cout << "�������Թ���ԱȨ�����еġ�" << std::endl;  
    }  
    
    system("pause");
    
    return 0;  
}
