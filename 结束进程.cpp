#include <iostream>  
#include <windows.h>  
#include <tlhelp32.h>  
#include <cstdlib> // For std::system  
  
bool EndProcessByPID(DWORD pid) {  
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);  
    if (hProcess == NULL) {  
        std::cerr << "无法打开进程: " << pid << std::endl;  
        return false;  
    }  
  
    if (!TerminateProcess(hProcess, 0)) { // 0表示正常退出码  
        std::cerr << "无法结束进程: " << pid << std::endl;  
        CloseHandle(hProcess);  
        return false;  
    }  
  
    CloseHandle(hProcess);  
    std::cout << "进程 " << pid << " 已结束" << std::endl;  
    return true;  
}  
  
int main() {  
    DWORD pid;  
    std::cout << "请输入要结束的进程的PID: ";  
    std::cin >> pid;  
  
    if (EndProcessByPID(pid)) {  
        // 进程成功结束  
    } else {  
        // 进程结束失败  
        return 1;  
    }  
  
  	system("pause");
  	
    return 0;  
}
