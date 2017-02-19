#include <iostream>
#include <stdlib.h>

#include "dynamic_array.h"

using namespace std;

int main() {
	cout << "********** insert(int x, int i)" << endl;

	cout << "********** create empty array" << endl;
	Dynamic_array d;
	d.print_state();
	cout << "get_size():" << d.get_size() << endl;

	cout << "********** case 1: range error" << endl;
	try {
		d.insert(99,1);
	} catch (Dynamic_array::Subscript_range_exception) {
		cout << "exception caught at 1" << endl;
	}

	cout << "********** case 2: empty array" << endl;
	d.insert(3,0);
	d.print_state();
	cout << "get_size():" << d.get_size() << endl;

	cout << "********** case 3: non-empty array; new block not needed" << endl;
	cout << "***** insert before start" << endl;
	d.insert(1,0);
	d.print_state();
	cout << "***** insert after end" << endl;
	d.insert(5,2);
	d.print_state();

	cout << "********** case 4: non-empty array; new block needed" << endl;
	cout << "***** case 4.a: insert x into old block" << endl;
	d.insert(7,3);
	d.insert(9,4);
	d.insert(99,5);
	d.print_state();

	cout << "***** case 4.b: insert x into new block" << endl;
	d.insert(88,0);
	d.print_state();
}
