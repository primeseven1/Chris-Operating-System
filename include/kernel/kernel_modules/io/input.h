#pragma once

#ifndef RING0
#warning "Only ring 0 needs input.h"
#endif // RING0

#ifdef RING0

char getKeyChar();

#endif // RING0