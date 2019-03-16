/** THIS IS AN AUTOGENERATED FILE **/
#include "uplink_deserializer.hpp"
#include <comms_utils.hpp>

void Comms::deserialize_uplink(const std::bitset<Comms::UPLINK_SIZE_BITS>& mes, Comms::Uplink* uplink) {
  unsigned int bitset_ptr = 0;
  std::bitset<32> bitset_0;
  for(int i = 0; i < 32; i++) bitset_0.set(i, mes[bitset_ptr++]);
  uplink->uplink_number = Comms::expand_int(bitset_0, 0, 4294967295);

  std::bitset<49> bitset_1;
  for(int i = 0; i < 49; i++) bitset_1.set(i, mes[bitset_ptr++]);
  Comms::expand_gps_time(bitset_1, &(uplink->uplink_timestamp));

  std::bitset<45> bitset_2;
  for(int i = 0; i < 45; i++) bitset_2.set(i, mes[bitset_ptr++]);
  Comms::expand_vector(bitset_2, 6400, 7200, &(uplink->other_satellite_position));

  std::bitset<45> bitset_3;
  for(int i = 0; i < 45; i++) bitset_3.set(i, mes[bitset_ptr++]);
  Comms::expand_vector(bitset_3, 8000, 12000, &(uplink->other_satellite_velocity));

  std::bitset<49> bitset_4;
  for(int i = 0; i < 49; i++) bitset_4.set(i, mes[bitset_ptr++]);
  Comms::expand_gps_time(bitset_4, &(uplink->other_satellite_timestamp));

  std::bitset<5> bitset_5;
  for(int i = 0; i < 5; i++) bitset_5.set(i, mes[bitset_ptr++]);
  uplink->constant_0_id = Comms::expand_int(bitset_5, 1, 19);

  std::bitset<32> bitset_6;
  for(int i = 0; i < 32; i++) bitset_6.set(i, mes[bitset_ptr++]);
  uplink->constant_0_val = Comms::expand_int(bitset_6, 0, 4294967295);

  std::bitset<5> bitset_7;
  for(int i = 0; i < 5; i++) bitset_7.set(i, mes[bitset_ptr++]);
  uplink->constant_1_id = Comms::expand_int(bitset_7, 1, 19);

  std::bitset<32> bitset_8;
  for(int i = 0; i < 32; i++) bitset_8.set(i, mes[bitset_ptr++]);
  uplink->constant_1_val = Comms::expand_int(bitset_8, 0, 4294967295);

  std::bitset<5> bitset_9;
  for(int i = 0; i < 5; i++) bitset_9.set(i, mes[bitset_ptr++]);
  uplink->constant_2_id = Comms::expand_int(bitset_9, 1, 19);

  std::bitset<32> bitset_10;
  for(int i = 0; i < 32; i++) bitset_10.set(i, mes[bitset_ptr++]);
  uplink->constant_2_val = Comms::expand_int(bitset_10, 0, 4294967295);

  std::bitset<5> bitset_11;
  for(int i = 0; i < 5; i++) bitset_11.set(i, mes[bitset_ptr++]);
  uplink->constant_3_id = Comms::expand_int(bitset_11, 1, 19);

  std::bitset<32> bitset_12;
  for(int i = 0; i < 32; i++) bitset_12.set(i, mes[bitset_ptr++]);
  uplink->constant_3_val = Comms::expand_int(bitset_12, 0, 4294967295);

  std::bitset<5> bitset_13;
  for(int i = 0; i < 5; i++) bitset_13.set(i, mes[bitset_ptr++]);
  uplink->constant_4_id = Comms::expand_int(bitset_13, 1, 19);

  std::bitset<32> bitset_14;
  for(int i = 0; i < 32; i++) bitset_14.set(i, mes[bitset_ptr++]);
  uplink->constant_4_val = Comms::expand_int(bitset_14, 0, 4294967295);

  std::bitset<3> bitset_15;
  for(int i = 0; i < 3; i++) bitset_15.set(i, mes[bitset_ptr++]);
  uplink->master_state = Comms::expand_int(bitset_15, 0, 4);

  std::bitset<4> bitset_16;
  for(int i = 0; i < 4; i++) bitset_16.set(i, mes[bitset_ptr++]);
  uplink->pan_state = Comms::expand_int(bitset_16, 0, 11);

  std::bitset<1> bitset_17;
  for(int i = 0; i < 1; i++) bitset_17.set(i, mes[bitset_ptr++]);
  uplink->is_follower = bitset_17[0];

  std::bitset<1> bitset_18;
  for(int i = 0; i < 1; i++) bitset_18.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_gomspace = bitset_18[0];

  std::bitset<1> bitset_19;
  for(int i = 0; i < 1; i++) bitset_19.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_piksi = bitset_19[0];

  std::bitset<1> bitset_20;
  for(int i = 0; i < 1; i++) bitset_20.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_quake = bitset_20[0];

  std::bitset<1> bitset_21;
  for(int i = 0; i < 1; i++) bitset_21.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_dcdc = bitset_21[0];

  std::bitset<1> bitset_22;
  for(int i = 0; i < 1; i++) bitset_22.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_spike_and_hold = bitset_22[0];

  std::bitset<1> bitset_23;
  for(int i = 0; i < 1; i++) bitset_23.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_adcs_system = bitset_23[0];

  std::bitset<1> bitset_24;
  for(int i = 0; i < 1; i++) bitset_24.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_pressure_sensor = bitset_24[0];

  std::bitset<1> bitset_25;
  for(int i = 0; i < 1; i++) bitset_25.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_temp_sensor_inner = bitset_25[0];

  std::bitset<1> bitset_26;
  for(int i = 0; i < 1; i++) bitset_26.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_temp_sensor_outer = bitset_26[0];

  std::bitset<1> bitset_27;
  for(int i = 0; i < 1; i++) bitset_27.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_docking_motor = bitset_27[0];

  std::bitset<1> bitset_28;
  for(int i = 0; i < 1; i++) bitset_28.set(i, mes[bitset_ptr++]);
  uplink->fc_hat_docking_switch = bitset_28[0];

  std::bitset<1> bitset_29;
  for(int i = 0; i < 1; i++) bitset_29.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_gyroscope = bitset_29[0];

  std::bitset<1> bitset_30;
  for(int i = 0; i < 1; i++) bitset_30.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_magnetometer = bitset_30[0];

  std::bitset<1> bitset_31;
  for(int i = 0; i < 1; i++) bitset_31.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_magnetorquer_x = bitset_31[0];

  std::bitset<1> bitset_32;
  for(int i = 0; i < 1; i++) bitset_32.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_magnetorquer_y = bitset_32[0];

  std::bitset<1> bitset_33;
  for(int i = 0; i < 1; i++) bitset_33.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_magnetorquer_z = bitset_33[0];

  std::bitset<1> bitset_34;
  for(int i = 0; i < 1; i++) bitset_34.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motorpot = bitset_34[0];

  std::bitset<1> bitset_35;
  for(int i = 0; i < 1; i++) bitset_35.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motor_x = bitset_35[0];

  std::bitset<1> bitset_36;
  for(int i = 0; i < 1; i++) bitset_36.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motor_y = bitset_36[0];

  std::bitset<1> bitset_37;
  for(int i = 0; i < 1; i++) bitset_37.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motor_z = bitset_37[0];

  std::bitset<1> bitset_38;
  for(int i = 0; i < 1; i++) bitset_38.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motor_x_adc = bitset_38[0];

  std::bitset<1> bitset_39;
  for(int i = 0; i < 1; i++) bitset_39.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motor_y_adc = bitset_39[0];

  std::bitset<1> bitset_40;
  for(int i = 0; i < 1; i++) bitset_40.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_motor_z_adc = bitset_40[0];

  std::bitset<1> bitset_41;
  for(int i = 0; i < 1; i++) bitset_41.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_ssa_adc_1 = bitset_41[0];

  std::bitset<1> bitset_42;
  for(int i = 0; i < 1; i++) bitset_42.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_ssa_adc_2 = bitset_42[0];

  std::bitset<1> bitset_43;
  for(int i = 0; i < 1; i++) bitset_43.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_ssa_adc_3 = bitset_43[0];

  std::bitset<1> bitset_44;
  for(int i = 0; i < 1; i++) bitset_44.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_ssa_adc_4 = bitset_44[0];

  std::bitset<1> bitset_45;
  for(int i = 0; i < 1; i++) bitset_45.set(i, mes[bitset_ptr++]);
  uplink->adcs_hat_ssa_adc_5 = bitset_45[0];

  std::bitset<2> bitset_46;
  for(int i = 0; i < 2; i++) bitset_46.set(i, mes[bitset_ptr++]);
  uplink->adcs_state = Comms::expand_int(bitset_46, 0, 3);

  std::bitset<1> bitset_47;
  for(int i = 0; i < 1; i++) bitset_47.set(i, mes[bitset_ptr++]);
  uplink->command_adcs = bitset_47[0];

  std::bitset<2> bitset_48;
  for(int i = 0; i < 2; i++) bitset_48.set(i, mes[bitset_ptr++]);
  uplink->adcs_frame = Comms::expand_int(bitset_48, 0, 3);

  std::bitset<29> bitset_49;
  for(int i = 0; i < 29; i++) bitset_49.set(i, mes[bitset_ptr++]);
  Comms::expand_quaternion(bitset_49, &(uplink->adcs_attitude));

  std::bitset<1> bitset_50;
  for(int i = 0; i < 1; i++) bitset_50.set(i, mes[bitset_ptr++]);
  uplink->command_propulsion = bitset_50[0];

  std::bitset<26> bitset_51;
  for(int i = 0; i < 26; i++) bitset_51.set(i, mes[bitset_ptr++]);
  Comms::expand_vector(bitset_51, 0, 0.005, &(uplink->firing_vector));

  std::bitset<49> bitset_52;
  for(int i = 0; i < 49; i++) bitset_52.set(i, mes[bitset_ptr++]);
  Comms::expand_gps_time(bitset_52, &(uplink->firing_time));

  std::bitset<1> bitset_53;
  for(int i = 0; i < 1; i++) bitset_53.set(i, mes[bitset_ptr++]);
  uplink->docking_motor_mode = bitset_53[0];

  std::bitset<1> bitset_54;
  for(int i = 0; i < 1; i++) bitset_54.set(i, mes[bitset_ptr++]);
  uplink->reset_piksi = bitset_54[0];

  std::bitset<1> bitset_55;
  for(int i = 0; i < 1; i++) bitset_55.set(i, mes[bitset_ptr++]);
  uplink->reset_quake = bitset_55[0];

  std::bitset<1> bitset_56;
  for(int i = 0; i < 1; i++) bitset_56.set(i, mes[bitset_ptr++]);
  uplink->reset_dcdc = bitset_56[0];

  std::bitset<1> bitset_57;
  for(int i = 0; i < 1; i++) bitset_57.set(i, mes[bitset_ptr++]);
  uplink->reset_spike_and_hold = bitset_57[0];

  std::bitset<1> bitset_58;
  for(int i = 0; i < 1; i++) bitset_58.set(i, mes[bitset_ptr++]);
  uplink->power_cycle_gomspace = bitset_58[0];

  std::bitset<1> bitset_59;
  for(int i = 0; i < 1; i++) bitset_59.set(i, mes[bitset_ptr++]);
  uplink->power_cycle_piksi = bitset_59[0];

  std::bitset<1> bitset_60;
  for(int i = 0; i < 1; i++) bitset_60.set(i, mes[bitset_ptr++]);
  uplink->power_cycle_quake = bitset_60[0];

  std::bitset<1> bitset_61;
  for(int i = 0; i < 1; i++) bitset_61.set(i, mes[bitset_ptr++]);
  uplink->power_cycle_adcs_system = bitset_61[0];

  std::bitset<1> bitset_62;
  for(int i = 0; i < 1; i++) bitset_62.set(i, mes[bitset_ptr++]);
  uplink->power_cycle_spike_and_hold = bitset_62[0];

}