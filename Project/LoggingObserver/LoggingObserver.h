#ifndef LOGGING_OBSERVER_H
#define LOGGING_OBSERVER_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

// Forward declarations
class Subject;

// ILoggable interface
class ILoggable {
public:
    virtual std::string stringToLog() const = 0;
    virtual ~ILoggable() = default;
};

// Observer interface
class Observer {
public:
    virtual void update(Subject* subject) = 0;
    virtual ~Observer() = default;
};

// Subject class
class Subject {
    std::vector<Observer*> observers;

public:
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();
    virtual ~Subject() = default;
};

// LogObserver class
class LogObserver : public Observer {
    std::ofstream logFile;

public:
    LogObserver(const std::string& filename);
    ~LogObserver();
    void update(Subject* subject) override;
};

#endif // LOGGING_OBSERVER_H
