#pragma once

#include <Game/_PRJ_NAME_Layer.h>
#include <Dragon/Application/Application.h>

class _PRJ_NAME_App final : public dragon::Application
{
	virtual bool OnInit() final override
	{
		PushLayer(new _PRJ_NAME_Layer());
		return true;
	}
};