#include "workerManager.h"


WorkerManager::WorkerManager() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	if (!ifs.is_open()) {
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	int num = this->get_EmpNum();
	this->m_EmpNum = num;

	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();
}

void WorkerManager::ShowMenu() {
	cout << "歡迎使用職工管理系統！" << endl;
	cout << "0.退出管理程序" << endl;
	cout << "1.增加職工信息" << endl;
	cout << "2.顯示職工信息" << endl;
	cout << "3.刪除離職職工" << endl;
	cout << "4.修改職工信息" << endl;
	cout << "5.查找職工信息" << endl;
	cout << "6.按照編號排序" << endl;
	cout << "7.清空所有文檔" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem() {
	cout << "歡迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddEmp() {
	cout << "請輸入新增職工數量: " << endl;

	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		int newSize = this->m_EmpNum + addNum;

		Worker** newSpace = new Worker * [newSize];

		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dSelect;

			cout << "請輸入第 " << i + 1 << " 個新職工編號: " << endl;
			cin >> id;

			cout << "請輸入第 " << i + 1 << " 個新職工姓名: " << endl;
			cin >> name;

			cout << "請選擇第 " << i + 1 << " 個新職工職稱: " << endl;
			cout << "1. 員工" << endl;
			cout << "2. 經理" << endl;
			cout << "3. 總裁" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			newSpace[this->m_EmpNum + i] = worker;
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = newSpace;
		this->m_EmpNum = newSize;
		this->m_FileIsEmpty = false;
		
		cout << "成功新增 " << addNum << " 名新職工!" << endl;
		this->save();
	}
	else {
		cout << "輸入錯誤!" << endl;
	}

	system("pause");
	system("cls");
}

void WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	ofs.close();
}

int WorkerManager::get_EmpNum() {

	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> did) {
		num++;
	}

	return num;
}

void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int did;

	int idx = 0;
	while (ifs >> id && ifs >> name && ifs >> did) {
		Worker* worker = NULL;

		if (did == 1) {
			worker = new Employee(id, name, did);
		}
		else if (did == 2) {
			worker = new Manager(id, name, did);
		}
		else {
			worker = new Boss(id, name, did);
		}
		this->m_EmpArray[idx++] = worker;
	}
	ifs.close();
}

void WorkerManager::Show_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或記錄為空!" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或記錄為空!" << endl;
	}
	else {
		cout << "請輸入要刪除職工的編號: " << endl;
		int id = 0;
		cin >> id;

		int idx = this->IsExist(id);

		if (idx != -1) {
			for (int i = idx; i < this->m_EmpNum-1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "刪除成功!" << endl;
		}
		else {
			cout << "刪除失敗，查無此職工!" << endl;
		}
	}
	system("pause");
	system("cls");
}

int WorkerManager::IsExist(int id) {
	int idx = -1;

	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			idx = i;
			break;
		}
	}

	return idx;
}

void WorkerManager::Mod_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或記錄為空!" << endl;
	}
	else {
		cout << "請輸入要修改職工的編號: " << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);

		if (ret != -1) {
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int newDid = 0;

			cout << "請輸入新的職工編號: " << endl;
			cin >> newId;

			cout << "請輸入新的職工姓名: " << endl;
			cin >> newName;

			cout << "請選擇新的職工職稱: " << endl;
			cout << "1. 員工" << endl;
			cout << "2. 經理" << endl;
			cout << "3. 總裁" << endl;
			cin >> newDid;

			Worker* worker = NULL;
			switch (newDid)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}

			this->m_EmpArray[ret] = worker;

			this->save();
			cout << "修改成功!" << endl;
		}
		else {
			cout << "修改失敗，查無此職工!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或記錄為空!" << endl;
	}
	else {
		cout << "請輸入查找的方式：" << endl;
		cout << "1.按職工編號查找" << endl;
		cout << "2.按姓名查找" << endl;

		int select = 0;
		cin >> select;


		if (select == 1)
		{
			int id;
			cout << "請輸入查找的職工編號：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "查找成功！該職工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查找失敗，查無此人!" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "請輸入查找的姓名：" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功,職工編號為："
						<< m_EmpArray[i]->m_Id
						<< "號的信息如下：" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "查找失敗，查無此人" << endl;
			}
		}
		else
		{
			cout << "輸入選項有誤" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或記錄為空！" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "請選擇排序方式： " << endl;
		cout << "1、按職工號進行升序" << endl;
		cout << "2、按職工號進行降序" << endl;

		int select = 0;
		cin >> select;


		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				Worker* temp = m_EmpArray[i];
				m_EmpArray[i] = m_EmpArray[minOrMax];
				m_EmpArray[minOrMax] = temp;
			}

		}

		cout << "排序成功,排序後結果為：" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File() {
	cout << "確認清空？" << endl;
	cout << "1.確認" << endl;
	cout << "2.返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_EmpNum = 0;
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}

	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager() {

	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}

}