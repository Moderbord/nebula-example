#pragma once
#include "componentinterface.h"

namespace Component
{

ComponentInterface::ComponentInterface()
	: OnBeginFrame(nullptr), OnRender(nullptr), OnEndFrame(nullptr)
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