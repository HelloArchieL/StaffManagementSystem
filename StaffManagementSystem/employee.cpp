#include "employee.h"

Employee::Employee(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

void Employee::showInfo() {
	cout << "¾�u�s��: " << this->m_Id
		<< "\t¾�u�m�W: " << this->m_Name
		<< "\t¾��: " << this->getDeptName()
		<< "\t¾�d: �����g�z��N������" << endl;
}

string Employee::getDeptName() {
	return string("���u");
}