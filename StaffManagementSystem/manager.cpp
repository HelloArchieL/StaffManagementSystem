#include "manager.h"

Manager::Manager(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

void Manager::showInfo() {
	cout << "¾�u�s��: " << this->m_Id
		<< "\t¾�u�m�W: " << this->m_Name
		<< "\t¾��: " << this->getDeptName()
		<< "\t¾�d: ���������N������" << endl;
}

string Manager::getDeptName() {
	return string("�g�z");
}