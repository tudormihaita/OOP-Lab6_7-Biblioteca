#pragma once

class Tests {
public:
	void run_all_tests();
private:
	void run_domain_tests();
	void run_validation_tests();
	void run_repo_tests();
	void run_service_tests();
};