#include <windows.h>  
#include <iostream>  
  
bool IsRunningAsAdmin() {  
    HANDLE hToken;  
    TOKEN_ELEVATION Elevation;  
    DWORD cbTokenElevation = sizeof(TOKEN_ELEVATION);  
  
    // 获取当前进程的令牌句柄  
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_READ, &hToken)) {  
        return false;  
    }  
  
    // 查询令牌的提升信息  
    if (!GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbTokenElevation)) {  
        CloseHandle(hToken);  
        return false;  
    }  
  
    // 检查令牌是否已提升  
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
        std::cout << "程序以管理员权限运行。" << std::endl;  
    } else {  
        std::cout << "程序不是以管理员权限运行的。" << std::endl;  
    }  
    
    system("pause");
    
    return 0;  
}
