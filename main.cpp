#include <iostream>
#include "testString.h"

using std::cout;
using std::endl;

int main()
{
	try
	{
	testString str1("Two wrongs");

	cout << endl
		<< "str1 : "
		<< str1.c_str()
		<< endl;

	testString str2 (str1);

	str2 += " don't make a right.";

	cout << endl
		<< "str2 : "
		<< str2.c_str()
		<< endl;

	cout << endl
		<< "str2 is of size : "
		<< str2.get_size()
		<< " and capacity : "
		<< str2.get_capacity()
		<< endl;

	str2.resize(15);

	cout << endl
		<< "str2 : "
		<< str2.c_str()
		<< endl;

	testString str3(10, 'k');

	cout << endl
		<< "str3 : "
		<< str3.c_str()
		<< endl;

	str3.clear();

	cout << endl
		<< "str3 is ";

	if (str3.empty())
		cout << "empty"
			<< endl;
	else
		cout <<	"filled"
			<< endl;

	str3 = "abc";

	cout << endl
		<< "str3 is ";

	if (str3.empty())
		cout << "empty"
			<< endl;
	else
		cout <<	"filled"
			<< endl;


	cout << endl
		<< "str3 : "
		<< str3.c_str()
		<< endl;

	cout << endl
		<< "First symbol of str3 : "
		<< str3.front()
		<< endl
		<< "Last symbol of str3 : "
		<< str3.back()
		<< endl;

	str2.insert(10, str3, 1, 10);

	cout << endl
		<< "str2 : "
		<< str2.c_str()
		<< endl;	

	str2.insert(50, str3, 1, 10);

	cout << endl
		<< "str2 : "
		<< str2.c_str()
		<< endl;
	}

	catch (std::exception& ex)
	{
		cout << endl
			<< ex.what()
			<< endl;
		return 1;
	}

	catch (...)
	{
		cout << endl
			<< "Unknown error."
			<< endl;
		throw;
	}

	return 0;
}
