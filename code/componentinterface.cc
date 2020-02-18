#pragma once
#include "componentinterface.h"

namespace Component
{

ComponentInterface::ComponentInterface()
	: _nextInstanceID(0), _numInstances(0)
{

}

ComponentInterface::~ComponentInterface()
{

}

const Util::StringAtom
ComponentInterface::GetStringID() const
{
	return this->stringID;
}

}