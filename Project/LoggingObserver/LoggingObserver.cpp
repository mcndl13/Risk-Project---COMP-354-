#include "LoggingObserver.h"

// Subject methods
void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::notify() {
    for (Observer* observer : observers) {
        observer->update(this);
    }
}

// LogObserver methods
LogObserver::LogObserver(const std::string& filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

LogObserver::~LogObserver() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void LogObserver::update(Subject* subject) {
    // Use dynamic_cast to ensure the subject can be cast to ILoggable safely
    ILoggable* loggable = dynamic_cast<ILoggable*>(subject);
    if (logFile.is_open() && loggable != nullptr) {
        logFile << loggable->stringToLog() << std::endl;
    }
}

