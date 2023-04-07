/*
cd /mnt/c/users/ruedam/Documents/CSCI1020_DS/Labs/Lab05

g++ -g -Wall -std=c++11 a.cpp -o a.out

time ./a.out

~/DrMemory-Linux-2.4.0-2/bin64/drmemory -brief -- test_vec.out
*/

#include<iostream>
#include<ostream>
#include<string>
#include<vector>

using namespace std;

int foobar(const vector<string>& a, int b) {
	int answer = 0;
	for (int i=0 ; i<a.size() ; i+=b) {
		answer++;
	}
	return answer;
}

void foo2(const vector<int>& a, string b) {
	b.clear();
	for (int i=0 ; i<a.size() ; i++) {
		if (a[i]>0)
			b.push_back('+');
		else
			b.push_back('-');
	}
}

vector<int> foo3(const vector<int>& a, const string& b) {
	return vector<int>(b.size(), a.size());
}

int foo3(const vector<string>& a, const string& b) {
	int ret = 0;
	for (int i=0 ; i<a.size() ; i++) {
		ret += (a[i]==b);
	}
	return ret;
}

vector<int> foo4(const vector<int>& a) {
	vector<int> answer = a;
	for (int i=0 ; i<a.size() ; i++) {
		if (a[i]<(a[a.size()-1]*a[a.size()-1])) {
			answer.erase(answer.end()-1);
		}
	}
	return answer;
}

vector<int> foo5(const vector<int>& a, int b) {
	vector<int> ret;
	for (int i=0 ; i<a.size() ; a[i]) {
		if (a[i]<b) {
			ret.insert(ret.end(), a[i]);
		}
	}
	return ret;
}



int main() {
	vector<int> intVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	vector<string> strVec = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"};

	int bint = 25;
	string bstring = "hello, world.";


	int answer = foobar(strVec, bint);
	cout<<answer<<endl;
	cout<<"======================================================"<<endl;
	for (int i=0 ; i<intVec.size() ; i++) {
		cout<<intVec[i]<<" ";
	}
	cout<<endl;
	foo2(intVec, bstring);
	for (int i=0 ; i<intVec.size() ; i++) {
		cout<<intVec[i]<<" ";
	}
	cout<<endl;
	cout<<"======================================================"<<endl;
	vector<int> foo3Result = foo3(intVec, bstring);
	for (int i=0 ; i<foo3Result.size() ; i++) {
		cout<<foo3Result[i]<<" ";
	}
	cout<<endl;
	cout<<"======================================================"<<endl;
	int ret = foo3(strVec, bstring);
	cout<<ret<<endl;
	cout<<"======================================================"<<endl;
	vector<int> answer2 = foo4(intVec);
	for (int i=0 ; i<answer2.size() ; i++) {
		cout<<answer2[i]<<" ";
	}
	cout<<endl;
	cout<<"======================================================"<<endl;
	vector<int> ret2 = foo5(intVec, bint);
	for (int i=0 ; i<ret2.size() ; i++) {
		cout<<ret2[i]<<" ";
	}
	cout<<endl;
}