#include <iostream>  
#include <windows.h>  
#include <tlhelp32.h>  
#include <cstdlib> // For std::system  
  
bool EndProcessByPID(DWORD pid) {  
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);  
    if (hProcess == NULL) {  
        std::cerr << "�޷��򿪽���: " << pid << std::endl;  
        return false;  
    }  
  
    if (!TerminateProcess(hProcess, 0)) { // 0��ʾ�����˳���  
        std::cerr << "�޷���������: " << pid << std::endl;  
        CloseHandle(hProcess);  
        return false;  
    }  
  
    CloseHandle(hProcess);  
    std::cout << "���� " << pid << " �ѽ���" << std::endl;  
    return true;  
}  
  
int main() {  
    DWORD pid;  
    std::cout << "������Ҫ�����Ľ��̵�PID: ";  
    std::cin >> pid;  
  
    if (EndProcessByPID(pid)) {  
        // ���̳ɹ�����  
    } else {  
        // ���̽���ʧ��  
        return 1;  
    }  
  
  	system("pause");
  	
    return 0;  
}
