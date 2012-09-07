/*========================================================================================================================
 additional needed external funtions ( have to  be provided by the user! )
========================================================================================================================*/

/**
 * set / reset tuner reset input
 * @param i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int setRESETN (unsigned int i_state);



/**
 * set / reset tuner receive enable input
 * @param i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int setRXEN (unsigned int i_state);



/**
 * set / reset tuner chiop enable input
 * @param i_state   level
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int setCEN (unsigned int i_state);



/**
 * waitloop 
 * @param i_looptime   * 1uS
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int waitloop (unsigned int i_looptime);


/**
 * i2cBusWrite 
 * @param deviceAdress    chip address 
 * @param registerAdress  register address 
 * @param *date           pointer to data source
 * @param length          number of bytes to transmit
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int i2cBusWrite (unsigned char deviceAddress, unsigned char registerAddress, char *date, unsigned int length);



/**
 * i2cBusRead 
 * @param deviceAdress    chip address 
 * @param registerAdress  register address 
 * @param *date           pointer to data destination
 * @param length          number of bytes to read
 * @retval TUNER_OK No error
 * @retval TUNER__ERROR Error
*/

int i2cBusRead (unsigned char deviceAddress, unsigned char registerAddress, char *date, unsigned int length);


/*========================================================================================================================
 end of additional needed external funtions
========================================================================================================================*/
