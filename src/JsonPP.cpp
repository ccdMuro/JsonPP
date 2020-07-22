#include "JsonPP.h"

#include <iostream>
#include <sstream>

using namespace std;

namespace Ccd {
namespace Json {

Value JsonPP::arrayFromString(std::string jsonString)
{
	// make shure that decimal delimiter is a dot '.'
	std::setlocale(LC_NUMERIC, "C");

	auto newArray = Array{};
	auto newValue = Value(nullptr);

	// check the borders
	auto beginPos = jsonString.find_first_of('[');
	auto endPos = jsonString.find_last_of(']');

	// if borders can not be defined something is wrong
	if (beginPos == string::npos || endPos == string::npos) {
		cout << "can't tell beginning or end of array" << endl;
		return newValue;
	}

	// offset is one position after the beginning border
	auto offset = beginPos + 1;

	// find the first character
	beginPos = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset);

	// if no usefull character could be found position is set to npos
	while (beginPos != string::npos) {
		offset = beginPos;
		// it could be ne new sub object
		if (jsonString.at(offset) == '{') {
			auto newBeginPos = offset;
			auto newEndPos = offset;
			auto openCount = 0;
			auto closeCount = 0;

			// find the enclosing curly braces
			for (auto character : jsonString.substr(offset)) {
				if (character == '{')
					openCount++;
				if (character == '}')
					closeCount++;
				// if the count of close and open curly braces is equeal
				// we have found the position of the closing one
				if (openCount == closeCount)
					break;
				newEndPos++;
			}

			// if the count is different there is a syntax error
			if (openCount != closeCount) {
				cout << "could not tell end of new subObject" << endl;
				return newValue;
			}

			// if everything went right, set the dataName and start a new
			// objectFromJson querry recursively
			auto subObject = objectFromString(jsonString.substr(newBeginPos,
				newEndPos - newBeginPos + 1));
			if (subObject.type() == ValueType::Null) {
				std::cout << "subObject ist nullptr" << std::endl;
				return newValue;
			}
			//newJsonObject->subObj.emplace(dataName, move(subObject));
			newArray.push_back(move(subObject));
			// set the offset to one position after the closing curly braces 
			offset = newEndPos + 1;
		}
		// it could be a string value
		else if (jsonString.at(offset) == '"') {
			// find the value borders
			auto beginOfValue = offset + 1;
			auto endOfValue = jsonString.find_first_of('"', offset + 1);
			if (endOfValue == string::npos) {
				cout << "cant find end of value" << endl;
				return newValue;
			}

			// save the found value
			auto value = jsonString.substr(beginOfValue, endOfValue - beginOfValue);

			// add the found data to the object struct map
			newArray.emplace_back(move(value));

			// set the offset to one position after the end of value
			offset = endOfValue + 1;
		}
		// it could be a numerical value
		else if (isdigit(jsonString.at(offset)) || (jsonString.at(offset) == '-')) {
			auto tempPos = offset;
			offset++;
			while (isdigit(jsonString.at(offset))) {
				offset++;
			}

			if (jsonString.at(offset) == '.') {
				offset++;

				if (!isdigit(jsonString.at(offset))) {
					std::cout << "exptected digit" << std::endl;
					return newValue;
				}
				offset++;
				while (isdigit(jsonString.at(offset))) {
					offset++;
				}
				//save the found double
				auto value = stod(jsonString.substr(tempPos, offset - tempPos));
				// add the found data to the object struct map
				newArray.emplace_back(value);
			}
			else {
				// save the found int
				auto value = stoi(jsonString.substr(tempPos, offset - tempPos));
				// add the found data to the object struct map
				newArray.emplace_back(value);
			}
		}
		//it could be an array
		else if (jsonString.at(offset) == '[') {
			
			auto newEndPos = offset;
			auto openCount = 0;
			auto closeCount = 0;

			// find the enclosing curly braces
			for (auto character : jsonString.substr(offset)) {
				if (character == '[')
					openCount++;
				if (character == ']')
					closeCount++;
				// if the count of close and open curly braces is equeal
				// we have found the position of the closing one
				if (openCount == closeCount)
					break;
				newEndPos++;
			}

			// if the count is different there is a syntax error
			if (openCount != closeCount) {
				cout << "could not tell end of new subObject" << endl;
				return newValue;
			}
			auto value = arrayFromString(jsonString.substr(offset));
			newArray.push_back(move(value));

			offset = newEndPos + 1;
		}
		else if (jsonString.at(offset) == ']') {
			break;
		}
		else if (jsonString.at(offset) == 't') {
			if (jsonString.compare(offset, 4, "true") == 0) {
				newArray.emplace_back(true);
				offset += 4;
			}
			else
				offset++;
		}
		else if (jsonString.at(offset) == 'f') {
			if (jsonString.compare(offset, 5, "false") == 0) {
				newArray.emplace_back(false);
				offset += 5;
			}
			else
				offset++;
		}
		else if (jsonString.at(offset) == 'n') {
			if (jsonString.compare(offset, 4, "null") == 0) {
				newArray.emplace_back(nullptr);
				offset += 4;
			}
			else
				offset++;
		}
		else {
			cout << "invalid value " << jsonString.at(offset) << " offset " << offset << endl;
			cout << jsonString << std::endl;
			return newValue;
		}

		// find the next character
		offset = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset);

