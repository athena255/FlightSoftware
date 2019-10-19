#include <unity.h>
#include <core_pins.h>
#include <usb_serial.h>
#include <array>
#include "../lib/Drivers/Piksi.hpp"

Devices::Piksi piksi("piksi", Serial4);
int setup_start_time;
int second_time;
int preread_time;

//assume piksi already setup
void test_piksi_fastread_pos() {
    std::array<double, 3> pos = {0};
    Serial.printf("Preread val: %d\n", pos[0]);
    preread_time = millis();
    Serial.println("FAST_POS: Attempting to get solution...");
    
    
    //while (!piksi.process_buffer() || pos[0] == 0) {
    bool keeprun = true;
    int out = -5;
    unsigned int tow = 0;
    piksi.get_pos_ecef(&tow,&pos);
    unsigned int prevtow = tow;
    
    //while (piksi.process_buffer() == SBP_OK || pos[0] ==0 ) {
    while (keeprun || pos[0] ==0 ) {
        out = piksi.process_buffer_i();
        piksi.get_pos_ecef(&tow,&pos);

        delayMicroseconds(1);
        //if(out==SBP_OK_CALLBACK_EXECUTED)
        if(tow!=prevtow)
            keeprun = false;
    }
    Serial.printf("PROCESS BUFF OUT: %hi\n", out );

    Serial.printf("Read time: %d ms\n", millis() - preread_time);
    Serial.printf("GPS position: %lf,%lf,%lf\n", pos[0], pos[1], pos[2]);
    double pos_mag = sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
    TEST_ASSERT_DOUBLE_WITHIN(1E3, 6.37E6, pos_mag); // We're somewhere on Earth.
    //TEST_ASSERT_GREATER_THAN(4, piksi.get_pos_ecef_nsats()); // We need at least 4 satellites to get position.

}

void test_sats(){
    preread_time = millis();

    TEST_ASSERT_GREATER_THAN(4, piksi.get_pos_ecef_nsats()); // We need at least 4 satellites to get position.
    Serial.printf("Num Sats Read Time: %d ms\n", millis() - preread_time);

}

//assume piksi already setup
void test_piksi_fast_vel() {
    preread_time = millis();
    Serial.println("FAST_VEL: Attempting to get solution...");
    
    std::array<double, 3> vel = {0};
        Serial.printf("Preread val: %d\n", vel[0]);

    //while (!piksi.process_buffer() || pos[0] == 0) {
    bool keeprun = true;
    int out = -5;
    //while (piksi.process_buffer() == SBP_OK || pos[0] ==0 ) {
    while (keeprun || vel[0] == 0 ) {
        out = piksi.process_buffer_i();
        delayMicroseconds(1000);
        piksi.get_vel_ecef(&vel);
        if(out==SBP_OK_CALLBACK_EXECUTED)
            keeprun = false;
    }
    Serial.printf("PROCESS BUFF OUT: %i\n", out );

    Serial.printf("Read time: %d ms\n", millis() - preread_time);
    Serial.printf("Vel position: %lf,%lf,%lf\n", vel[0], vel[1], vel[2]);
    double vel_mag = sqrt(vel[0]*vel[0] + vel[1]*vel[1] + vel[2]*vel[2]);
    TEST_ASSERT_DOUBLE_WITHIN(1E3, 3.9E3, vel_mag); // We're fast?
    //TEST_ASSERT_GREATER_THAN(4, piksi.get_pos_ecef_nsats()); // We need at least 4 satellites to get position.

}

void test_piksi_functional() {
    setup_start_time = millis();
    piksi.setup();
    Serial.println("Attempting to get solution...");
    
    std::array<double, 3> pos = {0};
    //while (!piksi.process_buffer() || pos[0] == 0) {
    while (piksi.process_buffer() == SBP_OK || pos[0] ==0 ) {
        delayMicroseconds(1000);
        piksi.get_pos_ecef(&pos);
    };

    Serial.printf("Setup time: %d ms\n", millis() - setup_start_time);
    Serial.printf("GPS position: %lf,%lf,%lf\n", pos[0], pos[1], pos[2]);
    double pos_mag = sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
    TEST_ASSERT_DOUBLE_WITHIN(1E3, 6.37E6, pos_mag); // We're somewhere on Earth.
    //TEST_ASSERT_GREATER_THAN(4, piksi.get_pos_ecef_nsats()); // We need at least 4 satellites to get position.

    // second_time = millis();

    // pos = {0,0,0};
    // //while (!piksi.process_buffer() || pos[0] == 0) {
    // while (piksi.process_buffer() == SBP_OK || pos[0] ==0 ) {
    //     delayMicroseconds(1000);
    //     piksi.get_pos_ecef(&pos);
    // };

    // Serial.printf("Second time: %d ms\n", millis() - second_time);
    // Serial.printf("GPS position: %lf,%lf,%lf\n", pos[0], pos[1], pos[2]);
    // pos_mag = sqrt(pos[0]*pos[0] + pos[1]*pos[1] + pos[2]*pos[2]);
    // TEST_ASSERT_DOUBLE_WITHIN(1E3, 6.37E6, pos_mag); // We're somewhere on Earth.
    // TEST_ASSERT_GREATER_THAN(4, piksi.get_pos_ecef_nsats()); // We need at least 4 satellites to get position.

}

int main(void) {
    delay(5000);
    Serial.begin(9600);
    while (!Serial);
    UNITY_BEGIN();
    //RUN_TEST(test_piksi_functional);
    piksi.setup();
    int weird_delay = 666;
    delay(weird_delay);
    RUN_TEST(test_piksi_fastread_pos);
    delay(weird_delay);
    RUN_TEST(test_piksi_fastread_pos);
    delay(weird_delay);
    RUN_TEST(test_piksi_fastread_pos);
    delay(weird_delay);
    Serial.println("****************************************************");
    RUN_TEST(test_piksi_fast_vel);
    delay(weird_delay);
    RUN_TEST(test_piksi_fast_vel);
    delay(weird_delay);
    RUN_TEST(test_piksi_fast_vel);
    delay(weird_delay);
    RUN_TEST(test_sats);

    delay(weird_delay);
    RUN_TEST(test_sats);
    UNITY_END();
    return 0;
}
