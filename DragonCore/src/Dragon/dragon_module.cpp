#include <Dragon/Application/Application.h>

// Defined in : <Dragon/Components/component_bindings.cpp>
//void init_components(py::module& m);

// Defined in : <Dragon/Math/math_bindings.cpp>
void init_math(py::module& m);

void init_dragon_module(py::module& m)
{
	// Game Bindings
	// World, GameObject, Coroutine??, Application, Networking, etc.

	// Component bindings
	//init_components(m);

	// Debug
	py::class_<dragon::Debug> debug(m, "Debug");
	debug
		/// @page script-doc
		/// @section Debug
		/// Does documentation get generated from here ?
		.def_static("error", [] (const char* fmt) { ERR(fmt); })
		.def_static("warning", [] (const char* fmt) { WARN(fmt); })
		.def_static("log", [] (const char* fmt) { LOG(fmt); })
		.def_static("write", [] (const char* channel, const char* fmt) { DEBUG(channel, fmt); });
	

	// Math bindings
	init_math(m);
}