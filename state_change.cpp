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
/* убрано так как хочется исключить возможности изменения в данном классе 
bool StateChange::setStateChange(vector<int> orbit, vector<int> phase)
{
	if (!existence)
	{
		orbitChange = orbit;
		phaseChange = phase;
		existence = true;
		return true;
	}
	return false;
}
*/

StateChange& StateChange::operator=(const StateChange &newStateChange)
{
	orbit_change_ = newStateChange.orbit_change_;
	phase_change_ = newStateChange.phase_change_;
	return *this;
}

//эта функции должна возвращать StateChange с orbit_change_ и пустым phase_change_ 
StateChange StateChange::StateChangeWithOrbit(const std::vector<int>)
{
	return StateChange();
}

StateChange StateChange::StateChangeWithPhase(const std::vector<int>)
{
	return StateChange();
}

std::ostream& operator<<(std::ostream& os, const StateChange x) 
{
	for (int i = 0; i < x.orbit_change_.size(); i++)
		os << x.orbit_change_[i] << " ";
	os << std::endl;
	for (int i = 0; i < x.phase_change_.size(); i++)
		os << x.phase_change_[i] << " ";
	return os;
}

