/** @file device_declarations.cpp
 * @author Tanishq Aggarwal
 * @date 6 Feb 2018
 * @brief Contains definitions for device objects representing devices in the satellite.
 */

#ifndef DEVICE_DECLARATIONS_HPP_
#define DEVICE_DECLARATIONS_HPP_

#include <Device.hpp>
#include <rwmutex.hpp>
#include <map>
#include "state_definitions.hpp"
#include <Gomspace/Gomspace.hpp>
#include <Piksi/Piksi.hpp>
#include <SpikeAndHold/SpikeAndHold.hpp>
#include <QLocate/QLocate.hpp>
#include <ADCS/ADCS.hpp>
#include <Pressure/PressureSensor.hpp>
#include <Temperature/TempSensor.hpp>
#include <DCDC/DCDC.hpp>
#include <DockingMotor/DockingMotor.hpp>
#include <DockingSwitch/DockingSwitch.hpp>

namespace Devices {
    //! Gomspace logical device used by flight controller code
    extern Gomspace gomspace;
    //! Piksi logical device used by flight controller code
    extern Piksi piksi;
    //! Spike and Hold logical device used by flight controller code
    extern SpikeAndHold spike_and_hold;
    //! DCDC logical device used by flight controller code
    extern DCDC dcdc;
    //! Quake logical device used by flight controller code
    extern QLocate quake;
    //! ADCS logical device used by flight controller code
    extern ADCS adcs_system;
    //! Main pressure sensor in outer tank
    extern PressureSensor pressure_sensor;
    //! Temperature sensor in inner tank
    extern TempSensor temp_sensor_inner;
    //! Temperature sensor in outer tank
    extern TempSensor temp_sensor_outer;
    //! Docking motor
    extern DockingMotor docking_motor;
    //! Docking switch
    extern DockingSwitch docking_switch;
}

namespace State {
namespace Hardware {
    //! Maps device names to logical device objects. This is an ordered map, in order to guarantee
    // that the devices are always listed in the same order.
    extern std::map<std::string, Devices::Device&> devices;
    //! Maps device names to their state. This is an ordered map, in order to guarantee
    // that the devices are always listed in the same order.
    extern std::map<std::string, DeviceState&> hat;
    //! Readers-writers lock that prevents multi-process modification of hardware availability table data.
    extern bool is_hardware_setup;
    //! Readers-writers lock that prevents multi-process modification of hardware availability table data.
    extern rwmutex_t hat_lock;

    //! Protects access to DCDC enabling/disabling.
    extern mutex_t dcdc_lock;
    //! Protects access to ADCS device. May be used by master process to rewrite device defaults.
    extern mutex_t adcs_device_lock;
    //! Protects access to Gomspace device. May be used by master process to rewrite device defaults.
    extern mutex_t gomspace_device_lock;
    //! Protects access to propulsion actuation.
    extern mutex_t spike_and_hold_lock;
    //! Protects access to Piksi device. May be used by master process to rewrite device defaults.
    extern mutex_t piksi_device_lock;
    //! Protects access to Quake device. May be used by master process to rewrite device defaults.
    extern mutex_t quake_device_lock;
}

namespace ADCS {
    //! Hardware availability table of devices attached to ADCS.
    extern std::map<std::string, Hardware::DeviceState&> adcs_hat;
}
}

#endif