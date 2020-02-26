#pragma once

#include <Game/AI/Behaviors/Behavior.h>

class IdleBehavior : public Behavior
{
public:
	IdleBehavior()
		: Behavior()
	{}

	virtual Behavior* Update(float dt) override { return nullptr; }
};