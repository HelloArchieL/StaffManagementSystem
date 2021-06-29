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
	cout << "�w��ϥ�¾�u�޲z�t�ΡI" << endl;
	cout << "0.�h�X�޲z�{��" << endl;
	cout << "1.�W�[¾�u�H��" << endl;
	cout << "2.���¾�u�H��" << endl;
	cout << "3.�R����¾¾�u" << endl;
	cout << "4.�ק�¾�u�H��" << endl;
	cout << "5.�d��¾�u�H��" << endl;
	cout << "6.���ӽs���Ƨ�" << endl;
	cout << "7.�M�ũҦ�����" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem() {
	cout << "�w��U���ϥ�" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::AddEmp() {
	cout << "�п�J�s�W¾�u�ƶq: " << endl;

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

			cout << "�п�J�� " << i + 1 << " �ӷs¾�u�s��: " << endl;
			cin >> id;

			cout << "�п�J�� " << i + 1 << " �ӷs¾�u�m�W: " << endl;
			cin >> name;

			cout << "�п�ܲ� " << i + 1 << " �ӷs¾�u¾��: " << endl;
			cout << "1. ���u" << endl;
			cout << "2. �g�z" << endl;
			cout << "3. �`��" << endl;
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
		
		cout << "���\�s�W " << addNum << " �W�s¾�u!" << endl;
		this->save();
	}
	else {
		cout << "��J���~!" << endl;
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
		cout << "��󤣦s�b�ΰO������!" << endl;
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
		cout << "��󤣦s�b�ΰO������!" << endl;
	}
	else {
		cout << "�п�J�n�R��¾�u���s��: " << endl;
		int id = 0;
		cin >> id;

		int idx = this->IsExist(id);

		if (idx != -1) {
			for (int i = idx; i < this->m_EmpNum-1; i++) {
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--;
			this->save();
			cout << "�R�����\!" << endl;
		}
		else {
			cout << "�R�����ѡA�d�L��¾�u!" << endl;
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
		cout << "��󤣦s�b�ΰO������!" << endl;
	}
	else {
		cout << "�п�J�n�ק�¾�u���s��: " << endl;
		int id = 0;
		cin >> id;

		int ret = this->IsExist(id);

		if (ret != -1) {
			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int newDid = 0;

			cout << "�п�J�s��¾�u�s��: " << endl;
			cin >> newId;

			cout << "�п�J�s��¾�u�m�W: " << endl;
			cin >> newName;

			cout << "�п�ܷs��¾�u¾��: " << endl;
			cout << "1. ���u" << endl;
			cout << "2. �g�z" << endl;
			cout << "3. �`��" << endl;
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
			cout << "�ק令�\!" << endl;
		}
		else {
			cout << "�ק異�ѡA�d�L��¾�u!" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "��󤣦s�b�ΰO������!" << endl;
	}
	else {
		cout << "�п�J�d�䪺�覡�G" << endl;
		cout << "1.��¾�u�s���d��" << endl;
		cout << "2.���m�W�d��" << endl;

		int select = 0;
		cin >> select;


		if (select == 1)
		{
			int id;
			cout << "�п�J�d�䪺¾�u�s���G" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				cout << "�d�䦨�\�I��¾�u�H���p�U�G" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "�d�䥢�ѡA�d�L���H!" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "�п�J�d�䪺�m�W�G" << endl;
			cin >> name;

			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "�d�䦨�\,¾�u�s�����G"
						<< m_EmpArray[i]->m_Id
						<< "�����H���p�U�G" << endl;

					flag = true;

					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "�d�䥢�ѡA�d�L���H" << endl;
			}
		}
		else
		{
			cout << "��J�ﶵ���~" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty)
	{
		cout << "��󤣦s�b�ΰO�����šI" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "�п�ܱƧǤ覡�G " << endl;
		cout << "1�B��¾�u���i��ɧ�" << endl;
		cout << "2�B��¾�u���i�歰��" << endl;

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

		cout << "�ƧǦ��\,�Ƨǫᵲ�G���G" << endl;
		this->save();
		this->Show_Emp();
	}
}

void WorkerManager::Clean_File() {
	cout << "�T�{�M�šH" << endl;
	cout << "1.�T�{" << endl;
	cout << "2.��^" << endl;

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
		cout << "�M�Ŧ��\�I" << endl;
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