#pragma once
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <cassert>
#include "Tests.h"
#include "UI.h"

using std::cout;

void run() {
	Tests tests;
	tests.run_all_tests();

	BookRepository book_repository;
	Validator book_validator;
	Library book_library{ book_repository, book_validator };
	ConsoleUI ui{ book_library };


	ui.run();
}


int main() {
	run();

	
	_CrtDumpMemoryLeaks();
	return 0;
}	