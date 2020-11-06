#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <variant>
#include <initializer_list>

namespace Ccd {
namespace Json {
	
enum class ValueType {
	Int = 0,
	Double,
	Bool,
	String,
	Object,
	Array,
	Null
};

class Value;

using Object = std::map<std::string,Value>;
using Array = std::vector<Value>;

class Value
{
	ValueType _type = ValueType::Null;
	std::variant<int, double, bool, std::string, Object, Array> m_value {};

public:
	Value();
	Value(const int value);
	Value(const double value);
	Value(const bool value);
	Value(const std::string& value);
	Value(const char* value);
	Value(const Array& array);
	Value(const Object& obj);
	Value(std::string&& value);
	Value(Array&& array);
	Value(Object&& obj);
	Value(std::nullptr_t np);
	Value(const std::initializer_list<Value> list);

	Value(const Value& other);
	Value(Value&& other);
	
	Value& operator=(const Value& other);
	Value& operator=(Value&& other);
	
	Value& operator[](const std::string& key);
	const Value& operator[](const std::string& key) const;
	Value& operator[](const int key);
	const Value& operator[](const int key) const;

	explicit operator double() const { return std::get<double>(m_value); }
	explicit operator int() const { return std::get<int>(m_value); }
	explicit operator bool() const { return std::get<bool>(m_value); }
	explicit operator std::string () const { return std::get<std::string>(m_value); }
	operator Object () const { return std::get<Object>(m_value); }
	operator Array () const { return std::get<Array>(m_value); }

	friend std::ostream& operator<<(std::ostream& os, const Value& val);
	
	ValueType type() const;
	
	int toInt() const;
	double toDouble() const;
	const std::string& toString() const;
	bool toBool() const;
	
	Array toArray() const;
	Object toObject() const;
};

}
}
