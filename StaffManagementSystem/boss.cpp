#include "boss.h"

Boss::Boss(int id, string name, int did) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = did;
}

void Boss::showInfo() {
	cout << "¾�u�s��: " << this->m_Id
		<< "\t¾�u�m�W: " << this->m_Name
		<< "\t¾��: " << this->getDeptName()
		<< "\t¾�d: �޲z���q�Ҧ��ư�" << endl;
}

string Boss::getDeptName() {
	return string("�`��");
}