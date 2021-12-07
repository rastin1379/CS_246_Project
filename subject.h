#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>

class Observer;

class Subject
{
  std::vector<Observer *> observers;

public:
  void attach(Observer *);
  void detach(Observer *);
  void notifyObservers();
  virtual ~Subject() = default;
};

#endif
