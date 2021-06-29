#include <iostream>
#include "workerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;

int main() {
	WorkerManager wm;
	int choice = 0;
	while (true) {
		wm.ShowMenu();
		cout << "�п�J�z�����:" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			wm.ExitSystem();
			break;
		case 1:
			wm.AddEmp();
			break;
		case 2:
			wm.Show_Emp();
			break;
		case 3:
			wm.Del_Emp();
			break;
		case 4:
			wm.Mod_Emp();
			break;
		case 5:
			wm.Find_Emp();
			break;
		case 6:
			wm.Sort_Emp();
			break;
		case 7:
			wm.Clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}
	

	system("pause");
	return 0;
}