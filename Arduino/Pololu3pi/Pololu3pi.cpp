#include <avr/io.h>
#include "Pololu3pi.h"
#include "../PololuQTRSensors/PololuQTRSensors.h"
#include "../OrangutanAnalog/OrangutanAnalog.h"

// a global qtr sensors
static PololuQTRSensorsRC qtr3pi;

#ifdef LIB_POLOLU

extern "C" void pololu_3pi_init(unsigned int line_sensor_timeout_us)
{
	Pololu3pi::init(line_sensor_timeout_us);
}

extern "C" unsigned int battery_millivolts()
{
	return Pololu3pi::batteryMillivolts();
}

extern "C" void read_line_sensors(unsigned int *sensor_values)
{
	return qtr3pi.read(sensor_values);
}

extern "C" void emitters_on()
{
	qtr3pi.emittersOn();
}

extern "C" void emitters_off()
{
	qtr3pi.emittersOff();
}

extern "C" void calibrate_line_sensors(unsigned char readMode)
{
	qtr3pi.calibrate(readMode);
}

extern "C" void read_line_sensors_calibrated(unsigned int *sensor_values, unsigned char readMode)
{
	qtr3pi.readCalibrated(sensor_values, readMode);
}

extern "C" unsigned int read_line(unsigned int *sensor_values, unsigned char readMode)
{
	return qtr3pi.readLine(sensor_values, 0, readMode);
}

extern "C" unsigned int read_line_white(unsigned int *sensor_values, unsigned char readMode)
{
	return qtr3pi.readLine(sensor_values, 1, readMode);
}

#endif

void Pololu3pi::init(unsigned int line_sensor_timeout_us)
{
	// Set up the line sensor and turn off the emitters.
	// The sensors are on PC0..4, and the emitter is on PC5.
	unsigned char pins[5] = {14,15,16,17,18};
	qtr3pi.init(pins,5,line_sensor_timeout_us,19);
	qtr3pi.emittersOff();
}

void Pololu3pi::readLineSensors(unsigned int *sensor_values, unsigned char readMode)
{
	return qtr3pi.read(sensor_values, readMode);
}

void Pololu3pi::emittersOn()
{
	qtr3pi.emittersOn();
}

void Pololu3pi::emittersOff()
{
	qtr3pi.emittersOff();
}

void Pololu3pi::calibrateLineSensors(unsigned char readMode)
{
	qtr3pi.calibrate(readMode);
}

void Pololu3pi::readLineSensorsCalibrated(unsigned int *sensor_values, unsigned char readMode)
{
	qtr3pi.readCalibrated(sensor_values, readMode);
}

unsigned int Pololu3pi::readLine(unsigned int *sensor_values, unsigned char readMode, unsigned char white_line)
{
	return qtr3pi.readLine(sensor_values, readMode, white_line);
}

unsigned int Pololu3pi::batteryMillivolts()
{
	return OrangutanAnalog::readAverage(6,10)*5000L*3/2/1023;
}

// Local Variables: **
// mode: C++ **
// c-basic-offset: 4 **
// tab-width: 4 **
// indent-tabs-mode: t **
// end: **