		// is it a closing curly braces we reached the end of the object and we are done
		if (jsonString.at(offset) == ']')
			break;
		// if a comma is next more values are following
		else if (jsonString.at(offset) == ',') {
			beginPos = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset + 1);
			continue;
		}
		// else syntax error
		else {
			std::cout << "syntax error!" << std::endl;
			std::cout << jsonString.substr(offset);
			return newValue;
		}

	}

	newValue = move(Value(move(newArray)));

	return newValue;
}

Value JsonPP::objectFromString(std::string jsonString)
{
	// make shure that decimal delimiter is a dot '.'
	std::setlocale(LC_NUMERIC, "C");
	// prepare new struct
	auto newJsonObject = Object{};
	auto newValue = Value(nullptr);

	// check the borders
	auto beginPos = jsonString.find_first_of('{');
	auto endPos = jsonString.find_last_of('}');

	// if borders can not be defined something is wrong
	if (beginPos == string::npos || endPos == string::npos) {
		cout << "can't tell beginning or end of object" << endl;
		return newValue;
	}

	// offset is one position after the beginning border
	auto offset = beginPos + 1;

	// find the first character
	beginPos = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset);

	// if no usefull character could be found position is set to npos
	while (beginPos != string::npos) {
		offset = beginPos + 1;

		// the first thing to find should be a string name
		if (jsonString.at(beginPos) != '"') {
			if (jsonString.at(beginPos) == '}') {
				break;
			}
			cout << "cant find beginning of dataName" << endl;
			cout << "beginPos = " << beginPos << " value " << jsonString.at(beginPos) << endl;
			return newValue;
		}

		// find the end of the string
		endPos = jsonString.find_first_of('"', offset);
		if (endPos == string::npos) {
			cout << "cant find end of dataName" << endl;
			return newValue;
		}

		// save the name to add it later to the map
		auto dataName = jsonString.substr(beginPos + 1, endPos - beginPos - 1);
		offset = endPos + 1;

		// check out the next character
		offset = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset);
		if (offset == string::npos) {
			cout << "cant find char after dataName" << endl;
			return newValue;
		}

		// after the name string should folow a colon
		if (jsonString.at(offset) != ':') {
			cout << "invalide char after dataName. should be colon" << endl;
			cout << jsonString.at(offset) << endl;
			return newValue;
		}

		// find the next character after the colon
		offset = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset + 1);
		if (offset == string::npos) {
			cout << "cant find value after colon" << endl;
			return newValue;
		}

		// it could be ne new sub object
		if (jsonString.at(offset) == '{') {
			auto newBeginPos = offset;
			auto newEndPos = offset;
			auto openCount = 0;
			auto closeCount = 0;

			// find the enclosing curly braces
			for (auto character : jsonString.substr(offset)) {
				if (character == '{')
					openCount++;
				if (character == '}')
					closeCount++;
				// if the count of close and open curly braces is equeal
				// we have found the position of the closing one
				if (openCount == closeCount)
					break;
				newEndPos++;
			}

			// if the count is different there is a syntax error
			if (openCount != closeCount) {
				cout << "could not tell end of new subObject" << endl;
				return newValue;
			}

			// if everything went right, set the dataName and start a new
			// objectFromJson querry recursively
			auto subObject = objectFromString(jsonString.substr(newBeginPos,
				newEndPos - newBeginPos + 1));
			if (subObject.type() == ValueType::Null) {
				std::cout << "subObject ist nullptr" << std::endl;
				return newValue;
			}
			//newJsonObject->subObj.emplace(dataName, move(subObject));
			newJsonObject.insert(make_pair(move(dataName), move(subObject)));

			// set the offset to one position after the closing curly braces 
			offset = newEndPos + 1;
		}
		// it could be a string value
		else if (jsonString.at(offset) == '"') {
			// find the value borders
			auto beginOfValue = offset + 1;
			auto endOfValue = jsonString.find_first_of('"', offset + 1);
			if (endOfValue == string::npos) {
				cout << "cant find end of value" << endl;
				return newValue;
			}

			// save the found value
			auto value = jsonString.substr(beginOfValue, endOfValue - beginOfValue);

			// add the found data to the object struct map
//			newJsonObject->data.emplace(dataName, value);
			newJsonObject.insert(make_pair(move(dataName), move(value)));

			// set the offset to one position after the end of value
			offset = endOfValue + 1;
		}
		// it could be a numerical value
		else if (isdigit(jsonString.at(offset)) || (jsonString.at(offset) == '-')) {
			auto tempPos = offset;
			offset++;
			while (isdigit(jsonString.at(offset))) {
				offset++;
			}

			if (jsonString.at(offset) == '.') {
				offset++;

				if (!isdigit(jsonString.at(offset))) {
					std::cout << "exptected digit" << std::endl;
					return newValue;
				}
				offset++;
				while (isdigit(jsonString.at(offset))) {
					offset++;
				}
				//save the found double
				auto value = stod(jsonString.substr(tempPos, offset - tempPos));
				// add the found data to the object struct map
				newJsonObject.insert(make_pair(move(dataName), move(value)));
			}
			else {
				// save the found int
				auto value = stoi(jsonString.substr(tempPos, offset - tempPos));
				// add the found data to the object struct map
				newJsonObject.insert(make_pair(move(dataName), move(value)));
			}
		} 
		//it could be an array
		else if (jsonString.at(offset) == '[') {
	
			auto newBeginPos = offset;
			auto newEndPos = offset;
			auto openCount = 0;
			auto closeCount = 0;

			// find the enclosing curly braces
			for (auto character : jsonString.substr(offset)) {
				if (character == '[')
					openCount++;
				if (character == ']')
					closeCount++;
				// if the count of close and open curly braces is equeal
				// we have found the position of the closing one
				if (openCount == closeCount)
					break;
				newEndPos++;
			}

			// if the count is different there is a syntax error
			if (openCount != closeCount) {
				cout << "could not tell end of new subObject" << endl;
				return newValue;
			}

			auto arrayItem = arrayFromString(jsonString.substr(newBeginPos, newEndPos+1 - newBeginPos));
			newJsonObject.insert(make_pair(move(dataName), move(arrayItem)));

			offset = newEndPos + 1;
		}
		else if (jsonString.at(offset) == 't') {
			if (jsonString.compare(offset, 4, "true") == 0) {
				newJsonObject.insert(make_pair(move(dataName), true));
				offset += 4;
			} else 
				offset++;
		}
		else if (jsonString.at(offset) == 'f') {
			if (jsonString.compare(offset, 5, "false") == 0) {
				newJsonObject.insert(make_pair(move(dataName), false));
				offset += 5;
			} else 
				offset++;
		}
		else if (jsonString.at(offset) == 'n') {
			if (jsonString.compare(offset, 4, "null") == 0) {
				newJsonObject.insert(make_pair(move(dataName), nullptr));
				offset += 4;
			}
			else
				offset++;
		}
		else {
			cout << "invalid value " << jsonString.at(offset) << endl;
			cout << jsonString << std::endl;
			return newValue;
		}

		// find the next character
		offset = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset);

		// is it a closing curly braces we reached the end of the object and we are done
		if (jsonString.at(offset) == '}')
			break;
		// if a comma is next more values are following
		else if (jsonString.at(offset) == ',') {
			beginPos = jsonString.find_first_not_of({ ' ', 9, 10 , 13 }, offset + 1);
			continue;
		}
		// else syntax error
		else {
			std::cout << "syntax error!" << std::endl;
			std::cout << jsonString.substr(offset);
			return newValue;
		}
	}
	
	newValue = move(Value(move(newJsonObject)));

	// if all went right, return the smart pointer to the parent object
	return newValue;
}

std::string JsonPP::stringFromObject ( const Object& jsonObject )
{
	std::stringstream jss;
	jss << jsonObject;
	return jss.str();
}

std::string JsonPP::stringFromArray( const Array& jsonArray )
{
	std::stringstream jss;
	jss << jsonArray;
	return jss.str();
}
}
}

