#ifndef CONTROL_TASK_BASE_HPP_
#define CONTROL_TASK_BASE_HPP_

#include <Nameable.hpp>
#include "debug_console.hpp"

/**
 * @brief Dummy class used so that we can produce generic pointers to
 * ControlTasks.
 */
class ControlTaskBase : public Nameable, public Debuggable {
   protected:
    const std::string _name;
   public:
    ControlTaskBase(const std::string& name) : _name(name) {}
};

#endif