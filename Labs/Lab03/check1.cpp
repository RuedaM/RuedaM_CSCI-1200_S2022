/*
g++ -Wall -Wextra -g check1.cpp -o check1.exe
*/

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;



void compute_squares(int a[], int b[], unsigned int n) {
	int *p, *q;
    q = b;


	for ( p=a; p<a+n; ++p ) {
		*q = (*p)*(*p);
		++q;
	}

}

int main() {
	const int n = 5;
	int a[n] = {1, 2, 3, 4, 5};
	int b[n];
	for (int i=0; i<n; i++) {cout<<a[i]<<" ";}
	cout<<endl;

	compute_squares(a, b, n);
	for (int i=0; i<n; i++) {cout<<a[i]<<" ";}
	cout<<endl;
	for (int j=0; j<n; j++) {cout<<b[j]<<" ";}
	cout<<endl;

	return 0;
}