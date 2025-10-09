#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <string>


using namespace std;

int main()
{
    setlocale(LC_ALL, "russian");
	float A;
	cin >> A;
	string sign;
	if (A < 0) {
		sign = '1';
	}
	else {
		sign = '0';
	}
	int module_A = abs(A);
	string module_binary_a;
	int k = 0;
	int a = 0;
	while (module_A > 0) {
		a = module_A % 2;
		module_binary_a = to_string(a) + module_binary_a;
		module_A /= 2;
		k++;
	}
	//cout << module_binary_a << "\n";


	int A1 = int(A);
	float zapyat = (A - A1);
	//cout << zapyat << "\n";
	string drobnaya;
	for (int i = 0; i < 23 && zapyat > 0; i++) {
		zapyat *= 2;
		if (zapyat >= 1.0) {
			drobnaya += '1';
			zapyat -= 1.0;
		}
		else {
			drobnaya += '0';
		}
	}


	
	int exponenta = 0;
	for (int i = 1; i < k; i++) {
		exponenta++;
	}
	/*cout << "\n" << exponenta;*/
	int exp = 127 + exponenta;
	string exp_konech;
	k = 0;
	while (exp > 0) {
		int temp = exp % 2;
		exp_konech = to_string(temp) + exp_konech;
		exp /= 2;
		k++;
	}
	//cout << exp_konech << "\n";


	string bin_drob = module_binary_a + drobnaya;
	string mantissa;
	for (int i = 1; i < size(bin_drob); i++) {
		mantissa += bin_drob[i];
	}
	while (size(mantissa) < 23) {
		mantissa += '0';
	}
	/*cout << mantissa;*/
	string number = sign + " " + exp_konech + " " + mantissa;
	cout << number << "\n";
}