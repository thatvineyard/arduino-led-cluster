#ifndef FILTER_H_INCLUDED
#define FILTER_H_INCLUDED

#define NUMBER_OF_FILTERS 11

namespace filter {

enum Filter {
  NULL_FILTER = -1,
  NO_FILTER = 0,
  ODD_COLUMNS = 1,
  EVEN_COLUMNS = 2,
  ODD_ROWS = 3,
  EVEN_ROWS = 4,
  CHECKERBOARD = 5,
  LEFT_HALF = 6,
  RIGHT_HALF = 7,
  LEFT_THIRD = 8,
  MIDDLE_THIRD = 9,
  RIGHT_THIRD = 10,
  OAAT = 11
};

String filterToSelector(Filter filter);

String filterToString(Filter filter);

}  // namespace filter

#endif