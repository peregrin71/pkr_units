//
// Header file that disables some code analysis on google include files 
//
//TICS -POR#021 The use of conditional compilation is only allowed in specific files to hide or implement platform dependent code. This file is portable by design
//TICS -POR#018 Level: 6, Category: Portability, Synopsis: Avoid the use of #pragma directives
//TICS -POR#037 Rule: POR#037, Level: 1, Category : Portability, Synopsis : Avoid the use of #pragma warning directive.
//

#pragma once

#include <stdexcept>
#include <thread>
#include <type_traits>

#ifdef _WIN32
	#include <codeanalysis/warnings.h>
	#pragma comment(lib,"gtest.lib")
#endif 

#pragma warning(push)
#pragma warning(disable:4996 6326 26451 26812 26451 26954) 
#pragma warning(disable:ALL_CODE_ANALYSIS_WARNINGS)
#define GTEST_LANG_CXX11 1
#include <gtest/gtest.h>
#pragma warning(pop)

namespace testing
{

template<typename E>
void test_throw_message(const std::string& message)
{
	try
	{
		static_assert(std::is_base_of_v<std::exception, E>, "E must be derived from std::exception");
		throw E(message);
	}
	catch (const E& e)
	{
		EXPECT_STREQ(message.c_str(), e.what());
	}
}

template<typename Fn>
void test_in_thread(Fn fn)
{
	std::thread t([&] { fn(); });
	t.join();
}

}








