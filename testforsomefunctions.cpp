
#include <vector>
#include <iostream>
#include<map>
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



vector<map<int, vector<int>>> createState(int n, vector<vector<int>> vec) {
	vector<map<int, vector<int>>> newState(vec.size());
	for (int i = 0; i < vec.size(); i++)
	{
		map<int, vector<int>> mapState;
		mapState[n] = vec[i];
		newState[i] = mapState;
	}
	return newState;
}


int main()
{
	vector<int> phase = GenereteZeroVector(3);
	vector<vector<int>> orbit = GenereteOneMatrixVector(3);
	vector<map<int, vector<int>>> vec = createState(2, orbit);
	for (int i = 0; i < vec.size(); i++) {
		cout << i << ":" << endl;
		map<int, vector<int>> ::iterator it = vec[i].begin();
		for (int j = 0; it != vec[i].end(); it++, j++) {  // выводим их
			cout << j << ") Key " << it->first << ", value:  ";
			for (int g = 0; g < it->second.size(); g++)
				cout << it->second[g] << " ";
		}
		cout << endl;
	}
	return 0;
}