#ifndef FMODINIT_H
#define FMODINIT_H

#include "fmod.hpp"
#include "fmod_errors.h"

namespace love 
{

	void initFMOD();

	//should be called once per frame
	void updateFMOD();
}

#endif