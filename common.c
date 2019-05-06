#include "common.h"

void outb(unsigned short int port, unsigned char value)
{
	asm volatile ("out %0, %1": : "dN" (port), "a" (value));
}

unsigned char inb(unsigned short int port)
{
	unsigned char ret;
	asm volatile ("in %0, %1" : "=a" (ret) : "dN" (port));
	return ret;
}

unsigned short inw(unsigned short int port)
{
	unsigned short int ret;
	asm volatile ("in %0, %1" : "=a" (ret) : "dN"(port));
	return ret;
}

