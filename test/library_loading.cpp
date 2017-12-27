#include "dlibxx.hxx"

#include <gmock/gmock.h>
#include "mocks/dlfcn_mock.h"

using namespace testing;

class TestLoadLibrary : public Test
{
};

TEST_F(TestLoadLibrary, Foo)
{
	DlfcnMock dlfcn;
	EXPECT_CALL(dlfcn, dlopen(_,_)).WillRepeatedly(Return(nullptr));

	dlibxx::handle lib;
	lib.load("test");

	EXPECT_FALSE(lib.loaded());
}
