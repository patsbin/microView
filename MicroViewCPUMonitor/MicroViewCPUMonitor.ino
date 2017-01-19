/*
*	MicroView Arduino Library
*	Copyright (C) 2014 Anubis
*	Instructable: http://www.instructables.com/id/MicroView-CPU-Usage-Temp-Monitor/
*/
#include <MicroView.h>

MicroViewWidget *widget[5];		// declaring an array of 4 MicroViewWidget
// The Setup
void setup()
{
	uView.begin();		// init and start MicroView
	uView.flipHorizontal(true);
	uView.flipVertical(true);
	for(int i = 0;i<5;i++)
	{
		widget[i] = new MicroViewSlider(0, 10*i, 0, 100, WIDGETSTYLE0);
	}
	uView.clear(PAGE);	// erase the memory buffer, when next uView.display() is called, the OLED will be cleared.
	Serial.begin(9600);
	for(int i = 0;i<5;i++)
	{
		widget[i]->reDraw();
	}
}
// validates input value and normalize it if needed
int validate(int val)
{
	if(val > 100)
	{
		val = 100;
	}
	if(val < 0)
	{
		val = 0;
	}
	return val;
}
// retrieves data from serial port
void readSerial() // this is where the input from the serial port is initially processed
{
	if (Serial.available())
	{
		//search for the begin
		if(Serial.read() == 'S')
		{
			// 4xcpu + 1 temp
			for(int i = 0;i<5;i++)
			{
				String val = Serial.readStringUntil(32);
				widget[i]->setValue(validate(val.toInt()));
			}
			uView.display();
		}
	}
}

void loop()
{
	readSerial();
}
