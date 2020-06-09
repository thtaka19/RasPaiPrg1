#ifndef PERI_ADDRESS00_H
#define PERI_ADDRESS00_H

#ifndef RPI23
#define PHY_PERI_ADDR(x) (0x20000000 + (x)) // for Pi Zero , Pi1 or
#else
#define PHY_PERI_ADDR(x) (0x3F000000 + (x))  //for Pi2 , Pi3 
#endif

#endif
