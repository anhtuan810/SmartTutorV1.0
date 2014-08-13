//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#include "grabber.h"

class Recorder
{
public:
	Recorder();
	~Recorder();
	void SetFileName(char* file_name);
	virtual bool InitiateOrDie() = 0;
	virtual bool StartRecording() = 0;
	virtual void StopRecording() = 0;
	
protected:
	char* file_name_;

private:
};