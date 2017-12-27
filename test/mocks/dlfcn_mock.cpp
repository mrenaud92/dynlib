#include "mocks/dlfcn_mock.h"

#include <functional>

namespace
{
std::function<void*(char const*, int)> _dlopen;
std::function<int(void*)> _dlclose;
std::function<void*(void*, char const*)> _dlsym;
std::function<char*(void)> _dlerror;
}

extern "C" {
void* dlopen(char const* filename, int flags)
{
	return _dlopen(filename, flags);
}

int dlclose(void* handle)
{
	return _dlclose(handle);
}

void* dlsym(void* handle, char const* symbol)
{
	return _dlsym(handle, symbol);
}

char* dlerror(void)
{
	return nullptr;
}


}

DlfcnMock::DlfcnMock()
{
	assert(!_dlopen);
	assert(!_dlclose);
	assert(!_dlsym);
	assert(!_dlerror);

	_dlopen = [this](char const* filename, int flags) {
		return dlopen(filename, flags);
	};

	_dlclose = [this](void* handle) {
		return dlclose(handle);
	};

	_dlsym = [this](void* handle, char const* symbol) {
		return dlsym(handle, symbol);
	};

	_dlerror = [this] { return _dlerror(); };
}

DlfcnMock::~DlfcnMock()
{
	_dlopen = {};
	_dlclose = {};
	_dlsym = {};
	_dlerror = {};
}
