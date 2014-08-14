//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "sensor.h"

Sensor::Sensor(){}

Sensor::~Sensor(){}

SensorState Sensor::GetSensorState()
{
	return sensor_state_;
}
