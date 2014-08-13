//
//  Smart Tutor v1.0
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//

#ifndef GRABBER_H_
#define GRABBER_H_

class Grabber
{
public:
	Grabber();
	~Grabber();
	virtual bool InitiateOrDie() = 0;
	virtual bool TurnOn() = 0;
	virtual void TurnOff() = 0;

protected:	

private:
};

#endif