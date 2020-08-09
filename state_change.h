#ifndef STATE_CHANGE_H_
#define STATE_CHANGE_H_

#include <iostream>
#include<vector>


class StateChange
{
private:
	std::vector<int> orbit_change_;
	std::vector<int> phase_change_;
public:
	StateChange() {};
	StateChange(const StateChange&);
	StateChange(const std::vector<int>, const std::vector<int>);
	//bool SetStateChange(const std::vector<int>, const std::vector<int>);
	StateChange& operator=(const StateChange&);
	StateChange& operator+(const StateChange&);
	~StateChange() {};
	friend std::ostream& operator<<(std::ostream&, const StateChange);
	static StateChange StateChangeWithOrbit(const std::vector<int>);
	static StateChange StateChangeWithPhase(const std::vector<int>);
};
#endif
