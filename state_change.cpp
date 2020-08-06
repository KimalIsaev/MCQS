#include "StateChange.h"

StateChange::StateChange(const std::vector<int> orbit, const std::vector<int> phase)
{
	orbitChange = orbit;
	phaseChange = phase;
}

StateChange::StateChange(const StateChange& orig)
{
	orbitChange = orig.orbitChange;
	phaseChange = orig.phaseChange;
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
	orbitChange = newStateChange.orbitChange;
	phaseChange = newStateChange.phaseChange;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const StateChange x) 
{
	for (int i = 0; i < x.orbitChange.size(); i++)
		os << x.orbitChange[i] << " ";
	os << endl;
	for (int i = 0; i < x.phaseChange.size(); i++)
		os << x.phaseChange[i] << " ";
	return os;
}

//эта функции должна возвращать StateChange с orbit_change_ и пустым phase_change_ 
static StateChange StateChangeWithOrbit(const vector<int> orbit_change){

}

//эта функции должна возвращать StateChange с orbit_change_ и пустым phase_change_
static StateChange StateChangeWithPhase(const vector<int> phase_change){

}
