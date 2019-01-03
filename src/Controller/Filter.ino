#include <Arduino.h>

Filter current_filter;

String filterToSelector(Filter filter) {
  switch (filter) {
    case NO_FILTER:
    default:
      return ".*";
      break;
    case ODD_COLUMNS:
      return ".*";
      break;
    case EVEN_COLUMNS:
      return ".*";
      break;
    case ODD_ROWS:
      return ".*";
      break;
    case EVEN_ROWS:
      return ".*";
      break;
    case CHECKERBOARD:
      return ".*";
      break;
    case LEFT_HALF:
      return ".*";
      break;
    case RIGHT_HALF:
      return ".*";
      break;
    case LEFT_THIRD:
      return ".*";
      break;
    case MIDDLE_THIRD:
      return ".*";
      break;
    case RIGHT_THIRD:
      return ".*";
      break;
  }
}