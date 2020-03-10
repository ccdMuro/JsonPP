#include <iostream>
#include <JsonPP.h>

int main(int args, char** argv)
{
	// Example 1
	// Create Ccd::Json::Object manualy
	auto jOb = Ccd::Json::Object {};
	
	// value - string 
	jOb["Hello"] = "World";

	// value - int
	jOb["answer"] = 42;

	// value - double
	jOb["pi"] = 3.14159;
	
	// value - bool
	jOb["valid"] = true;

	// value - null
	jOb["empty"] = nullptr;

	// value - array
	jOb["colors"] = { "red", "green", "blue" };

	// value - object
	jOb["user"] = Ccd::Json::Object{
			{"name","max"},
			{"age",18},
			{"size",1.90},
			{"hobbies", { "reading", "rock music" }}
	};

	std::cout << "\n";
	std::cout << "########## Example 1 #########" << "\n";
	std::cout << "Create Ccd::Json::Object from scrach\n";
	std::cout << "##############################" << "\n";
	std::cout << "==> " << jOb << "\n";

	// Example 2
	// Read in a JSON String
	
	// example JSON string
	constexpr auto JSONstring = 
	"{\"subobject\":{\"id\":1337,\"mixed_array\":[123,\"book\", 5.6, false]}}";

	// parse String and return Ccd::Json::Object
	auto jOb2 = Ccd::Json::JsonPP::objectFromString(JSONstring);

	std::cout << "\n";
	std::cout << "########## Example 2 #########" << "\n";
	std::cout << "Ccd::Json::Object from String\n";
	std::cout << "##############################" << "\n";
	std::cout << "Initial String:\n";
	std::cout << "==> " << JSONstring << "\n";
	std::cout << "Resulting Object:\n";
	std::cout << "==> " << jOb2 << "\n";


	// Example 3 
	// Access Ccd::Json::Object value in code
	std::cout << "\n";
	std::cout << "########## Example 3 #########" << "\n";
	std::cout << "Access Ccd::Json::Object values in code\n";
	std::cout << "##############################" << "\n";

	// Access array elements in a for loop
	std::cout << "Object 1 colors:\n";
	std::cout << "==> ";
	for ( const auto& color : jOb["colors"].toArray()) {
		std::cout << color << " ";
	}
	std::cout << "\n";
	
	// Access element
	// If using operator<< of an iostream
	// there is no need to cast the Ccd::Json
	// into explicit type 
	std::cout << "Object 2 subobject id:\n";
	std::cout << "==> " << jOb2["subobject"]["id"] << "\n";

	// Read element and write to variable
	// If writing to variable use access method like
	// .toString() or a explicit cast like static_cast<int>
	auto userName = jOb["user"]["name"].toString();
	auto userAge = static_cast<int>(jOb["user"]["age"]);
	std::cout << "User age:\n";
	std::cout << "==> " << userName << " " << userAge << "\n";

	return 0;
}
