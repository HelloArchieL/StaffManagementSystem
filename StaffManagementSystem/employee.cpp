#include "employee.h"

Employee::Employee(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

void Employee::showInfo() {
	cout << "職工編號: " << this->m_Id
		<< "\t職工姓名: " << this->m_Name
		<< "\t職稱: " << this->getDeptName()
		<< "\t職責: 完成經理交代的任務" << endl;
}

string Employee::getDeptName() {
	return string("員工");
}