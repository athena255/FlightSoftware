/** THIS IS AN AUTOGENERATED FILE **/
#ifndef STATE_HISTORY_RATES_HPP_
#define STATE_HISTORY_RATES_HPP_

namespace StateHistory {
namespace Rates {

constexpr unsigned int COLLECTION_PERIOD =
    300000; // Collect five minutes worth of data in buffers
namespace Propulsion {
constexpr unsigned int tank_pressure_history = COLLECTION_PERIOD / 10;
constexpr unsigned int inner_tank_temperature_history = COLLECTION_PERIOD / 10;
constexpr unsigned int outer_tank_temperature_history = COLLECTION_PERIOD / 10;
} // namespace Propulsion
namespace Piksi {
constexpr unsigned int iar_history = COLLECTION_PERIOD / 10;
constexpr unsigned int nsats_history = COLLECTION_PERIOD / 10;
constexpr unsigned int is_float_rtk_history = COLLECTION_PERIOD / 10;
constexpr unsigned int is_fixed_rtk_history = COLLECTION_PERIOD / 10;
constexpr unsigned int recorded_position_history = COLLECTION_PERIOD / 10;
constexpr unsigned int recorded_velocity_history = COLLECTION_PERIOD / 10;
constexpr unsigned int recorded_position_other_history = COLLECTION_PERIOD / 10;
constexpr unsigned int position_history = COLLECTION_PERIOD / 10;
constexpr unsigned int velocity_history = COLLECTION_PERIOD / 10;
constexpr unsigned int position_other_history = COLLECTION_PERIOD / 10;
constexpr unsigned int velocity_other_history = COLLECTION_PERIOD / 10;
} // namespace Piksi
namespace ADCS {
constexpr unsigned int gyro_history = COLLECTION_PERIOD / 10;
constexpr unsigned int gyro_fast_history = COLLECTION_PERIOD / 10;
constexpr unsigned int attitude_cmd_history = COLLECTION_PERIOD / 10;
constexpr unsigned int attitude_history = COLLECTION_PERIOD / 10;
constexpr unsigned int attitude_fast_history = COLLECTION_PERIOD / 10;
constexpr unsigned int rate_history = COLLECTION_PERIOD / 10;
constexpr unsigned int rate_fast_history = COLLECTION_PERIOD / 10;
constexpr unsigned int spacecraft_L_history = COLLECTION_PERIOD / 10;
constexpr unsigned int spacecraft_L_fast_history = COLLECTION_PERIOD / 10;
constexpr unsigned int magnetometer_history = COLLECTION_PERIOD / 10;
constexpr unsigned int rwa_ramp_cmd_history = COLLECTION_PERIOD / 10;
constexpr unsigned int mtr_cmd_history = COLLECTION_PERIOD / 10;
constexpr unsigned int ssa_vector_history = COLLECTION_PERIOD / 10;
} // namespace ADCS

} // namespace Rates
} // namespace StateHistory

#endif