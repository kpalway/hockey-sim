#ifndef EVENT_HPP
#define EVENT_HPP

class Game;

enum EventType {
  SHOT_ATTEMPT,
  SHOT,
  GOAL,
  PERIOD_END,
  LINE_CHANGE,
  PENALTY,
  PENALTY_END
};

class Event {
public:
  Event(EventType type, Game &game, int period, double time):
    type(type), game(game), period(period), time(time) { }
  virtual ~Event() { }
  virtual void print() = 0;
  virtual void apply();
  EventType Type() { return type; }
protected:
  EventType type;
  Game &game;
  int period;
  double time;
};

#endif // EVENT_HPP
