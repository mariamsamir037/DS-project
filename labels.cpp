#include <iostream>
#include <string>
using namespace std;

class labels{
public:
	int bar;
	int margin;
	string features;

public:
	labels(string f, int b, int m){
	bar = b;
	margin = m;
    features = f;
	}
};
