/*
 * i2clab.cpp
 *
 *  Created on: Oct 19, 2017
 *      Author: rehanashraf
 */

#include <i2clab.h>

    bool i2c_lab::init(void)
    {
    	i2c.initSlave(slaveAddr, data_save_Array,sizeof(data_save_Array));
    	return true;
    }


    bool i2c_lab::run(void *p)
    {
        while(1) {

            uint8_t index = i2c.getregDataIndex(); // Get reg address; aka buffer[reg]

            if(prev_data != data_save_Array[index] /*&& i2c.isThereDataToRead()*/)
            {
            	prev_data = data_save_Array[index];
            }
        }
    	return true;
    }
