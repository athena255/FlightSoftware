/** THIS IS AN AUTOGENERATED FILE **/
#ifndef STATE_HISTORY_RATES_HPP_
#define STATE_HISTORY_RATES_HPP_

namespace StateHistory {
namespace Rates {
constexpr unsigned int COLLECTION_PERIOD = 300000; // Collect five minutes worth of data in buffers
namespace Propulsion {
  constexpr unsigned int tank_pressure_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int inner_tank_temperature_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int outer_tank_temperature_history_rate = COLLECTION_PERIOD / 10;
}
namespace Piksi {
  constexpr unsigned int iar_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int nsats_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int is_float_rtk_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int is_fixed_rtk_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int recorded_position_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int recorded_velocity_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int recorded_position_other_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int position_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int velocity_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int position_other_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int velocity_other_history_rate = COLLECTION_PERIOD / 10;
}
namespace ADCS {
  constexpr unsigned int gyro_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int gyro_fast_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int attitude_cmd_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int attitude_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int attitude_fast_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int rate_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int rate_fast_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int spacecraft_L_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int spacecraft_L_fast_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int magnetometer_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int rwa_ramp_cmd_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int mtr_cmd_history_rate = COLLECTION_PERIOD / 10;
  constexpr unsigned int ssa_vector_history_rate = COLLECTION_PERIOD / 10;
}
}
}

#endif