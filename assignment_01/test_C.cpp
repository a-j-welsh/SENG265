#include <iostream>
#include <stdlib.h>

#include "dynamic_array.h"

using namespace std;

int main() {
	Dynamic_array d0;
	d0.print_state();

	Dynamic_array p0;
	p0.print_state();

	cout << "********** insert(dynamic_array & p, int i)" << endl;

	cout << "********** case 1: range error" << endl;
	try {
		d0.insert(p0, -1);
	} catch (Dynamic_array::Subscript_range_exception) {
		cout << "exception caught at -1" << endl;
	}
	try {
		d0.insert(p0, 1);
	} catch (Dynamic_array::Subscript_range_exception) {
		cout << "exception caught at 1" << endl;
	}
	d0.print_state();

	cout << "********** case 2: parameter array empty" << endl;
	d0.insert(p0, 0);
	d0.print_state();

	cout << "********** case 3: array empty" << endl;
	p0.insert(0, 0);
	p0.insert(2, 1);
	Dynamic_array d1;
	d1.insert(p0, 0);
	d1.print_state();

	cout << "********** case 4: array non-empty; new blocks not needed" << endl;
	d1.insert(p0, 1);
	d1.print_state();

	cout << "********** case 5: array non-empty; new blocks needed" << endl;
	cout << "***** case 5.a: insert position at start of block" << endl;
	Dynamic_array d2;
	for (int i = 0; i < 9; i++)
		d2.insert(2*i+1, i);
	d2.insert(p0, 5);
	d2.print_state();

	cout << "***** case 5.b: insert position at middle of block" << endl;
	Dynamic_array d3;
	for (int i = 0; i < 9; i++)
		d3.insert(2*i+1, i);
	d3.insert(p0, 7);
	d3.print_state();

	cout << "***** case 5.c: insert position after end of block" << endl;
	Dynamic_array d4;
	for (int i = 0; i < 9; i++)
		d4.insert(2*i+1, i);
	d4.insert(p0, 9);
	d4.print_state();
}
