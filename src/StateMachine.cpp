#include "StateMachine.hpp"
#include "StateWaitStart.hpp"
#include "StateGameStarted.hpp"
#include "StateGameEnd.hpp"

StateMachine::StateMachine()
{
    initStates();
}

std::shared_ptr<StateBase> StateMachine::getCurrentState() const
{
    return currentState;
}

void StateMachine::setCurrentState(State::_state state)
{
    currentState = allStates[state];
}

void StateMachine::initStates()
{
    allStates[State::WaitStart] = std::make_shared<StateWaitStart>();
    allStates[State::GameEnd] = std::make_shared<StateGameEnd>();
    allStates[State::GameStarted] = std::make_shared<StateGameStarted>();

    setCurrentState(State::WaitStart);
}


