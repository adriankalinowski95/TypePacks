// TypePacks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <functional>
#include <string>
#include <tuple>
#include <stdexcept>
#include <optional>

#include "DefTypes.h"

using my_special_variant = templated_struct::builder<std::variant, def_types::my_special_type>::type;

class MyClass {
public:
    MyClass(int a, float b, std::string c) : 
        m_a{ a },
        m_b{ b },
        m_c{ c } {}

    MyClass() {}

private:
    int m_a;
    float m_b;
    std::string m_c;
};

template <typename T, typename ...Args>
std::shared_ptr<T> createObj(Args... args) {
	return std::make_shared<T>(args...);
}

template <typename T>
bool isValidate(const my_special_variant value) {
	return std::holds_alternative<T>(value);
}

template <typename... Args, std::size_t... Is>
bool isValidate(std::vector<my_special_variant> input, std::index_sequence<Is...>) {
	return (isValidate<Args>(input[Is]) && ...);
}

template <typename T>
std::optional<T> getValue(const my_special_variant value) {
	const auto ptrToValue = std::get_if<T>(&value);
	 if (!ptrToValue) {
	 	return std::nullopt;
	 }
	
	return *ptrToValue;
}

template <typename T, typename... Args, std::size_t... Is>
std::shared_ptr<T> createObjEx(std::vector<my_special_variant> input, std::index_sequence<Is...>) {
	return createObj<T>(*getValue<Args>(input[Is])...);
}

template <typename T, typename ...Args>
std::shared_ptr<T> createObjectEx(std::vector<my_special_variant> input) {
	constexpr auto argsCount = sizeof...(Args);
	constexpr auto indexSequence = std::index_sequence_for<Args...>{};
	if (!isValidate<Args...>(input, indexSequence)) {
		return nullptr;
	}

	return createObjEx<T, Args...>(input, indexSequence);
}

template <typename TupleT, std::size_t... Is>
void printTupleManual(const TupleT& tp, std::index_sequence<Is...>) {
	(printElem(std::get<Is>(tp)), ...);
}

/*
template <typename TupleT, std::size_t... Is>
void printTupleManual(const TupleT& tp, std::index_sequence<Is...>) {
	(printElem(std::get<Is>(tp)), ...);
}
*/

int main() {
	my_special_variant templatedVariant{ 123 };
	if (!std::holds_alternative<int>(templatedVariant)) {
		return 0;
	}

	const auto valueInside = std::get_if<int>(&templatedVariant);
	if (!valueInside) {
		return 0;
	}

	std::cout << "Value inside a templated variant: " << std::to_string(*valueInside) << std::endl;


    std::vector<my_special_variant> args = { 1, 2.0f, "test" };
	
	auto object = createObj<MyClass>(1, 2.0f, std::string("test"));

	auto result = createObjectEx<MyClass, int, float, std::string>(args);

	// std::shared_ptr<MyClass> val( new MyClass{ 1, 2.0f, std::string("test")});

	return 1;
}

/*
return createObj<T>(getValue)

std::cout << "args count: " << argsCount << std::endl;
// tutaj powinno byc jaksi index seqneucen...
//if (!getValue<Args>() || ...) {
//	
//}

return nullptr;
*/