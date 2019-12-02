#pragma once

#include <ostream>

#include <catch2/catch.hpp>

#include <Dragon/Config.h>
#include <Dragon/Application/Application.h>
#include <Dragon/Application/Layer.h>

#include <Platform/SFML/Graphics/SfmlGraphics.h>

class TestLayer : public dragon::Layer
{
	

public:
	TestLayer() : dragon::Layer("TestLayer") {}
	~TestLayer() = default;

	TestLayer(const TestLayer&) = delete;
	TestLayer(TestLayer&&) = delete;
	TestLayer& operator=(const TestLayer&) = delete;
	TestLayer& operator=(TestLayer&&) = delete;

	virtual void OnAttach() final override { }
	virtual void OnDetach() final override { }

	virtual void Update(float dt) final override {}
	virtual void FixedUpdate(float dt) final override {}
	virtual void Render(dragon::RenderTarget& target) final override {}
};

class TestApp : public dragon::Application
{
	virtual bool OnInit() override
	{
		PushLayer(new TestLayer());
		return true;
	}

	friend std::ostream& operator<<(std::ostream& out, const dragon::Application& app)
	{
		return out << "TestApp" << std::endl;
	}
};

TEST_CASE("Testing Initialization", "[DragonEngine][Application]")
{
	TestApp app;
	REQUIRE(app.Init());
	app.Shutdown();

	// Need to deinitialize logging before running any other tests or we run into problems.
	dragon::Debug::GetInstance().SetSystem(nullptr);
}