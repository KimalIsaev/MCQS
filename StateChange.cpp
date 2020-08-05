#include "StateChange.h"

StateChange::StateChange(vector<int> orbit, vector<int> phase)
{
	orbitChange = orbit;
	phaseChange = phase;
	existence = true;
}

StateChange::StateChange(const StateChange& orig)
{
	orbitChange = orig.orbitChange;
	phaseChange = orig.phaseChange;
	existence = true;
}

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

bool StateChange::getExistance()
{
	return existence;
}

StateChange& StateChange::operator=(const StateChange &newStateChange)
{
	existence = newStateChange.existence;
	orbitChange = newStateChange.orbitChange;
	phaseChange = newStateChange.phaseChange;
	return *this;
}