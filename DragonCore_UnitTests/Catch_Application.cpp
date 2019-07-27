#pragma once

#include <ostream>

#include <catch2/catch.hpp>

#include <Dragon/Config.h>
#include <Dragon/Application/Application.h>
#include <Dragon/Application/Layer.h>

class TestApp : public dragon::Application
{
	friend std::ostream& operator<<(std::ostream& out, const dragon::Application& app)
	{
		return out << "TestApp" << std::endl;
	}
};

class TestLayer : public dragon::Layer
{
	virtual void Update(float dt) {}
	virtual void FixedUpdate(float dt) {}
	virtual void Render() {}
};

TEST_CASE("Testing Initialization", "[DragonEngine][Application]")
{
	TestApp app;
	REQUIRE(app.Init());
	app.Run();
}