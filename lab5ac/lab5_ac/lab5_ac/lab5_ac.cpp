#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");
	int A = -45;
	int module_A = abs(A);
	char module_binary_a[9] = {0};
	for (int i = 0; i < 8; i++) {
		module_binary_a[i] = '0';
	}


	int k = 0;
	int a = 0;
	for (int i = 7; module_A > 0 && i >= 0; i--) {
		a = module_A % 2;
		if (a == 0)
			module_binary_a[i] = '0';
		else
			module_binary_a[i] = '1';
		module_A /= 2;
		k++;
	}
	//cout << module_binary_a << "\n";


	char binary_a[9] = {0};
	for (int i = 0; i < 8; i++) {
		if (module_binary_a[i] == '1') {
			binary_a[i] = '0';
		}
		else {
			binary_a[i] += '1';
		}
	}
	//cout << binary_a << "\n";


	int carry = 1;
	for (int i = 7; i >= 0; i--) {
		if (carry == 0) {
			break;
		}
		if (binary_a[i] == '0') {
			binary_a[i] = '1';
			carry = 0;
		}
		else {
			binary_a[i] = '0';
			carry = 1;
		}
	}
	cout << binary_a << "\n";
}
