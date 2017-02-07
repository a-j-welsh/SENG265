#include <iostream>
#include <stdlib.h>

#include "dynamic_array.h"

using namespace std;

int main() {
	Dynamic_array d;
	d.insert(1,0);
	d.insert(3,1);
	d.insert(5,2);
	d.insert(7,3);
	d.insert(9,4);
	d.insert(11,5);
	d.print_state();

	cout << "********** remove(int i)" << endl;

	cout << "********** case 1: range error" << endl;
	try {
		d.remove(-1);
	} catch (Dynamic_array::Subscript_range_exception) {
		cout << "exception caught at -1" << endl;
	}
	try {
		d.remove(6);
	} catch (Dynamic_array::Subscript_range_exception) {
		cout << "exception caught at 6" << endl;
	}

	cout << "********** case 2: block size == 1" << endl;
	d.remove(5);
	d.print_state();

	cout << "********** case 3: block size > 1" << endl;
	cout << "***** remove right element" << endl;
	d.remove(4);
	d.print_state();

	cout << "***** remove left element" << endl;
	d.remove(0);
	d.print_state();
}
