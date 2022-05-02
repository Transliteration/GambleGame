#pragma once
#include <memory>

#include "StateBase.hpp"

class StateMachine
{
    std::array<std::shared_ptr<StateBase>, State::_size> allStates;
    std::shared_ptr<StateBase> currentState;
    
public:
    StateMachine();
    std::shared_ptr<StateBase> getCurrentState() const;
    void setCurrentState(State::_state state);
    void initStates();
};