#pragma once

// As cool as python is it doesn't handle loading embedded "scripts" very well.
// In order to embed scripts into the final "Resource" zipfile, and give the ability to import all scripts that are going to be embedded
// Need to be pre-loaded through an interface like : https://stackoverflow.com/questions/5362771/how-to-load-a-module-from-code-in-a-string#answer-53080237
//
// Issue: Script dependency will possibly be a problem.
//
// if (RELEASE)
//		Iterate over all scripts in the scripts folder:
//			dragon_create_module_by_string("modulename", string);
// Python:	
// import sys, importlib
// 
// dragon_create_module_by_string(...)
//
//		module_name = 'my_module'
//		module_spec = importlib.util.spec_from_loader(module_name, loader=None)
//		module_instance = importlib.util.module_from_spec(module_spec)
//
//		exec(codeAsString, module_instance.__dict__)
//		sys.modules[module_name] = module_instance
//
//
// WHAT WOULD BE EVEN BETTER :
// It is possible to extend the importing process from python. Creating a "Finder" and "Loader" would solve all issues.
// https://docs.python.org/3/reference/import.html

#include <pybind11/embed.h>
namespace py = pybind11;

void init_dragon_module(py::module& m);

PYBIND11_EMBEDDED_MODULE(pydragon, m)
{
	init_dragon_module(m);
}