#pragma once

namespace dragon
{

	class ApplicationSettings
	{
	public:
		~ApplicationSettings() = default;

		bool Init();

		ApplicationSettings(const ApplicationSettings&) = default;
		ApplicationSettings(ApplicationSettings&&) = default;
		ApplicationSettings& operator=(const ApplicationSettings&) = default;
		ApplicationSettings& operator=(ApplicationSettings&&) = default;

	private:
		ApplicationSettings() = default;
	};

};