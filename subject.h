#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;

class Subject
{
  std::vector<shared_ptr<Observer>> observers;

public:
  void attach(shared_ptr<Observer>);
  void notifyObservers();
  virtual ~Subject() = default;
};

#endif
