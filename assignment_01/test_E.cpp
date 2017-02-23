#include <iostream>
#include <stdlib.h>

#include "dynamic_array.h"

using namespace std;

int main() {
	Dynamic_array p0;
	Dynamic_array d0(p0);
	d0.print_state();
	p0.print_state();

	d0.insert(1, 0);
	d0.print_state();
	p0.print_state();

	Dynamic_array p3;
	p3.insert(2, 0);
	p3.insert(4, 1);
	p3.insert(6, 2);
	Dynamic_array d1(p3);
	d1.print_state();
	p3.print_state();

	d1[1] = 99;
	d1.print_state();
	p3.print_state();

	Dynamic_array d2;
	d2.insert(1,0);
	d2 = p0;
	d2.print_state();
	p0.print_state();

	d2.insert(99,0);
	d2.print_state();
	p0.print_state();

	Dynamic_array d3;
	d3.insert(1,0);
	d3 = p3;
	d3.print_state();
	p3.print_state();

	d3[1] = 99;
	d3.print_state();
	p3.print_state();
}
