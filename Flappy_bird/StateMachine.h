#pragma once

#include "State.h"

using StateRef = std::unique_ptr<State>;

class StateMachine
{
public:
	void AddState(StateRef newState, bool isReplacing = true);
	void RemoveState();
	void StateChanges();

	StateRef& GetActiveState();

private:
	std::stack<StateRef> _states;
	StateRef _newState;
	bool _isRemoving;
	bool _isAdding;
	bool _isReplacing;
};