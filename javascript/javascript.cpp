#pragma once
#include "javascript.h"
#include "js_duktape.h"

namespace javascript {
	std::shared_ptr<Javascript> CreateDuktape()
	{
		return std::make_shared<DuktapeImpl>();
	}
} // End namespace javascript.