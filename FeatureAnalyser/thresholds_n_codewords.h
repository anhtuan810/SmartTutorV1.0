//
//  Smart Tutor v1.0
//	Feature Analyser
//
//  Created: 2014.08.20
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef THRESHOLDS_H_
#define THRESHOLDS_H_

#include <tuple>

// Store the codebook that contain 14 codewords
enum Codewords
{
	CONTRACTION_LOW = 0,
	CONTRACTION_AVERAGE = 1,
	CONTRACTION_HIGH = 2,

	DIRECTION_FORWARD = 3,
	DIRECTION_BACKWARD = 4,

	DISPLACEMENT_MOVING = 5,
	DISPLACEMENT_NOT_MOVING = 6,

	ENERGY_LOW = 7,
	ENERGY_AVERAGE = 8,
	ENERGY_HIGH = 9,

	IMPULSE = 10,

	STABILITY_LEAN_LEFT = 11,
	STABILITY_LEAN_RIGHT = 12,
	STABILITY_BALANCED = 13
};


// Store the thresholds for the whole module. All thresholds are manually defined
class Thresholds
{
public:
	const int kCodewordsNo = 14;
	Thresholds();
	~Thresholds();
	std::pair<double, double> GetThresholds(Codewords codeword);
protected:
private:
};

#endif