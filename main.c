#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "constants.h"
#include "configPins.h"
#include "configLCD.h"
#include "byteToNib.h"
#include "sendNibble.h"
#include "pulse.h"
#include "printAstring.h"

void app_main(void)
{
    configPins();
    configLCD();

   /* uint8_t name[]={"Quad FM4"};
    byteToNib(0x84, LO);
    printAstring(name);

    uint8_t name1[] = {"streamer"};
    byteToNib(0xc4, LO);
    printAstring(name1);*/
    // declare a float to hold temperature
    float temperature = 21.5;
    int16_t t = (int16_t) (10 * temperature); // 21.5 becomes 215
    //split into tens, units, fractions
    int16_t tens  = (t / 100) % 10;  // 2
    int16_t units = (t / 10)  % 10;  // 1
    int16_t frac  = t % 10;          // 5

    printf("tens: %d  units: %d  frac: %d\n", tens, units, frac);

    byteToNib(0x80, LO);// set the instruction register to place the data at line 1 position 0
    byteToNib(tens|0x30, HI);// set the data register to print the decimal number 2 at the position specified above

    byteToNib(0x81, LO);// set the instruction register to place the data at line 1 position 0
    byteToNib(units|0x30, HI);// set the data register to print the decimal number 2 at the position specified above

    byteToNib(0x82, LO);// set the instruction register to place the data at line 1 position 0
    byteToNib(frac|0x30, HI);// set the data register to print the decimal number 2 at the position specified above

    while(1)
    {
        vTaskDelay(250/portTICK_PERIOD_MS);
    }
}