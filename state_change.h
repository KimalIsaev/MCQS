#ifndef STATE_CHANGE_H_
#define STATE_CHANGE_H_

#include <iostream>
#include<map>


class StateChange
{
private:
	std::map<int, std::map<int, int>> state_;
public:
	StateChange() {};
	StateChange(const StateChange&);
	StateChange(std::map<int, std::map<int, int>>);
	//bool SetStateChange(const std::vector<int>, const std::vector<int>);
	StateChange& operator=(const StateChange&);
	StateChange& operator+(const StateChange&);
	~StateChange() {};
	friend std::ostream& operator<<(std::ostream&, const StateChange);
	//static StateChange StateChangeWithOrbit(const std::vector<int>);
	//static StateChange StateChangeWithPhase(const std::vector<int>);
};
#endif
