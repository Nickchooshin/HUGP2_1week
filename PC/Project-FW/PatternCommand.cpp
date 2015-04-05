#include "PatternCommand.h"

CPatternCommand::CPatternCommand() : m_bLife(true)
{
}
CPatternCommand::~CPatternCommand()
{
}

const bool CPatternCommand::BeLife() const
{
	return m_bLife ;
}