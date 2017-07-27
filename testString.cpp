#include <algorithm>
#include <utility>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "testString.h"

using std::cout;
using std::endl;

testString::testString() :
		size(0), capacity(1), p_str(new char[1]) {}

testString::testString(const testString& str) : 
		size(str.size), capacity(2 * str.size + 1)
{
	try
	{
		p_str = new char[capacity];
	} 

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in testString constructor"
			<< endl;
		throw;
	}

	std::copy(str.p_str, str.p_str + size, p_str);
}

testString::testString(const testString& str, size_t pos, size_t len) :
	capacity(str.capacity)
{
	if (pos > str.size)
		throw std::out_of_range("'pos' is out of range in testString constructor");

	if ((len > str.size) || ((pos + len) > str.size))
		len = str.size - pos;

	size = len;

	try
	{
			p_str = new char[capacity];
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in testString constructor"
			<< endl;
		throw;
	}

	std::copy(str.p_str + pos, str.p_str + pos + len, p_str);
}

testString::testString(size_t n, char c) :
	size(n), capacity(2 * n + 1)
{
	try
	{
			p_str = new char[capacity];
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in testString constructor"
			<< endl;
		throw;
	}

	for (auto i = 0; i < n; ++i)
		p_str[i] = c;
}

testString::testString(testString&& str) :
	testString()
{
	swap(str);
}

testString::testString(const char* s) : 
	size(strlen(s)), capacity(2 * strlen(s) + 1)
{
	try
	{
		p_str = new char[capacity];
	}
	
	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in testString constructor"
			<< endl;
		throw;
	}

	std::copy(s, s + size, p_str);
}

testString::testString(const char* s, size_t n) :
	size(n), capacity(2 * n + 1)
{
	try
	{
			p_str = new char[capacity];
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in testString constructor"
			<< endl;
		throw;
	}

	std::copy(s, s + n, p_str);
}

testString::~testString()
{
	if (p_str)
		delete[] p_str;
}

testString& testString::operator = (testString str)
{
	swap(str);

	return *this;
}

testString& testString::operator = (const char* s)
{
	try
	{
		testString temp(s);
		swap(temp);
	}

	catch(std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during testString 'operator = ' execution"
			<< endl;
		throw;
	}

	return *this;
}

testString& testString::operator = (char c)
{
	char temp_str[2];
	temp_str[0] = c;
	temp_str[1] = '\0';

	try
	{
		testString temp(temp_str);
		swap(temp);
	}
	
	catch(std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during testString 'operator = ' execution"
			<< endl;
		throw;
	}

	return *this;
}

testString& testString::operator = (testString&& str)
{	
	swap(str);

	return *this;
}

size_t testString::get_size() const
{
	return size;
}


size_t testString::get_capacity() const
{
	return capacity;
}

void testString::resize(size_t n)
{
	resize(n, '\0');

	return;
}

void testString::resize(size_t n, char c)
{
	if (n > capacity)
	{
		try
		{
			reserve(n);
		}

		catch (std::bad_alloc& ex)
		{
			cout << endl
				<< "Bad allocation during 'testString.resize()' execution"
				<< endl;
			throw;
		}

		for (auto i = size; i < n; ++i)
			p_str[i] = c;

		size = n;
		return;
	}

	if (n == size)
		return;

	if (n > size)
	{
		for (auto i = size; i < n; ++i)
			p_str[i] = c;

		size = n;
		return;
	}

	for (auto i = n; i < size; ++i)
		p_str[i] = '\0';

	size = n;

	return;
}

void testString::reserve(size_t n)
{
	if (n > capacity)
	{
		try
		{
			char* temp = new char[n];

			std::copy(p_str, p_str + size, temp);

			testString temp_str(temp);

			temp_str.p_str = temp;
		
			temp_str.capacity = n;
			swap(temp_str);
		}
	
		catch (std::bad_alloc& ex)
		{
			cout << endl
				<< "Bad allocation during 'testString.reserve()' execution"
				<< endl;
			throw;
		}


	}

	return;
}

void testString::clear()
{
	size =  0;

	return;
}

bool testString::empty() const
{
	return size ? false : true;
}

char& testString::operator [] (size_t pos)
{
	return p_str[pos];
}

const char& testString::operator [] (size_t pos) const
{
	return p_str[pos];
}

char& testString::back()
{
	return p_str[size - 1];
}

const char& testString::back() const
{
	return p_str[size - 1];
}

char& testString::front()
{
	return p_str[0];
}

const char& testString::front() const
{
	return p_str[0];
}

testString& testString::operator += (const testString& str)
{
	testString temp;

	while ((size + str.size) >= capacity)
		capacity = 2 * capacity + 1;

	try
	{
		temp.reserve(capacity);
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during testString 'operator +=' execution"
			<< endl;
		throw;
	}

	std::copy(p_str, p_str + size, temp.p_str);
	std::copy(str.p_str, str.p_str + str.size, temp.p_str + size);
	temp.size = size + str.size;

	swap(temp);

	return *this;
	
}

testString& testString::operator += (const char* s)
{
	try
	{
		testString temp(s);
	
		*this += temp;
	}
	
	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during testString 'operator +=' execution"
			<< endl;
		throw;
	}


	return *this;
}

testString& testString::operator += (char c)
{
	char s[2];
	s[0] = c;
	s[1] = '\0';

	try
	{
		*this += s;
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during testString 'operator +=' execution"
			<< endl;
		throw;
	}


	return *this;
}

