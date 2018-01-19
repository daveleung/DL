#include <iostream>
using namespace std;

template <typename T>
class HasFriend
{
private:
	T item;
	static int ct;
public:
	HasFriend(const T & i) : item(i) {ct++;}
	~HasFriend() {ct--;}
	friend void counts();
	friend void reports(HasFriend<T> &);
};

//each specialization has its own static data member
template <typename T>
int HasFriend<T>::ct = 0;

//non-template friend to all hasFriend<T> classes
void counts()
{
	cout << "int count: " << HasFriend<int>::ct << "; ";
	cout << "double count: " << HasFriend<double>::ct << endl;
}

//non-template friend to the HasFriend<int> class
void reports(HasFriend<int> & hf)
{
	cout << "HasFriend<int>: " << hf.item << endl;
}

void reports(HasFriend<double> & hf)
{
	cout << "HasFriend<double>: " << hf.item << endl;
}

int main()
{
	cout << "No objects declared: ";
	counts();
	HasFriend<int> hfil(10);
	cout << "After hfil declared: ";
	counts();
	HasFriend<double> hfil2(20);
	cout << "After hfil2 declared: ";
	counts();
	HasFriend<double> hfdb(10.5);
	cout << "After hfdb declared: ";
	counts();
	reports(hfil);
	reports(hfil2);
	reports(hfdb);

	return 0;
}
