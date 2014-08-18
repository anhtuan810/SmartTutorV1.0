//
//  Smart Tutor v1.0
//	Feature Extractor
//
//  Created: 2014.08.15
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_impulse.h"

FeatureImpulse::FeatureImpulse(){};
FeatureImpulse::~FeatureImpulse(){};


//************************************
// Method:    GetImpulseList
// FullName:  FeatureImpulse::GetImpulseList
// Only works with offline processing, on the whole list of energy
// Access:    public 
// Returns:   std::vector<double>
// Qualifier:
// Parameter: std::vector<double> & energy_list
//************************************
std::vector<double> FeatureImpulse::GetImpulseList(std::vector<double> &energy_list)
{
	double* impulse_list = new double(energy_list.size());

	// The constants
	const int kThresQoM = 12500;
	const int kPeriodMin = 3;
	const int kPeriodMax = 25;

	int i = 0;
	while (i < energy_list.size() - 1)
	{
		double energy = energy_list[i];
		if (energy > kThresQoM)
		{
			int id_start = i;
			while (energy_list[i] > kThresQoM)
				i++;
			int id_end = i;
			if (id_end - id_start + 1 > kPeriodMin && id_end - id_start + 1 < kPeriodMax)
			{
				// If contain impulse between id_min and id_max ==> Change values
				double sum = 0;
				for (size_t  k = id_start; k <= id_end; k++)
				{
					sum += energy_list[k];
				}
				double impulse = (double)sum / (id_end - id_start + 1);

				// Assign new value
				for (size_t k = id_start; k <= id_end ; k++)
				{
					impulse_list[k] = impulse;
				}
			}
		}
		i++;
	}

	return std::vector<double>(impulse_list, impulse_list + energy_list.size());
}

