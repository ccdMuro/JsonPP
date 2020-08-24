#include "Value.h"

#include <iostream>

using namespace std;

namespace Ccd
{
namespace Json
{

Value::Value() : _type ( ValueType::Null ) {}

Value::Value ( const int value ) : _type ( ValueType::Int ), m_value ( value ) { }

Value::Value ( const double value ) : _type ( ValueType::Double ), m_value ( value ) {}

Value::Value ( const bool value ) : _type ( ValueType::Bool ), m_value ( value ) {}

Value::Value ( const std::string& value ) : _type ( ValueType::String ), m_value ( value ) {}

Value::Value ( const char* value ) : _type ( ValueType::String ), m_value {std::move(std::string{value})} {}

Value::Value ( const Array& array ) : _type ( ValueType::Array ), m_value ( array ) {}

Value::Value ( const Object& obj ) : _type ( ValueType::Object ), m_value ( obj ) {}

Value::Value ( std::string&& value ) : _type ( ValueType::String ), m_value ( move ( value ) ) {}

Value::Value ( Array&& array ) : _type ( ValueType::Array ), m_value ( move ( array ) ) {}

Value::Value ( Object&& obj ) : _type ( ValueType::Object ), m_value ( move ( obj ) ) {}

Value::Value ( std::nullptr_t ) : _type ( ValueType::Null ) {}

Value::Value ( const initializer_list<Value> list ) : _type ( ValueType::Array ), m_value ( list ) {}

Value::Value ( const Value& other )
{
	_type = other._type;
	switch ( other._type ) {
	case ValueType::Int:
		m_value = other.m_value;
		break;
	case ValueType::Double:
		m_value = other.m_value;
		break;
	case ValueType::Bool:
		m_value = other.m_value;
		break;
	case ValueType::String:
		m_value = other.m_value;
		break;
	case ValueType::Object:
		m_value = other.m_value;
		break;
	case ValueType::Array:
		m_value = other.m_value;
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
		m_value = other.m_value;
		break;
	case ValueType::Double:
		m_value = other.m_value;
		break;
	case ValueType::Bool:
		m_value = other.m_value;
		break;
	case ValueType::String:
		m_value = move ( other.m_value );
		break;
	case ValueType::Object:
		m_value = move ( other.m_value );
		break;
	case ValueType::Array:
		m_value = move ( other.m_value );
		break;
	case ValueType::Null:
	default:
		break;
	}
}

Value& Value::operator = ( const Value& other )
{
	_type = other._type;
	switch ( other._type ) {
	case ValueType::Int:
		m_value = other.m_value;
		break;
	case ValueType::Double:
		m_value = other.m_value;
		break;
	case ValueType::Bool:
		m_value = other.m_value;
		break;
	case ValueType::String:
		m_value = other.m_value;
		break;
	case ValueType::Object:
		m_value = other.m_value;
		break;
	case ValueType::Array:
		m_value = other.m_value;
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
		m_value = move ( other.m_value );
		break;
	case ValueType::Double:
		m_value = move ( other.m_value );
		break;
	case ValueType::Bool:
		m_value = move ( other.m_value );
		break;
	case ValueType::String:
		m_value = move ( other.m_value );
		break;
	case ValueType::Object:
		m_value = move ( other.m_value );
		break;
	case ValueType::Array:
		m_value = move ( other.m_value );
		break;
	case ValueType::Null:
	default:
		break;
	}

	return *this;
}

Value& Value::operator[] ( const std::string& key )
{
	if ( _type == ValueType::Null ) {
		_type = ValueType::Object;
	}

	if ( _type != ValueType::Object )
		throw std::string ( "Item is no Object" );


	return std::get<Object>(m_value)[key];
}

const Value& Value::operator[] ( const std::string& key ) const
{
	if ( _type != ValueType::Object )
		throw std::string ( "Item is no Object" );

	try {
		return std::get<Object>(m_value).at ( key );
	} catch ( const std::out_of_range& oor ) {
		//std::cerr << "Out of Range error (" << key << "): " << oor.what() << '\n';
		return *this;
	}

}

Value& Value::operator[] ( const int key )
{
	if ( _type != ValueType::Array )
		throw std::string ( "Item is no Array" );
	return std::get<Array>(m_value)[key];
}

const Value& Value::operator[] ( const int key ) const
{
	if ( _type != ValueType::Array )
		throw std::string ( "Item is no Array" );
	return std::get<Array>(m_value)[key];
}


ValueType Value::type() const
{
	return _type;
}

int Value::toInt() const
{
	return std::get<int>(m_value);
}

double Value::toDouble() const
{
	return std::get<double>(m_value);
}

const std::string& Value::toString() const
{
	return std::get<std::string>(m_value);
}

bool Value::toBool() const
{
	return std::get<bool>(m_value);
}

Array Value::toArray() const
{
	return std::get<Array>(m_value);
}

Object Value::toObject() const
{
	return std::get<Object>(m_value);
}

static unsigned int indentLvl = 0;

inline static void indent ( std::ostream& os )
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
		indent ( os );
		os << "\"" + item->first + "\":" << item->second;
		if ( ++item != obj.end() )
			os << "," << std::endl;
	}
	os << std::endl;

	indentLvl--;
	indent ( os );
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
		os << std::get<int>(val.m_value);
		break;
	case ValueType::Double:
		os << std::get<double>(val.m_value);
		break;
	case ValueType::Bool:
		os << ( std::get<bool>(val.m_value)?"true":"false" );
		break;
	case ValueType::String:
		os << "\"" + std::get<std::string>(val.m_value) + "\"";
		break;
	case ValueType::Object:
		os << std::get<Object>(val.m_value);
		break;
	case ValueType::Array:
		os << std::get<Array>(val.m_value);
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
