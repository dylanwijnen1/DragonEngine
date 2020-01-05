#pragma once

#include <Game/@{PRJ_NAME}@Layer.h>
#include <Dragon/Application/Application.h>

class @{PRJ_NAME}@App final : public dragon::Application
{
	virtual bool OnInit() final override
	{
		PushLayer(new @{PRJ_NAME}@Layer());
		return true;
	}
};