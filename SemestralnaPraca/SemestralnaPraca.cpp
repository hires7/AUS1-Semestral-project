#include <iostream>
#include "Town.h"

int main()
{
	Town town("Bratislava", 1, 432000);
	std::cout << town.toString() << std::endl;
}
