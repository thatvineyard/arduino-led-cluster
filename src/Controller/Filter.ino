#include <Arduino.h>

namespace filter {

Filter current_filter;

String filterToSelector(Filter filter) {
  switch (filter) {
    case NO_FILTER:
    default:
      return ".*";
    case ODD_COLUMNS:
      return "[BDFHJ]..";
    case EVEN_COLUMNS:
      return "[ACEGI]..";
    case ODD_ROWS:
      return "..[13579]";
    case EVEN_ROWS:
      return "..[02468]";
    case CHECKERBOARD:
      return ".*";
    case LEFT_HALF:
      return "[ABCDE]..";
    case RIGHT_HALF:
      return "[FGHIJ]..";
    case LEFT_THIRD:
      return "[ABC]..";
    case MIDDLE_THIRD:
      return "[DEFG]..";
    case RIGHT_THIRD:
      return "[HIJ]..";
  }
}

String filterToString(Filter filter) {
  switch (filter) {
    case NO_FILTER:
      return "NO_FILTER";
    case ODD_COLUMNS:
      return "ODD_COLUMNS";
    case EVEN_COLUMNS:
      return "EVEN_COLUMNS";
    case ODD_ROWS:
      return "ODD_ROWS";
    case EVEN_ROWS:
      return "EVEN_ROWS";
    case CHECKERBOARD:
      return "CHECKERBOARD";
    case LEFT_HALF:
      return "LEFT_HALF";
    case RIGHT_HALF:
      return "RIGHT_HALF";
    case LEFT_THIRD:
      return "LEFT_THIRD";
    case MIDDLE_THIRD:
      return "MIDDLE_THIRD";
    case RIGHT_THIRD:
      return "RIGHT_THIRD";
    default:
      return "NULL_COMMAND";
  }
}
}  // namespace filter