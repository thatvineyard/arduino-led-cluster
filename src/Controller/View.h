#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

/**
 * view
 *
 * This module handles the view of the control panel. This is what keeps track
 * of which view mode is selected, which parameter is being changed.
 */
#define NUMBER_OF_VIEWS 4

namespace view {
enum View { MACRO = 0, ANIMATION = 1, FILTER = 2, ANIMATION_SPEED = 3 };

byte view_scroll = 0;
byte macro_selector = 0;
byte parameter_selector = 0;
byte animation_selector = 0;
byte filter_selector = 0;

void initView();

// SCROLL
void scrollParameter(bool direction);

void scrollMacro(bool direction);

void scrollAnimation(bool direction);

void scrollFilter(bool direction);

void scrollControl(bool direction);

// CHANGE VALUES
void changeSelectedParameter(int delta);

void changeSelectedControl(int delta);

}  // namespace view

#endif