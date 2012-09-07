//---------------------------------------------------------------------------

#ifndef i2c_driverH
#define i2c_driverH

// Sends data bytes to xc4000 via I2C starting with
// bytes_to_send[0] and ending with bytes_to_send[nb_bytes_to_send-1]
int xc_send_i2c_data(unsigned char *bytes_to_send, int nb_bytes_to_send);

// Reads data bytes from xc4000 via I2C starting with
// bytes_received[0] and ending with bytes_received[nb_bytes_to_receive-1]
int xc_read_i2c_data(unsigned char *bytes_received, int nb_bytes_to_receive);

// Does hardware reset
int xc_reset();

// Waits for wait_ms milliseconds
void xc_wait(int wait_ms);

//---------------------------------------------------------------------------
#endif
