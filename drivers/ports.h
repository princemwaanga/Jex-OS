/**
 * Read a byte from the specified port
 * //#include "/home/prince/os/os2/drivers/ports.h"
 */
unsigned char port_byte_in (unsigned short port);

void port_byte_out (unsigned short port, unsigned char data);

unsigned short port_word_in (unsigned short port);

void port_word_out (unsigned short port, unsigned short data);
