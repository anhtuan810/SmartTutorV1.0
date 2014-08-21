//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "thresholds_n_codewords.h"
#include <limits>


Thresholds::Thresholds(){}
Thresholds::~Thresholds(){}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::pair<double, double> Thresholds::GetThresholds(Codewords codeword)
{
	switch (codeword)
	{
	// -----------------------------------------------------------------------------------------------------------------
	case Codewords::CONTRACTION_LOW:
		return std::pair<double, double>(std::numeric_limits<double>::min(), 0.3848);
		break;

	case Codewords::CONTRACTION_AVERAGE:
		return std::pair<double, double>(0.3848, 0.4746);
		break;

	case Codewords::CONTRACTION_HIGH:
		return std::pair<double, double>(0.4746, std::numeric_limits<double>::max());
		break;

	// -----------------------------------------------------------------------------------------------------------------
	case Codewords::DIRECTION_FORWARD:
		return std::pair<double, double>(0, 0);
		break;

	case Codewords::DIRECTION_BACKWARD:
		return std::pair<double, double>(0, 0);
		break;

	// -----------------------------------------------------------------------------------------------------------------
	case Codewords::DISPLACEMENT_MOVING:
		return std::pair<double, double>(0, 0);
		break;

	case Codewords::DISPLACEMENT_NOT_MOVING:
		return std::pair<double, double>(0, 0);
		break;

	// -----------------------------------------------------------------------------------------------------------------
	case Codewords::ENERGY_LOW:
		return std::pair<double, double>(std::numeric_limits<double>::min(), 4.0617);
		break;

	case Codewords::ENERGY_AVERAGE:
		return std::pair<double, double>(4.0617, 6.3438);
		break;

	case Codewords::ENERGY_HIGH:
		return std::pair<double, double>(6.3438, std::numeric_limits<double>::max());
		break;

	// -----------------------------------------------------------------------------------------------------------------
	case Codewords::IMPULSE:
		return std::pair<double, double>(0, 0.0001);
		break;

	// -----------------------------------------------------------------------------------------------------------------
	case Codewords::STABILITY_LEAN_LEFT:
		return std::pair<double, double>(std::numeric_limits<double>::min(), -0.0809);
		break;

	case Codewords::STABILITY_LEAN_RIGHT:
		return std::pair<double, double>(-0.0809, 0.1242);
		break;

	case Codewords::STABILITY_BALANCED:
		return std::pair<double, double>(0.1242, std::numeric_limits<double>::max());
		break;

	// -----------------------------------------------------------------------------------------------------------------
	default:
		return std::pair<double, double>(0, 0);
		break;
	}
}

