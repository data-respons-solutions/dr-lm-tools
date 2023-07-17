#ifndef GPIO_H
#define GPIO_H

#include <QObject>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <gpiod.hpp>

class Gpio : public QObject
{
    Q_OBJECT

public:
    explicit Gpio(const std::string& name, const bool activateLow);
    ~Gpio();

    void set(bool state);
    bool get();

private:
    static const std::unordered_map<std::string, ::gpiod::line> namedGpioLines_;
    static std::unordered_map<std::string, ::gpiod::line> getNamedLines();
    ::gpiod::line gpiodLine_;
    static ::gpiod::line getNamedGpioLine(const std::string& name);
};

#endif // GPIO_H
