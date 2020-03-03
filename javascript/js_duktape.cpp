#pragma once
#include "js_duktape.h"

namespace javascript {

	DuktapeImpl::DuktapeImpl()
	{
		ctx = duk_create_heap_default();
	}

	DuktapeImpl::~DuktapeImpl()
	{
		duk_destroy_heap(ctx);
	}

	void DuktapeImpl::AddFromString(const std::string& source)
	{
		duk_push_string(ctx, source.c_str());
		duk_eval(ctx);
	}

	void DuktapeImpl::AddFromStream(std::istream& is)
	{
		std::string s(std::istreambuf_iterator<char>(is), {});

		duk_push_string(ctx, s.c_str());
		duk_eval(ctx);

	}

	const std::size_t DuktapeImpl::GetPrintLines() const
	{

		return std::size_t();
	}

	const std::string DuktapeImpl::GetPrintString()
	{
		return std::string();
	}

	const std::any DuktapeImpl::CallFunction(const std::string& func, const std::vector<std::any>& args)
	{

		duk_get_global_string(ctx, func.c_str());

		for (const auto& arg : args)
		{
			if (arg.type() == typeid(int))
			{
				duk_push_int(ctx, std::any_cast<int>(arg));
			}
		}

		duk_call(ctx, args.size());

		std::any value = GetReturn();

		duk_pop(ctx);
		
		return value;
	}

	const std::any DuktapeImpl::CallMethod(const std::string& obj, const std::string& func, const std::vector<std::any>& args)
	{
		duk_get_global_string(ctx, obj.c_str());
		duk_get_prop_string(ctx, -1, func.c_str());
		duk_dup(ctx, -2);

		for (const auto& arg : args)
		{
			if (arg.type() == typeid(int))
			{
				duk_push_int(ctx, std::any_cast<int>(arg));
			}
		}

		duk_call_method(ctx, args.size());

		std::any value = GetReturn();

		duk_pop_2(ctx);

		return value;
	}

	const std::string DuktapeImpl::GetTopType(int id) const
	{
		if (duk_is_number(ctx, id))
		{
			return "number";
		}
		if (duk_is_string(ctx, id))
		{
			return "string";
		}

		return std::string();
	}

	const std::size_t DuktapeImpl::SetArgs(const std::vector<std::any>& args) const
	{
		return std::size_t();
	}

	const std::any DuktapeImpl::GetReturn() const
	{
		std::any value;
		std::string type = GetTopType(-1);
		if (type == "number")
		{
			value = duk_get_number(ctx, -1);
		}
		else if (type == "string")
		{
			value = duk_get_string(ctx, -1);
		}

		return value;
	}
}