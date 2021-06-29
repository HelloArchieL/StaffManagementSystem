#include "boss.h"

Boss::Boss(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

void Boss::showInfo() {
	cout << "職工編號: " << this->m_Id
		<< "\t職工姓名: " << this->m_Name
		<< "\t職稱: " << this->getDeptName()
		<< "\t職責: 管理公司所有事務" << endl;
}

string Boss::getDeptName() {
	return string("總裁");
}