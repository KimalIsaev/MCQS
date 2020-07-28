#include "StateChange.h"

StateChange::StateChange(vector<int> orbit, vector<int> phase)
{
	orbitChange = orbit;
	phaseChange = phase;
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