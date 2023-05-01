#pragma once

#ifndef RING0
#warning "Only ring 0 needs ports.h"
#endif // RING0

#ifdef RING0

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif // RING0