#pragma once
#include <string>
#include "AuthenticationManager.h"
#include "InstanceManager.h"
#include "DatabaseConnection.h"
using namespace std;


static AuthenticationManager authManager; //
static InstanceManager instManager; //
class Main
{
public:

	Main() {};
	void start(); //
};