void testString::push_back(char c)
{
	try
	{
		*this += c;
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during testString 'operator +=' execution"
			<< endl;
		throw;
	}


	return;
}

testString& testString::insert(size_t pos, const testString& str)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.insert()'");

	try
	{
		insert(pos, str, 0, str.size);
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in 'testString.insert()'"
			<< endl;
		throw;
	}

	return *this;
}

testString& testString::insert(size_t pos, const testString& str, size_t subpos, size_t sublen)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.insert()'");

	if (subpos > str.size)
		throw std::out_of_range("'subpos' is out of range in 'testString.insert()'");

	if (((subpos + sublen) > str.size) || (sublen > str.size) > str.size)
		sublen = str.size - subpos;

	try
	{
		testString temp;

		while ((size + (sublen - subpos)) >= capacity)
			capacity = 2 * capacity + 1;
	
		temp.reserve(capacity);
		temp.size = size + sublen;
	
		std::copy(p_str, p_str + pos, temp.p_str);
		std::copy(str.p_str + subpos, str.p_str + subpos + sublen, temp.p_str + pos);
		std::copy(p_str + pos, p_str + size, temp.p_str + pos + sublen);

		swap(temp);
	}
	
	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in 'testString.insert()'"
			<< endl;
		throw;
	}


	return *this;
}

testString& testString::insert(size_t pos, const char* s)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.insert()'");

	try
	{
		testString temp(s);

		insert(pos, temp);
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in 'testString.insert()'"
			<< endl;
		throw;
	}

	return *this;
}

testString& testString::insert(size_t pos, const char* s, size_t n)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.insert()'");
	
	try
	{
		testString temp(s);

		insert(pos, temp, 0, n);
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in 'testString.insert()'"
			<< endl;
		throw;

	}

	return *this;
}

testString& testString::insert(size_t pos, size_t n, char c)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.insert()'");

	char s[n + 1];
	for (auto i = 0; i < n; ++i)
		s[i] = c;

	s[n] = '\0';

	try
	{
		testString temp(s);

		insert(pos, temp);
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation in 'testString.insert()'"
			<< endl;
		throw;

	}


	return *this;
}

testString& testString::erase(size_t pos, size_t len)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.erase()'");

	if ((len || (pos + len)) > size)
		len = size - pos;

	std::copy(p_str + pos + len, p_str + size, p_str + pos);

	return *this;
}

testString& testString::replace(size_t pos, size_t len, const testString& str)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.replace()'");

	if ((len || (pos + len)) > size)
		len = size - pos;

	replace(pos, len, str, 0, str.size);

	return *this;
}

testString& testString::replace(size_t pos, size_t len, const testString& str, size_t subpos, size_t sublen)
{

	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.replace()'");

	if (subpos > str.size)
		throw std::out_of_range("'subpos' is out of range in 'testString.replace()'");

	if ((len || (pos + len)) > size)
		len = size - pos;

	if ((sublen || (subpos + sublen)) > str.size)
		sublen = str.size - subpos;

	testString temp;

	while ((size - len + sublen) >= capacity)
		capacity = 2 * capacity + 1;

	try
	{
		temp.reserve(capacity);
	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during 'testString.replace()' execution"
			<< endl;
		throw;

	}

	temp.size = size - len + sublen;

	std::copy(p_str, p_str + pos, temp.p_str);
	std::copy(str.p_str + subpos, str.p_str + subpos + sublen, temp.p_str + pos);
	std::copy(p_str + pos + len, p_str + size, temp.p_str + pos + sublen);

	swap(temp);

	return *this;
}

testString& testString::replace(size_t pos, size_t len, const char* s)
{

	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.replace()'");

	if ((len || (pos + len)) > size)
		len = size - pos;

	try
	{
		testString temp(s);

	
		replace(pos, len, temp);
	}
	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during 'testString.replace()' execution"
			<< endl;
		throw;

	}


	return *this;
}

testString& testString::replace(size_t pos, size_t len, const char* s, size_t n)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.replace()'");

	if ((len || (pos + len)) > size)
		len = size - pos;


	try
	{
		testString temp(s);
		replace(pos, len, temp, 0, n);

	}

	catch (std::bad_alloc& ex)
	{
		cout << endl
			<< "Bad allocation during 'testString.replace()' execution"
			<< endl;
		throw;

	}


	return *this;
}

testString& testString::replace(size_t pos, size_t len, size_t n, char c)
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.replace()'");

	if ((len || (pos + len)) > size)
		len = size - pos;

	char s[n + 1];
	for (auto i = 0; i < n; ++i)
		s[i] = c;

	s[n] = '\0';

	replace(pos, len, s);

	return *this;
}

void testString::swap(testString& str)
{
	std::swap(p_str, str.p_str);
	std::swap(size, str.size);
	std::swap(capacity, str.capacity);

	return;
}

void testString::pop_back()
{
	--size;

	return;
}

const char* testString::c_str() const
{
	p_str[size] = '\0';

	return p_str;
}

size_t testString::copy(char* s, size_t len, size_t pos) const
{
	if (pos > size)
		throw std::out_of_range("'pos' is out of range in 'testString.copy()'");

	if ((len || (pos + len)) > size)
		len = size - pos;

	std::copy(p_str + pos, p_str + pos + len, s);

	return len;
}
