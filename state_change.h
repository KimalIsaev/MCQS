#ifndef STATE_CHANGE_H_
#define STATE_CHANGE_H_

#include <iostream>
#include <vector>

class StateChange
{
private:
	vector<int> orbit_change_;
	vector<int> phase_change_;
public:
	StateChange() {};
	StateChange(const StateChange&);
	StateChange(const std::vector<int>, const std::vector<int>);
	//bool SetStateChange(const std::vector<int>, const std::vector<int>);
	StateChange& operator=(const StateChange&);
	~StateChange() {};
	friend std::ostream& operator<<(std::ostream&, const StateChange);
	static StateChange StateChangeWithOrbit(const vector<int>); //напиши, пожалуйста эти две
	static StateChange StateChangeWithPhase(const vector<int>);
};
#endif
