/*
 * i2clab.h
 *
 *  Created on: Oct 19, 2017
 *      Author: rehanashraf
 */

#ifndef L5_APPLICATION_I2CLAB_H_
#define L5_APPLICATION_I2CLAB_H_

#include "tasks.hpp"
#include "examples/examples.hpp"
#include "stdio.h"
#include "printf_lib.h"     // u0_dbg_printf()
#include "i2c2.hpp"

class i2c_lab :  public scheduler_task {
public:
	i2c_lab(): scheduler_task("i2c", 2000, PRIORITY_LOW) { /* constructor code */ };

    bool init(void);
    bool run(void *p);

private:
    I2C2 &i2c = I2C2::getInstance();		//get the instance of the i2c bus using singleton pattern
    const uint8_t slaveAddr = 0x66;         // Set Slave address to 0x66;

    uint8_t data_save_Array[128] = {0};     // Array of 128/buffer for our data
    uint8_t prev_data = data_save_Array[0];

};

#endif /* L5_APPLICATION_I2CLAB_H_ */
