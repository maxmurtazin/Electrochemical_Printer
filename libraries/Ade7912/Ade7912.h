/*

 *
 * How to use:
 * Read well documented tutorial on how to use evive sensing here: 
 * Function List:
 * 1) ade791x_init() : initialize the ADE7912 IC to communicate over SPI communication with microcontroller ATmega2560
 * 2) long ade791x_read_v1() : returns the voltage sensed between the Probe V and COM (or on the Graph port between the Right Pin and Center Pin (COM))
 * 3) long ade791x_read_vim() : returns the voltage sensed between the Probe I/V and COM (or on the Graph port between the Left Pin and Center Pin (COM))
 * 4) long ade791x_read_im(): NOTE: Put the JP2 Jumper of I or V (Blue) on the I side for sensing current. This function returns the current sensed 
 *    between the Probe I/V and COM (or on the Graph port between the Right Pin and Center Pin (COM))
 *
 */

#ifndef ADE7912_H_
#define ADE7912_H_



#ifndef ADE7911X_REG_IWV
#define ADE791X_REG_IWV            0x00    /* Instantaneous value of Current I. */
#define ADE791X_REG_V1WV           0x01    /* Instantaneous value of Voltage V1 */
#define ADE791X_REG_V2WV           0x02    /* Instantaneous value of Voltage V2 */
//For V1WV 5,320,000 reading = 34.5V  (Multiplier = 0.006485) mV
#define ADE791X_MUL_V1WV           0.006485
//For V2WV 5,320,000Num reading = 6.3315V (Multiplier = 0.0011901) mV
#define ADE791X_MUL_VIMWV          0.0011901
//For IWV 5,320,000 reading = 3.15A (Multiplier = 0.0005921) mA
#define ADE791X_MUL_IWV            0.0005921
#define ADE791X_OFFSET_V1WV          363378      //387161;   //Adjust
#define ADE791X_OFFSET_VIMWV         369226                  //Adjust  
#define ADE791X_OFFSET_IWV           355000     //369226;   //Adjust
#endif

void ade791x_init(void);
long ade791x_read_v1(void);
long ade791x_read_vim(void);
long ade791x_read_im(void);

#endif /* ADE7912_H_ */