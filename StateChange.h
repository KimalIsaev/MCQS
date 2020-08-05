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
public:
	StateChange() {};
	StateChange(const StateChange&);
	StateChange(vector<int>, vector<int>);
	bool setStateChange(vector<int>, vector<int>);
	bool getExistance();
	StateChange& operator=(const StateChange&);
	~StateChange() {};
	friend std::ostream& operator<<(std::ostream&, StateChange);
};

