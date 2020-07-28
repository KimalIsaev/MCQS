
#pragma once
#include <iostream>
#include <vector>
using namespace std;

class StateChange
{
private:
	bool existence = false;
	vector<int> orbitChange;
	vector<int> phaseChange;
	StateChange();
	StateChange(vector<int>, vector<int>);
	bool setStateChange(vector<int>, vector<int>);
};

