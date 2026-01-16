// Copyright (c) 2022 by Thermo Fisher Scientific
// All rights reserved. This file includes confidential and proprietary information of Thermo Fisher Scientific

#pragma once

#include <utility>
#include <testing/google_test.h>
#include <testing/stringify.h>

//-----------------------------------------------------------------------------------------------------------------------------------------
// This header file contains code and MACROs for unit testing
// compiletime checks of (member) functions and (member) function templates.
//
// The problem statement :
// When creating C++ code with SFINAE (or later concepts) you do it to 
// explicitly disable, by design, the compilation of some code constructs.
// 
// During maintenance of the code it is important that the disabled
// code constructs do not accidentally become compileable because
// this may have unintended consequences in the client code.
// 
// This is a video about that problem from C++ conference of 2022
// Testing compile time constructs within a runtime unit testing framework.
// https://www.youtube.com/watch?v=hMn_dCae00g&t=1130s
// 
// They propose a two step process (with external tooling), this header file provides
// a one time process.
// 
// Some key properties of this solution
// - When giving the compiler an option between two functions with signatures
//   (int,args_t...) and (double,args_t...) and then trying to compile
//   (1, args...) where the one is an integer it is forced to evaluate
//   all function templates starting with an int first.
// -  This means that we can create test functions that SFINAE out based on the deduced
//    return value of the function under test.
//	  The test function wraps the original function with the original arguments but puts a int argument
//    in front and then checks if it can deduce the return type.
// - In case that the original function returns a void, the test function will return a void_type struct
//	 to ensure that a test function always returns a full type if it isn't SFINAED out.
// - In case the test function with the int argument cannot be selected there will be a second test
//   function with a first argument that has a double type. The compiler can consider this one
//   since there is an implicit cast from int to double available.
//   if this test function is selected a no_type type will be returned from the test function.
// - Then tere is an overloaded can_compile function that returns false for no_type and true for anything else.
// 
// INSIGHTS
// - it is better to use SFINAE explicitly then checking with static_assert
// even if static_assert WILL give easier to read compiler warnings, with SFINAE the compiler 
// gets a chance to find another overload where static_assert will block that.
// - perfect forwarding in templates will preserve the "noexcept" property of lambdas where pass by value will not.
// (seems like a bug in MSVC since clang that runs during code editing will see the noexcept)
//

namespace compile_time_testing
{
template<typename type_t>
struct is_valid_type {};

// decltype(sizeof(is_valid_type<decltype(fn(args...))>) != 0ul) will evaluate to a bool when the fn(args...) evaluates
// to a compileable function (lambda).

template<typename fn_t, typename... args_t>
constexpr auto can_compile_helper(int, fn_t&& fn, args_t&&... args) -> decltype(sizeof(is_valid_type<decltype(fn(args...))>) != 0ul)
{
	return true;
}

template<typename fn_t, typename... args_t>
constexpr auto can_compile_helper(double, fn_t&&, args_t&&...)
{
	return false;
}

template<typename fn_t, typename... args_t>
constexpr bool can_compile(fn_t&& fn, args_t&&... args)
{
	return can_compile_helper(1, fn, args...);
}


template<typename type_t>
constexpr auto is_complete_type_helper(int) -> decltype(sizeof(type_t) != 0)
{
	return true;
}

template<typename type_t>
constexpr bool is_complete_type_helper(double)
{
	return false;
}

template<typename type_t>
constexpr bool is_complete_type()
{
	return is_complete_type_helper<type_t>(1);
}

template<typename type_t, typename... args_t>
constexpr bool is_constructible(args_t...)
{
	if constexpr(is_complete_type<type_t>())
	{
		return std::is_constructible_v<type_t, args_t...>;
	}
	return false;
}

} // namespace compile_time_testing

//-----------------------------------------------------------------------------------------------------------------------------------------
// Define MACROS to setup compile time test code
// TODO : get macros right for GCC/Clang (only tested msvc so far)

#define COMPILE_STRING_CAT2(a, b)	a##b
#define COMPILE_STRING_CAT(a, b)	COMPILE_STRING_CAT2(a, b)
#define COMPILE_LINE_VAR			COMPILE_STRING_CAT(can_compile_line_,__LINE__)				// create a unique boolean variable name (for use in a unit test file)
#define COMPILE_LINE_LAMBDA			COMPILE_STRING_CAT(can_compile_lambda_,__LINE__)		// create a unique generic lamabda function name  (for use in a unit test file)
#define EVAL_COMPILE_LINE_LAMBDA	COMPILE_STRING_CAT(eval_compile_lambda_,__LINE__)		// create a unique generic lamabda function name  (for use in a unit test file)
#define COMPILE_FORWARD_ARGS(expression) expression(std::forward<decltype(args)>(args)...)

//-----------------------------------------------------------------------------------------------------------------------------------------
// 1. First define a generic lambda that allows arguments to be forwarded to the function expression.
//		- such an expresion is the name of a function call or it is an temporary instance of a class with its function call
//		  e.g. functionname or myclass{}.functionname
// 2. the ::compile_time_testing::can_compile will
//		- evaluate if a call can be made to a function with starting parameter int and the lambda with passed arguments and then return true
//		- otherwise it will evaluate to a function with a double first parameter which will return false.

