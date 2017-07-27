#include <cstring>

class testString
{
private:
	char* p_str;
	size_t size;
	size_t capacity;
public:
	testString();
	testString(const testString& str);	
	testString(const testString& str, size_t pos, size_t len); 
	testString(const char* s);
	testString(const char* s, size_t n); 
	testString(size_t n, char c);
	testString(testString&& str);

	~testString();

	testString& operator = (testString str);
	testString& operator = (const char* s);
	testString& operator = (char c);
	testString& operator = (testString&& str);


	size_t get_size() const;

	size_t get_capacity() const;

	void resize(size_t n);
	void resize(size_t n, char c);

	void reserve(size_t n = 0);

	void clear();

	bool empty() const;

	char& operator [] (size_t pos);
	const char& operator [] (size_t pos) const;

	char& back();
	const char& back() const;

	char& front();
	const char& front() const;

	testString& operator += (const testString& str);
	testString& operator += (const char* s);
	testString& operator += (char c);

	void push_back(char c);

	testString& insert(size_t pos, const testString& str);
	testString& insert(size_t pos, const testString& str, size_t subpos, size_t sublen);
	testString& insert(size_t pos, const char* s);
	testString& insert(size_t pos, const char* s, size_t n);
	testString& insert(size_t pos, size_t n, char c);

	testString& erase (size_t pos, size_t len);

	testString& replace(size_t pos, size_t len, const testString& str);
	testString& replace(size_t pos, size_t len, const testString& str, size_t subpos, size_t sublen);
	testString& replace(size_t pos, size_t len, const char* s);
	testString& replace(size_t pos, size_t len, const char* s, size_t n);
	testString& replace(size_t pos, size_t len, size_t n, char c);

	void swap(testString& str);

	void pop_back();

	const char* c_str() const;

	size_t copy(char* s, size_t len, size_t pos = 0) const;
};
