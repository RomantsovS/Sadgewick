#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../List.h"

int main() {
	CList<int> lst{15, 9};

	lst.print();

	lst.sort();

	lst.print();

	return 0;
}