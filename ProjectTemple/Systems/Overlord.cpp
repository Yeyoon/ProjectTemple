///////////////////////////////////////////////////////////////
// Filename:	Overlord.cpp
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#include <Systems\Overlord.h>

using namespace Engine;

Overlord* Overlord::m_instance = 0;
Destroyer<Overlord> Overlord::m_destroyer;

Overlord::Overlord(void)
{
	m_system = NULL;
	m_currentCamera = NULL;
}