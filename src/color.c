#include <stdio.h>
#include "color.h"



const char* color_to_string(enum color_t c) {
  switch (c) {
  case BLUE :  return "BLUE";
    break;
  case RED :  return "RED";
    break;
  case GREEN :  return "GREEN";
    break;
  case YELLOW :  return "YELLOW";
    break;
  case ORANGE :  return "ORANGE";
    break;
  case VIOLET :  return "VIOLET";
    break;
  case CYAN :  return "CYAN";
    break;
  case PINK :  return "PINK";
    break;
  case MAX_COLOR :  return "MAX_COLOR";
    break;
  case NO_COLOR :  return "NO_COLOR";
    break;
  }
  return "Error";
}

