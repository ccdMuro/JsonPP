#include <iostream>
#include <JsonPP.h>

int main(int args, char** argv)
{
	std::cout << "##### Example - from Code #####\n";
	std::cout << "Ccd::Json::Object from scrach\n";
	std::cout << "###############################\n";

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

	std::cout << "==>\n";
	std::cout << jOb;
	std::cout << "\n<==\n\n";

	return 0;
}
