#pragma once

#ifdef PRINTLIBRARY_EXPORTS
#define PRINTLIBRARY_API __declspec(dllexport)
#else
#define PRINTLIBRARY_API __declspec(dllexport)
#endif


extern "C" {
	PRINTLIBRARY_API void printWelcomeMessage();
}

