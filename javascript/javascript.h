#pragma once
#include <string>
#include <memory>
#include <vector>
#include <any>
#include <istream>

namespace javascript {

	// Simple javascript interface!
	// ============================
	// For now you can only receive object from function calls and method calls.
	// Also loading from a string and a stream does not return any result. 
	// Object are returned as map<string, any> structure (in any in case you
	// need it). Object need to be JSONifyable to be returned, mean no function
	// will be returned (they will be replaced by empty objects).
	class Javascript
	{
	public:
		// Add javascript code from a string to the engine.
		// throws exception 
		//	runtime_error	-> error message
		virtual void AddFromString(const std::string& source) = 0;
		// Add javascript code from a stream (a file) to the engine.
		// throws exception 
		//	runtime_error	-> error message
		virtual void AddFromStream(std::istream& is) = 0;
		// Call a function in the javascript.
		// throws exception 
		//	runtime_error	-> error message
		// Returns
		//	any				-> return value
		virtual const std::any CallFunction(
			const std::string& func,
			const std::vector<std::any>& args = {}) = 0;
		// Call a method in a class.
		// throws exception 
		//	runtime_error	-> error message
		// Returns
		//	any				-> return value
		virtual const std::any CallMethod(
			const std::string& obj,
			const std::string& func,
			const std::vector<std::any>& args = {}) = 0;
		// Get the number of lines left in the engine.
		virtual const std::size_t GetPrintLines() const = 0;
		// Pop the first line of code from the engine.
		virtual const std::string GetPrintString() = 0;
	};

	// Create a Duktape version of the javascript engine.
	std::shared_ptr<Javascript> CreateDuktape();

} // End namespace javascript.