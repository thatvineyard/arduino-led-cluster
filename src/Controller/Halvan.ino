

namespace halvan {

animation::Animation animation = animation::NO_ANIMATION;
filter::Filter filter = filter::OAAT;
int counter = 0;
int red = 255;
int green = 30;
int blue = 0;
int intensity = 0;

void reset() {
  // Swoopy reset
  counter = 0;

  red = 255;
  green = 30;
  blue = 0;

  composer::setFilter(filter::NO_FILTER);
  composer::setMacro(STOP);
  composer::setAnimation(animation::LEFT_TO_RIGHT, false);
  composer::setAnimationSpeed(255);
}

void lightOneAtATime() {
  red = 255;
  green = 30;
  blue = 0;
  filter::setModifier(counter);
  composer::setFilter(filter);

  composer::setParameter(0, red);
  composer::setParameter(1, green);
  composer::setParameter(2, blue);
  composer::setMacro(S_BASECOLOR);

  composer::update();

  Command macro = M_FLICKER;
  composer::setParameter(0, 100);
  composer::setParameter(1, 200);
  composer::setAnimation(animation, false);
  composer::setMacro(macro);

  counter++;
}

void lightNextOneBad() {
  red = 30;
  green = 255;
  blue = 50;
  filter::setModifier(counter);
  composer::setFilter(filter);

  composer::setParameter(0, red);
  composer::setParameter(1, green);
  composer::setParameter(2, blue);
  composer::setMacro(S_BASECOLOR);

  composer::update();

  Command macro = M_PULSE;
  composer::setParameter(0, 100);
  composer::setParameter(1, 10);
  composer::setParameter(2, 50);
  composer::setParameter(3, 100);

  composer::setAnimation(animation, false);
  composer::setMacro(macro);
}

void lightHarryPotterFirst() {
  red = 255;
  green = 30;
  blue = 0;
  composer::setColor(red, green, blue);

  composer::setFilter(filter::NO_FILTER);
  composer::setAnimationForceUpdate(animation::RANDOM_OAAT, false);

  composer::setMacro(M_FLICKER);
  composer::update();
}

void lightHarryPotterSecond() {
  red = 255;
  green = 30;
  blue = 0;
  composer::setColor(red, green, blue);

  composer::setFilter(filter::NO_FILTER);
  composer::setAnimationForceUpdate(animation::RANDOM, false);

  composer::setParameter(0, mapScale(LINEAR, 100, 200, 0, 255, intensity));
  composer::setParameter(1, mapScale(LINEAR, 100, 200, 0, 255, intensity));

  composer::setMacro(M_SINGLEFLASH);
  composer::update();
}

void lightGlassBil() {
  red = 0;
  green = 50;
  blue = 255;
  composer::setColor(red, green, blue);

  composer::setFilter(filter::NO_FILTER);
  composer::setAnimationForceUpdate(animation::RANDOM_OAAT, false);

  composer::setMacro(M_FLICKER);
  composer::update();
}

void setIntensity(int new_intensity) { intensity = new_intensity; }

}  // namespace halvan