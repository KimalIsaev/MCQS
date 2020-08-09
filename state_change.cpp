#include "state_change.h"

StateChange::StateChange(const std::vector<int> orbit, const std::vector<int> phase)
{
	orbit_change_ = orbit;
	phase_change_ = phase;
}


StateChange::StateChange(const StateChange& orig)
{
	orbit_change_ = orig.orbit_change_;
	phase_change_ = orig.phase_change_;
}


StateChange& StateChange::operator=(const StateChange &newStateChange)
{
	orbit_change_ = newStateChange.orbit_change_;
	phase_change_ = newStateChange.phase_change_;
	return *this;
}

StateChange& StateChange::operator+(const StateChange& newStateChange)
{
	int thisSize = this->phase_change_.size();
	int newSize = newStateChange.phase_change_.size();
	StateChange resultStateChange;
	if (!thisSize || !newSize)
		if (!thisSize)
			resultStateChange.phase_change_ = newStateChange.phase_change_;
		else
			resultStateChange.phase_change_ = this->phase_change_;
	else
	{
		int i;
		for (i = 0; i < thisSize && i < newSize; i++)
			resultStateChange.phase_change_[i] = resultStateChange.phase_change_[i] + this->phase_change_[i];
		for (; i < thisSize; i++)
			resultStateChange.phase_change_[i] =this->phase_change_[i];
		for (; i < newSize; i++)
			resultStateChange.phase_change_[i] = newStateChange.phase_change_[i];
	}

	thisSize = this->orbit_change_.size();
	newSize = newStateChange.orbit_change_.size();
	if (!thisSize || !newSize)
		if (!thisSize)
			resultStateChange.orbit_change_ = newStateChange.orbit_change_;
		else
			resultStateChange.orbit_change_ = this->orbit_change_;
	else
	{
		int i;
		for (i = 0; i < thisSize && i < newSize; i++)
			resultStateChange.orbit_change_[i] = resultStateChange.orbit_change_[i] + this->orbit_change_[i];
		for (; i < thisSize; i++)
			resultStateChange.orbit_change_[i] = this->orbit_change_[i];
		for (; i < newSize; i++)
			resultStateChange.orbit_change_[i] = newStateChange.orbit_change_[i];
	}

	return resultStateChange;
}


std::ostream& operator<<(std::ostream& os, const StateChange x) 
{
	os << "orbits:" << std::endl;
	for (int i = 0; i < x.orbit_change_.size(); i++)
		os << x.orbit_change_[i] << " ";
	os << std::endl;
	os << "phase:" << std::endl;
	for (int i = 0; i < x.phase_change_.size(); i++)
		os << x.phase_change_[i] << " ";
	os << std::endl;
	return os;
}

StateChange StateChange::StateChangeWithOrbit(const std::vector<int> new_orbit)
{
	StateChange a;
	a.orbit_change_ = new_orbit;
	return a;
}

StateChange StateChange::StateChangeWithPhase(const std::vector<int> new_phase)
{
	StateChange a;
	a.orbit_change_ = new_phase;
	return a;
}