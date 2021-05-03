
#include <iostream>

#define E_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062

int monteCarlo_float() {
	int tries = 0;
	
	// TODO: approximate Pi and count the tries

	return tries;
}

int monteCarlo_double() {
	int tries = 0;
	
	// TODO: approximate Pi and count the tries

	return tries;
}

int monteCarlo_long_double() {
	int tries = 0;
	
	// TODO: approximate Pi and count the tries

	return tries;
}

int main(int argc, char * argv[])
{
	std::cout << "Float Tries: " <<  monteCarlo_float() << std::endl;
	std::cout << "Double Tries: " << monteCarlo_double() << std::endl;
	std::cout << "Long Double Tries: " << monteCarlo_long_double() << std::endl;
	
	// TODO: Provide an exact output using the three data types.
	std::cout << "(in-) Exact Output of float Pi: " << E_PI << std::endl;
	
	return 0;
}
