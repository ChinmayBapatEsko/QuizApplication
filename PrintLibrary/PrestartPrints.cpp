#include "pch.h"
#include "PrestartPrints.h"
#include <stdio.h>

extern "C" {
	void printWelcomeMessage() {
		printf("(DLL_IS_PRINTING) WELCOME To my Quiz Application. Without any further ado, lets start! (DLL_IS_PRINTING)\n");
	}
}
