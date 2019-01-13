#include <Arduino.h>

namespace filter {

Filter current_filter;

String filterToSelector(Filter filter) {
  switch (filter) {
    case NO_FILTER:
    default:
      return F(".*");
    case ODD_COLUMNS:
      return F("[BDFHJ]..");
    case EVEN_COLUMNS:
      return F("[ACEGI]..");
    case ODD_ROWS:
      return F("..[13579]");
    case EVEN_ROWS:
      return F("..[02468]");
    case CHECKERBOARD:
      return F(".*");
    case LEFT_HALF:
      return F("[ABCDE]..");
    case RIGHT_HALF:
      return F("[FGHIJ]..");
    case LEFT_THIRD:
      return F("[ABC]..");
    case MIDDLE_THIRD:
      return F("[DEFG]..");
    case RIGHT_THIRD:
      return F("[HIJ]..");
  }
}

String filterToString(Filter filter) {
  switch (filter) {
    case NO_FILTER:
      return F("NO_FILTER");
    case ODD_COLUMNS:
      return F("ODD_COLUMNS");
    case EVEN_COLUMNS:
      return F("EVEN_COLUMNS");
    case ODD_ROWS:
      return F("ODD_ROWS");
    case EVEN_ROWS:
      return F("EVEN_ROWS");
    case CHECKERBOARD:
      return F("CHECKERBOARD");
    case LEFT_HALF:
      return F("LEFT_HALF");
    case RIGHT_HALF:
      return F("RIGHT_HALF");
    case LEFT_THIRD:
      return F("LEFT_THIRD");
    case MIDDLE_THIRD:
      return F("MIDDLE_THIRD");
    case RIGHT_THIRD:
      return F("RIGHT_THIRD");
    default:
      return F("NULL_COMMAND");
  }
}
}  // namespace filter