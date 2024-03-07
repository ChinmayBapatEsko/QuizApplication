#pragma once
#include <string>
#include "AuthenticationManager.h"
#include "InstanceManager.h"
using namespace std;

class Main
{
public:
	AuthenticationManager authManager; //
	InstanceManager instManager; //

	Main() {};
	void start(); //
};

