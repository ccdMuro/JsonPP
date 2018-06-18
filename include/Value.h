#pragma once

#include <memory>
#include <string>
#include <vector>
#include <map>
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

	int _intValue = 0;
	double _dobValue = 0.0;
	bool _bolValue = false;
	std::string _strValue = {};
	
	Object _objValue = {};
	Array _aryValue = {};

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

	explicit operator double() const { return _dobValue; }
	explicit operator int() const { return _intValue; }
	explicit operator bool() const { return _bolValue; }
	explicit operator std::string () const { return _strValue; }
	operator Object () const { return _objValue; }
	operator Array () const { return _aryValue; }

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
