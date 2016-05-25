#include "Value.h"

#include <iostream>

using namespace std;

namespace Ccd {
namespace Json {

Value::Value() : _type ( ValueType::Null ) {}
	
Value::Value ( const int value ) : _type ( ValueType::Int ), _intValue ( value ) { }

Value::Value ( const double value ) : _type ( ValueType::Double ), _dobValue ( value ) {}

Value::Value ( const bool value ) : _type ( ValueType::Bool ), _bolValue ( value ) {}

Value::Value ( const std::string& value ) : _type ( ValueType::String ), _strValue ( value ) {}

Value::Value ( const char* value ) : _type ( ValueType::String ), _strValue ( value ) {}

Value::Value ( const Array& array ) : _type ( ValueType::Array ), _aryValue ( array ) {}

Value::Value ( const Object& obj ) : _type ( ValueType::Object ), _objValue ( obj ) {}

Value::Value ( std::string&& value ) : _type ( ValueType::String ), _strValue ( move(value) ) {}

Value::Value ( Array&& array ) : _type ( ValueType::Array ), _aryValue ( move(array) ) {}

Value::Value ( Object&& obj ) : _type ( ValueType::Object ), _objValue ( move(obj) ) {}

Value::Value ( std::nullptr_t np ) : _type ( ValueType::Null ) {}

Value::Value(const initializer_list<Value> list) : _type ( ValueType::Array ), _aryValue ( list ) {};

Value::Value ( const Value& other ) 
{
	_type = other._type;
	switch ( other._type ) {
		case ValueType::Int:
			_intValue = other._intValue;
			break;
		case ValueType::Double:
			_dobValue = other._dobValue;
			break;
		case ValueType::Bool:
			_bolValue = other._bolValue;
			break;
		case ValueType::String:
			_strValue = other._strValue;
			break;
		case ValueType::Object:
			_objValue = other._objValue;
			break;
		case ValueType::Array:
			_aryValue = other._aryValue;
			break;
		case ValueType::Null:
		default:
			break;
	}
}

Value::Value ( Value&& other ) 
{
	_type = other._type;
	switch ( other._type ) {
		case ValueType::Int:
			_intValue = other._intValue;
			break;
		case ValueType::Double:
			_dobValue = other._dobValue;
			break;
		case ValueType::Bool:
			_bolValue = other._bolValue;
			break;
		case ValueType::String:
			_strValue = move(other._strValue);
			break;
		case ValueType::Object:
			_objValue = move(other._objValue);
			break;
		case ValueType::Array:
			_aryValue = move(other._aryValue);
			break;
		case ValueType::Null:
		default:
			break;
	}
}

Value& Value::operator = (const Value& other )
{
	_type = other._type;
	switch ( other._type ) {
		case ValueType::Int:
			_intValue = other._intValue;
			break;
		case ValueType::Double:
			_dobValue = other._dobValue;
			break;
		case ValueType::Bool:
			_bolValue = other._bolValue;
			break;
		case ValueType::String:
			_strValue = other._strValue;
			break;
		case ValueType::Object:
			_objValue = other._objValue;
			break;
		case ValueType::Array:
			_aryValue = other._aryValue;
			break;
		case ValueType::Null:
		default:
			break;
	}
	
	return *this;
}

Value& Value::operator = ( Value&& other )
{
	_type = other._type;
	switch ( other._type ) {
		case ValueType::Int:
			_intValue = move(other._intValue);
			break;
		case ValueType::Double:
			_dobValue = move(other._dobValue);
			break;
		case ValueType::Bool:
			_bolValue = move(other._bolValue);
			break;
		case ValueType::String:
			_strValue = move(other._strValue);
			break;
		case ValueType::Object:
			_objValue = move(other._objValue);
			break;
		case ValueType::Array:
			_aryValue = move(other._aryValue);
			break;
		case ValueType::Null:
		default:
			break;
	}
	
	return *this;
}

Value& Value::operator[](const std::string& key)
{
	if ( _type == ValueType::Null ){
		_type = ValueType::Object;
	}
	
	if ( _type != ValueType::Object )
		throw std::string ("Item is no Object");
		
	
	return _objValue[key];
}

Value& Value::operator[](const int key)
{
	if ( _type != ValueType::Array )
		throw std::string ("Item is no Array");
	return _aryValue[key];
}


ValueType Value::type()
{
	return _type;
}

int Value::toInt()
{
	return _intValue;
}

double Value::toDouble()
{
	return _dobValue;
}

std::string& Value::toString()
{
	return _strValue;
}

bool Value::toBool()
{
	return _bolValue;
}

Array Value::toArray()
{
	return _aryValue;
}

Object Value::toObject()
{
	return _objValue;
}

static unsigned int indentLvl = 0;

inline static void indent(std::ostream& os)
{
	for ( auto indentIdx = 0u ; indentIdx < indentLvl; indentIdx++ ) {
			os << "\t";
	}
}

std::ostream& operator<< ( std::ostream& os, const Object& obj )
{
	os << "{" << std::endl;
	indentLvl++;
	
	for ( auto item = obj.begin() ; item != obj.end(); ) {
		indent(os);
		os << "\"" + item->first + "\":" << item->second;
		if ( ++item != obj.end() )
			os << "," << std::endl;
	}
	os << std::endl;
	
	indentLvl--;
	indent(os);
	os << "}";

	return os;
}

std::ostream & operator<< ( std::ostream & os, const Array& array )
{
	os << "[";
	for ( auto item = array.begin() ; item != array.end(); ) {
		os << *item;
		if ( ++item != array.end() )
			os << ", ";
	}
	os << "]";

	return os;
}

std::ostream & operator<< ( std::ostream & os, const Value& val )
{
	switch ( val._type ) {
		case ValueType::Int:
			os << val._intValue;
			break;
		case ValueType::Double:
			os << val._dobValue;
			break;
		case ValueType::Bool:
			os << ( val._bolValue?"true":"false" );
			break;
		case ValueType::String:
			os << "\"" + val._strValue + "\"";
			break;
		case ValueType::Object:
			os << val._objValue;
			break;
		case ValueType::Array:
			os << val._aryValue;
			break;
		case ValueType::Null:
			os << "null";
			break;
		default:
			break;
	}
	return os;
}

}
}
