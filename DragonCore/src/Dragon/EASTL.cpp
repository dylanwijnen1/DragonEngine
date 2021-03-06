// See: EASTL FAQ.html#Prob.16

#include <Dragon/Config.h>

#include <new>

void* operator new[] (size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	return ::new char[size];
}

void* operator new[] (size_t size, size_t alignment, size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{
	return ::new char[size];
}

#include <EASTL/string.h>

// EASTL also wants us to define this (see string.h line 197)
int Vsnprintf8(char* pDestination, size_t n, const char* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnprintf(pDestination, n, pFormat, arguments);
#else
	return vsnprintf(pDestination, n, pFormat, arguments);
#endif
}

int Vsnprintf16(char16_t* pDestination, size_t n, const char16_t* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnwprintf((wchar_t*)pDestination, n, (wchar_t*)pFormat, arguments);
#else
	char* d = new char[n + 1];
	int r = vsnprintf(d, n, convertstring<char16_t, char>(pFormat).c_str(), arguments);
	memcpy(pDestination, convertstring<char, char16_t>(d).c_str(), (n + 1) * sizeof(char16_t));
	delete[] d;
	return r;
#endif
}

int Vsnprintf32(char32_t* pDestination, size_t n, const char32_t* pFormat, va_list arguments)
{
	return 0;
}

#if defined(EA_WCHAR_UNIQUE) && EA_WCHAR_UNIQUE
int VsnprintfW(wchar_t* pDestination, size_t n, const wchar_t* pFormat, va_list arguments)
{
#ifdef _MSC_VER
	return _vsnwprintf_s(pDestination, n, n, pFormat, arguments);
#else
	char* d = new char[n + 1];
	int r = vsnprintf(d, n, convertstring<char16_t, char>(pFormat).c_str(), arguments);
	memcpy(pDestination, convertstring<char, char16_t>(d).c_str(), (n + 1) * sizeof(char16_t));
	delete[] d;
	return r;
#endif
}
#endif
