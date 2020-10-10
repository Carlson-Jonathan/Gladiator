#include<iostream>
#include <memory>
#include <vector>
using namespace std;

class MyClass {
public:

	MyClass(int x) {
       this->x = x;
	}

	~MyClass(){cout << "Destroyed!" << endl;}
	void stuff() {
		cout << "This is working" << endl;
	}

	int x;

};

int main() {


	vector<shared_ptr<MyClass>> thisList1;
	vector<shared_ptr<MyClass>> thisList2;
	for(int i = 1; i < 11; i++) {
		shared_ptr pObject make_shared<MyClass>(i * 2);
		thisList1.push_back(pObject);
	}

	// This will cause items from both lists to be destroyed on delete
	thisList2 = thisList1; 

	// This will preserve items in list2, even when delete is called on list1.
	// for(int i = 1; i < 11; i++) {  
	// 	pObject = new MyClass(i * 2);
	// 	thisList2.push_back(pObject);
	// }

	delete thisList1[4];
	// thisList1.erase(thisList1.begin() + 4);

	for(auto i : thisList1)
		cout << i->x << ", ";
	cout << endl;

	for(auto i : thisList2)
		cout << i->x << ", ";
	cout << endl;


	return 0;
}