#include <iostream>
using std::cout;
using std::endl;

//template prototypes
template <typename T> void counts();
template <typename T> void report(T &);

//template class
template <typename TT>
class HasFriendT
{
private:
	TT item;
	static int ct;
public:
	HasFriendT(const TT & i) : item(i) {ct++;}
	~HasFriendT() {ct--;}
	friend void counts<TT>();
	friend void report<>(HasFriendT<TT> &);
};

template <typename T>
int HasFriendT<T>::ct = 0;

template <typename T>
void counts()
{
	cout << "template size: " << sizeof(HasFriendT<T>) << "; ";
	cout << "template counts(): " << HasFriendT<T>::ct << endl;
}

template <typename T>
void report(T & hf)
{
	cout << hf.item << endl;
}

int main()
{
	counts<int>();
	HasFriendT<int> hfil(10);
	HasFriendT<double> hfil2(20);
	HasFriendT<double> hfdb(10.5);
	report(hfil);
	report(hfil2);
	report(hfdb);
	cout << "counts<int>() output:\n";
	counts<int>();
	cout << "counts<double>() output:\n";
	counts<double>();

	return 0;
}