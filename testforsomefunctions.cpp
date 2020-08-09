#include"state_change.h"
#include <vector>
#include <iostream>
using namespace std;


vector<vector<int>> GenereteOneMatrixVector(int n)
{
	vector<vector<int>> onesMatrixVector(n);
	for (int i = 0; i < n; i++) {
		vector<int> vec(n);
		onesMatrixVector[i] = vec;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			onesMatrixVector[i][j] = 0;
		onesMatrixVector[i][i] = 1;
	}
	return onesMatrixVector;
}

vector<int> GenereteZeroVector(size_t n)
{
	vector<int> vec(n);
	for (int i = 0; i < vec.size(); i++)
		vec[i] = 0;
	return vec;
}



vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<vector<int>> orbit,
	vector<vector<int>> phase) {
	int nPhase = phase.size();
	int nOrbit = orbit.size();
	int n;
	if (nOrbit > nPhase)
		n = nOrbit;
	else
		n = nPhase;
	vector<StateChange> vectorStateChange(n);
	int i;
	for (i = 0; i < nOrbit && i < nPhase; i++) {
		StateChange st(orbit[i], phase[i]);
		vectorStateChange[i] = st;
	}
	for (; i < nOrbit; i++) {
		vectorStateChange[i] = StateChange::StateChangeWithOrbit(orbit[i]);
	}
	for (; i < nPhase; i++) {
		vectorStateChange[i] = StateChange::StateChangeWithPhase(orbit[i]);
	}
	return vectorStateChange;
}

vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<int> orbit,
	vector<vector<int>> phase) {
	int nPhase = phase.size();
	vector<StateChange> vectorStateChange(nPhase);
	for (int i = 0; i < nPhase; i++) {
		StateChange st(orbit, phase[i]);
		vectorStateChange[i] = st;
	}
	return vectorStateChange;
}

vector<StateChange> createStateChangeVectorFromOrbitAndPhase(vector<vector<int>> orbit,
	vector<int> phase) {

	int nOrbit = orbit.size();
	vector<StateChange> vectorStateChange(nOrbit);
	for (int i = 0; i < nOrbit; i++) {
		StateChange st(orbit[i], phase);
		vectorStateChange[i] = st;
	}
	return vectorStateChange;

}

int main()
{
	vector<int> phase = GenereteZeroVector(3);
	vector<vector<int>> orbit = GenereteOneMatrixVector(3);
	vector<StateChange> vec = createStateChangeVectorFromOrbitAndPhase(orbit, phase);
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i];
	return 0;
}