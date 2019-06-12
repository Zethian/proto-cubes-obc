/*
   obcsim.ino

   Main file for the OBC simulator.
*/

#include "Arduino.h"
#include "msp_obc.h"
#include "SDcard.hpp"
#include "obcsim_configuration.hpp"
#include "RS232.hpp"
#include "RTC.hpp"

#define I2C_SPEED (400L*1000L)
#define I2C_TIMEOUT (100L*1000L)

static msp_link_t exp_link;
static unsigned char exp_buf[EXP_MTU + 5];

/* Arduino Setup */
void setup()
{
  /* Start up debug connection on programming USB port */
  Serial.begin(115200);
  Serial.println("-------------------------");
  Serial.println(" Proto-CUBES OBC started");
  Serial.println("-------------------------");

  /* Create link to the experiment & start I2C */
  exp_link = msp_create_link(EXP_ADDR, msp_seqflags_init(), exp_buf, EXP_MTU);
  msp_i2c_start(I2C_SPEED, I2C_TIMEOUT);

  /* Init RS-232 connection, SD card and RTC */
  RS_init();
  SD_init();
  RTC_init();
}

/* Arduino Loop */
void loop()
{
  static bool initiated = false;

  if (!initiated) {
    sequence_init(&exp_link);
    initiated = true;
  }

  sequence_loop(&exp_link);
  if (Serial2.available()) {
    RS_read(&exp_link);
  }
}
