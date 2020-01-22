#include <memory>
#include <iostream>
#include <vector>
using namespace std;
 

//�̱��� : ���� Ŭ��������, �� �ϳ��� �ν��Ͻ��� ���� Ŭ����
//������ ������ �ϳ�.
class singleTonEX {

//�̱��� ���� ����
private:
	//�̱����� ���� �ϳ��� �ν��Ͻ��� ������ ������,
	//������ �Ҹ����� ���������ڸ� private�� �д�.
	singleTonEX() {};
	~singleTonEX() {};

public:
	//�̱����� �Ǳ����� �ݵ�� �ʿ��� �Լ�
	//getter�Լ�, �̱��� �ν��Ͻ��� �����´�.
	static singleTonEX* getSingle() {
		if (singleTonInst == nullptr)
			singleTonInst = new singleTonEX;
		return singleTonInst; 
	}
	//�̱��� �ı� �Լ�, �Ҹ��ڿ��� �ڵ����� �ҷ����� �ʱ� ������
	//�̱����� ����ϰ� ���Ŀ��� �� �������� �޸� ������ ����� �Ѵ�.
	static void destroy() {
		if (singleTonInst != nullptr)
			delete singleTonInst;
	}

private:
	//�̱��� �ν��Ͻ��� ���ο� ����ƽ���� ���� �ȴ�.
	static singleTonEX* singleTonInst;



//���� ���� ����
public:

	//
	// ���ϴ� �Լ��� �߰��ϼ���!
	//


private:
	//
	//���ϴ� �ڷ���� �߰��ϼ���!!

};

//����ƽ ��������� �ݵ�� � ���� ���ϰ� �־�� �Ѵ�.
//���� �ƹ��� �ǹ̾��� nullptr�� �־��ش�.
singleTonEX* singleTonEX::singleTonInst = nullptr;


class foo {

private:
	foo() {

	}
	~foo() {
		cout << "destruct" << endl;
	}


public:
	void something() {
		cout << "�Ǥ�" << endl;
	}

public:
	static foo* inst;

	static foo* getSingle() {
		if (inst == nullptr)
			inst = new foo;
		return inst;
	}

	static void destroy() {
		delete inst;
	}
	

public:
	void add(int a) {
		v.push_back(a);
	}
	
	void show() {
		for (int i = 0; i < v.size(); ++i)
			cout << v[i] << endl;
	}
	void deleteVectorInt(int a) {
		for (auto it = v.begin(); it != v.end(); )
		{
			if (*it == a) 
			{
				it = v.erase(it);
			}
			else ++it;
		}
	}


public:
	vector<int>& getVector() 
	{
		return v;
	}


	int a;
	int b;
	vector<int> v;
};

foo* foo::inst = nullptr;

#define FOOMANAGER foo::getSingle()

class goo {

public:
	goo() {
		cout << "goo's constructor" << endl;
	}
	~goo() {
		cout << "goo's destructor" << endl;
	}

public:

	void something() 
	{
		vector<int>& gooVector = FOOMANAGER->getVector();

		for (int i = 0; i < gooVector.size(); ++i) 
		{
			cout << gooVector[i] << endl;
		}

		for (auto it = gooVector.begin(); it != gooVector.end(); ) {
			if (*it == 4) {
				it = gooVector.erase(it);
			}
			else ++it;
		}

		//FOOMANAGER->deleteVectorInt(4);

		for (int i = 0; i < gooVector.size(); ++i) {
			cout << gooVector[i] << endl;
		}

	}


	int a;
	int b;

};


class zoo {

public:
	zoo() {
		cout << "goo's constructor" << endl;
	}
	~zoo() {
		cout << "goo's destructor" << endl;
	}

public:

	void something() {
		vector<int> v = FOOMANAGER->getVector();
	}

	int a;
	int b;

};


int main() {

	FOOMANAGER->add(3);
	FOOMANAGER->add(4);
	FOOMANAGER->add(5);
	FOOMANAGER->add(6);
	FOOMANAGER->add(7);
	FOOMANAGER->show();

	goo g;
	g.something();

	FOOMANAGER->show();
}