#define MUST_COMPILE(expression,...) \
	auto COMPILE_LINE_LAMBDA = [&](auto&&... args) -> decltype(COMPILE_FORWARD_ARGS(expression)) { return COMPILE_FORWARD_ARGS(expression); }; \
	static constexpr auto COMPILE_LINE_VAR = ::compile_time_testing::can_compile(COMPILE_LINE_LAMBDA, __VA_ARGS__); \
	static_assert(COMPILE_LINE_VAR, "'" STRINGIFY(expression) "' does not compile with given arguments even when it must."); \
	ASSERT_TRUE(COMPILE_LINE_VAR)

#define MUST_NOT_COMPILE(expression,...) \
	auto COMPILE_LINE_LAMBDA = [&](auto&&... args) -> decltype(COMPILE_FORWARD_ARGS(expression)) { return COMPILE_FORWARD_ARGS(expression); }; \
	static constexpr auto COMPILE_LINE_VAR = ::compile_time_testing::can_compile(COMPILE_LINE_LAMBDA, __VA_ARGS__); \
	static_assert(!COMPILE_LINE_VAR, "'" STRINGIFY(expression) "' compiles with given arguments even when it must not."); \
	ASSERT_FALSE(COMPILE_LINE_VAR)

#define COMPILE_ASSERT_TRUE(expression) \
	static constexpr auto COMPILE_LINE_LAMBDA = [&]{ return (expression); }; \
	static_assert(COMPILE_LINE_LAMBDA()); \
	ASSERT_TRUE(COMPILE_LINE_LAMBDA());

#define COMPILE_ASSERT_FALSE(expression) \
	static constexpr auto COMPILE_LINE_LAMBDA = [&]{ return (expression); }; \
	static_assert(!COMPILE_LINE_LAMBDA()); \
	ASSERT_FALSE(COMPILE_LINE_LAMBDA());

#define COMPILE_ASSERT_EQ(expression, value) \
	static constexpr auto COMPILE_LINE_LAMBDA = [&]{ return (expression); }; \
	static_assert(COMPILE_LINE_LAMBDA() == value); \
	ASSERT_EQ(COMPILE_LINE_LAMBDA(), value); 

#define COMPILE_ASSERT_NE(expression, value) \
	static constexpr auto COMPILE_LINE_LAMBDA = [&]{ return (expression); }; \
	static_assert(COMPILE_LINE_LAMBDA() != value); \
	ASSERT_NE(COMPILE_LINE_LAMBDA(), value); 
	
#define MUST_BE_CONSTRUCTIBLE(type,...) \
	static constexpr auto COMPILE_LINE_VAR = ::compile_time_testing::is_constructible<type>(__VA_ARGS__); \
	static_assert(COMPILE_LINE_VAR, "'" STRINGIFY(expression) "' is not constructible with given arguments even when it must."); \
	ASSERT_TRUE(COMPILE_LINE_VAR)

#define MUST_NOT_BE_CONSTRUCTIBLE(type,...) \
	static constexpr auto COMPILE_LINE_VAR = ::compile_time_testing::is_constructible<type>(__VA_ARGS__); \
	static_assert(!COMPILE_LINE_VAR, "'" STRINGIFY(expression) "' is constructible with given arguments even when it must not be."); \
	ASSERT_FALSE(COMPILE_LINE_VAR)

#define MUST_BE_COMPLETE(type) \
	static constexpr auto COMPILE_LINE_VAR = ::compile_time_testing::is_complete_type<type>(); \
	static_assert(COMPILE_LINE_VAR, "'" STRINGIFY(type) "' is not a complete type even when it must be"); \
	ASSERT_TRUE(COMPILE_LINE_VAR)

#define MUST_NOT_BE_COMPLETE(type) \
	static constexpr auto COMPILE_LINE_VAR = ::compile_time_testing::is_complete_type<type>(); \
	static_assert(!COMPILE_LINE_VAR, "'" STRINGIFY(type) "' is a complete type even when it must not be"); \
	ASSERT_FALSE(COMPILE_LINE_VAR)


#define MUST_BE_COPYABLE(type) \
	static constexpr bool COMPILE_LINE_VAR = std::is_copy_constructible_v<type> && std::is_copy_assignable_v<type>; \
	static_assert(COMPILE_LINE_VAR, "'" STRINGIFY(type) "' type is not copyable even when it should be"); \
	ASSERT_TRUE(COMPILE_LINE_VAR)

#define MUST_NOT_BE_COPYABLE(type) \
	static constexpr bool COMPILE_LINE_VAR = std::is_copy_constructible_v<type> && std::is_copy_assignable_v<type>; \
	static_assert(!COMPILE_LINE_VAR, "'" STRINGIFY(type) "' type is copyable even when it should be"); \
	ASSERT_FALSE(COMPILE_LINE_VAR)

#define MUST_BE_MOVABLE(type) \
	static constexpr bool COMPILE_LINE_VAR = std::is_move_constructible_v<type> && std::is_move_assignable_v<type>; \
	static_assert(COMPILE_LINE_VAR, "'" STRINGIFY(type) "' type is not moveable even when it should be"); \
	ASSERT_TRUE(COMPILE_LINE_VAR)

#define MUST_NOT_BE_MOVABLE(type) \
	static constexpr bool COMPILE_LINE_VAR = std::is_move_constructible_v<type> && std::is_move_assignable_v<type>; \
	static_assert(!COMPILE_LINE_VAR, "'" STRINGIFY(type) "' type is moveable even when it should be"); \
	ASSERT_FALSE(COMPILE_LINE_VAR)








