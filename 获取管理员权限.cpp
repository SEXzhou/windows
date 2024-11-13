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
  
    tkp.PrivilegeCount = 1;  // 设置一个权限  
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;  
  
    // 获取关机权限  
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
    sei.lpVerb = "runas"; // 请求管理员权限  
    sei.lpFile = filePath.c_str();  
    sei.nShow = SW_SHOWNORMAL;  
  
    if (ShellExecuteExA(&sei) != TRUE) {  
        std::cerr << "请求管理员权限失败" << std::endl;  
        return false;  
    }  
  
    // 等待新进程结束  
    WaitForSingleObject(sei.hProcess, INFINITE);  
    CloseHandle(sei.hProcess);  
  
    return true;  
}  
  
int main() {  
    std::string filePath;  
    std::cout << "请输入文件路径: ";  
    std::getline(std::cin, filePath);  
  
    if (!IsRunningAsAdmin()) {  
        if (RestartAsAdmin(filePath)) {  
            std::cout << "程序将以管理员权限重新启动。" << std::endl;  
            return 0; // 当前实例退出  
        } else {  
            std::cerr << "无法以管理员权限重新启动程序。" << std::endl;  
            return 1; // 返回错误代码  
        }  
    } else {  
        // 程序已经以管理员权限运行，执行你的代码...  
        std::cout << "程序以管理员权限运行，正在执行操作..." << std::endl;  
        // 这里添加你的代码来执行文件或操作  
    }  
    
    system("pause");
  
    return 0;  
}
