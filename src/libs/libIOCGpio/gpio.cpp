#include "gpio.h"
#include <filesystem>

#include <QLoggingCategory>
Q_LOGGING_CATEGORY(DBG_GPIO, "IOC.Gpio", QtInfoMsg)


const std::unordered_map<std::string, ::gpiod::line> Gpio::namedGpioLines_ {Gpio::getNamedLines()};

Gpio::Gpio(const std::string& name, const bool activateLow)
    : QObject{}
    , gpiodLine_{getNamedGpioLine(name)}
{
    qCDebug(DBG_GPIO) << "name:" << gpiodLine_.name().c_str() << ", active low:" << (gpiodLine_.active_state() == ::gpiod::line::ACTIVE_LOW);

    gpiodLine_.request({
        "IOC",
        ::gpiod::line_request::DIRECTION_OUTPUT,
        activateLow ? ::gpiod::line_request::FLAG_ACTIVE_LOW : 0
    });
}

Gpio::~Gpio()
{
    gpiodLine_.release();
}

void Gpio::set(bool state)
{
    qCDebug(DBG_GPIO) << "name:" << gpiodLine_.name().c_str() << "state:" << state;

    gpiodLine_.set_value(state ? 1 : 0);
}

bool Gpio::get()
{
    return gpiodLine_.get_value() == 1;
}

std::unordered_map<std::string, gpiod::line> Gpio::getNamedLines()
{
    std::unordered_map<std::string, ::gpiod::line > result;

    for (const auto& cit: ::gpiod::make_chip_iter())
    {
        qCDebug(DBG_GPIO) << "GPIO: " << cit.name().c_str() << " - number of lines:" << cit.num_lines();
        for (const auto& lit: ::gpiod::line_iter(cit))
        {
            qCDebug(DBG_GPIO)
                << lit.offset() << ":"
                << (lit.name().empty() ? "unnamed" : lit.name().c_str()) << " "
                << (lit.consumer().empty() ? "no consumer" : lit.consumer().c_str()) << " "
                << (lit.direction() == ::gpiod::line::DIRECTION_INPUT ? "input" : "output") << " "
                << (lit.active_state() == ::gpiod::line::ACTIVE_LOW
                        ? "active-low" : "active-high") << " ";

            if(!lit.name().empty())
            {
                result[lit.name()] = lit;
            }
        }
    }
    return result;
}

gpiod::line Gpio::getNamedGpioLine(const std::string &name)
{
    if(const auto it = Gpio::namedGpioLines_.find(name); it == Gpio::namedGpioLines_.end())
    {
        qFatal("GPIO line not found: %s", name.c_str());
        return gpiod::line();
    }
    else
    {
        return it->second;
    }
}
