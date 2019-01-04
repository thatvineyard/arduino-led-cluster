#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

/**
 * view
 *
 * This module handles the view of the control panel. This is what keeps track
 * of which view mode is selected, which parameter is being changed.
 */

namespace view {

enum view { MACRO = 0, ANIMATION = 1, FILTER = 2, ANIMATION_SPEED = 3 };

int view_scroll = 0;

int macro_selector = 0;
int parameter_selector = 0;
int animation_selector = 0;
int filter_selector = 0;

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