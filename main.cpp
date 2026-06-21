#include "HospitalSystem.h"
#include <iostream>

int main() {
	HospitalSystem& system = HospitalSystem::get_instance();

	system.start_system_loop();

	return 0;
}