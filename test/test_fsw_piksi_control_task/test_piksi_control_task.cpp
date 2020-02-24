#include "../StateFieldRegistryMock.hpp"
#include "../custom_assertions.hpp"

#include <fsw/FCCode/PiksiControlTask.hpp>
#include <fsw/FCCode/piksi_mode_t.enum>
#include <fsw/FCCode/radio_state_t.enum>

#include <fsw/FCCode/Drivers/Piksi.hpp>
#include <unity.h>

constexpr float nan_d = std::numeric_limits<double>::quiet_NaN();

#define assert_piksi_mode(x) {\
    TEST_ASSERT_EQUAL(x, static_cast<piksi_mode_t>(tf.currentState_fp->get()));\
}

class TestFixture {
    public:
        StateFieldRegistryMock registry;
        std::shared_ptr<WritableStateField<unsigned char>> radio_state_fp;

        // pointers to statefields for easy access
        ReadableStateField<int>* currentState_fp;
        ReadableStateField<d_vector_t>* pos_fp;
        ReadableStateField<d_vector_t>* vel_fp;
        ReadableStateField<d_vector_t>* baseline_fp;
        ReadableStateField<gps_time_t>* time_fp;
        ReadableStateField<unsigned int>* fix_error_count_fp;
        InternalStateField<sys_time_t>* last_fix_time_fp;
        WritableStateField<bool>* data_mute_fp;
        Fault* piksi_fault_fp;

        std::unique_ptr<PiksiControlTask> piksi_task;

        Devices::Piksi piksi;
        
        #ifdef DESKTOP
                #define PIKSI_INITIALIZATION piksi("piksi")
        #else
                #define PIKSI_INITIALIZATION piksi("piksi", Serial4)
        #endif

        // Create a TestFixture instance of PiksiController with pointers to statefields
        TestFixture() : registry(), PIKSI_INITIALIZATION {
                radio_state_fp = registry.create_internal_field<unsigned char>("radio.state");

                // by default, set the state to something that does not interfere with piksi
                radio_state_fp->set(static_cast<unsigned char>(radio_state_t::config));
                piksi_task = std::make_unique<PiksiControlTask>(registry, 0, piksi);  
                piksi_task->init();
                // initialize pointers to statefields      
                currentState_fp = registry.find_readable_field_t<int>("piksi.state");
                pos_fp = registry.find_readable_field_t<d_vector_t>("piksi.pos");
                vel_fp = registry.find_readable_field_t<d_vector_t>("piksi.vel");
                baseline_fp = registry.find_readable_field_t<d_vector_t>("piksi.baseline_pos");
                time_fp = registry.find_readable_field_t<gps_time_t>("piksi.time");
                fix_error_count_fp = registry.find_readable_field_t<unsigned int>("piksi.fix_error_count");
                last_fix_time_fp = registry.find_internal_field_t<sys_time_t>("piksi.last_fix_time");
                data_mute_fp = registry.find_writable_field_t<bool>("piksi.data_mute");

                piksi_fault_fp = static_cast<Fault*>(registry.find_writable_field_t<bool>("piksi.fault"));
        }

        #undef PIKSI_INITIALIZATION

        //method to make calling execute faster
        void execute(){
                piksi_task->execute();
        }

        //set of mocking methods
        void set_read_return(unsigned int read_out){
                piksi_task->piksi.set_read_return(read_out);
        }
        void set_gps_time(const unsigned int tow){
                piksi_task->piksi.set_gps_time(tow);
        }
        void set_pos_ecef(const unsigned int tow, const std::array<double, 3>& position, const unsigned char nsats){
                piksi_task->piksi.set_pos_ecef(tow, position, nsats);
        }
        void set_vel_ecef(const unsigned int tow, const std::array<double, 3>& velocity){
                piksi_task->piksi.set_vel_ecef(tow, velocity);
        }
        void set_baseline_ecef(const unsigned int tow, const std::array<double, 3>& position){
                piksi_task->piksi.set_baseline_ecef(tow, position);
        }
        void set_baseline_flag(const unsigned char flag){
                piksi_task->piksi.set_baseline_flag(flag);
        }
};

//returns the magnitude^2 of a vector 3 of doubles
float mag_2(const std::array<double, 3> input){
        return (float)(input[0]*input[0] + input[1]*input[1] + input[2]*input[2]);
}

void check_nan_set(TestFixture &tf){
    PAN_TEST_ASSERT_EQUAL_DOUBLE_VEC(d_vector_t({nan_d, nan_d, nan_d}).data(), tf.pos_fp->get().data(), 1e-10);
    PAN_TEST_ASSERT_EQUAL_DOUBLE_VEC(d_vector_t({nan_d, nan_d, nan_d}).data(), tf.vel_fp->get().data(), 1e-10);
    PAN_TEST_ASSERT_EQUAL_DOUBLE_VEC(d_vector_t({nan_d, nan_d, nan_d}).data(), tf.baseline_fp->get().data(), 1e-10);

    gps_time_t time = tf.time_fp->get();
    TEST_ASSERT_EQUAL(false, time.is_set);
    TEST_ASSERT_EQUAL(0, time.wn);
    TEST_ASSERT_EQUAL(0, time.tow);
    TEST_ASSERT_EQUAL(0, time.ns);
}

void test_task_initialization()
{
    TestFixture tf;
    assert_piksi_mode(piksi_mode_t::no_fix);
    TEST_ASSERT_TRUE(tf.data_mute_fp->get());
    check_nan_set(tf);
}

void test_read_errors(){
        TestFixture tf;

        //read out == 3 means a CRC error occurred
        tf.set_read_return(3);
        tf.execute();
        assert_piksi_mode(piksi_mode_t::crc_error);
        check_nan_set(tf);

        //read out == 4 means no bytes were in the buffer
        tf.set_read_return(4);
        tf.execute();
        assert_piksi_mode(piksi_mode_t::no_data_error);
        check_nan_set(tf);

        //read out == 5 means we were processing bytes for more than 900 microseconds
        tf.set_read_return(5);
        tf.execute();
        assert_piksi_mode(piksi_mode_t::time_limit_error);
        check_nan_set(tf);

        //not cataloged read_return value
        tf.set_read_return(7);
        tf.execute();
        assert_piksi_mode(piksi_mode_t::data_error);
        check_nan_set(tf);    
}

//normal errors that come up, but don't mean that the piksi has failed
void test_normal_errors(){
        TestFixture tf;

        std::array<double, 3> pos = {1000.0, 2000.0, 3000.0};
        std::array<double, 3> vel = {4000.0, 5000.0, 6000.0};
        std::array<double, 3> baseline = {7000.0, 8000.0, 9000.0};

        //tests to make sure to error out if packets not synced to same tow
        unsigned int tow = 100;
        unsigned int bad_tow = 200;
        tf.set_read_return(1);
        tf.set_gps_time(bad_tow);
        tf.set_pos_ecef(tow, pos, 4);
        tf.set_vel_ecef(tow, vel);
        tf.set_baseline_ecef(tow, baseline);
        tf.set_baseline_flag(1);
        tf.execute();
        //should error out because of time inconsistency
        assert_piksi_mode(piksi_mode_t::sync_error);

        //insufficient nsats
        tow = 200;
        tf.set_read_return(1);
        tf.set_gps_time(tow);
        tf.set_pos_ecef(tow, pos, 3);
        tf.set_vel_ecef(tow, vel);
        tf.set_baseline_ecef(tow, baseline);
        tf.set_baseline_flag(1);
        tf.execute();
        //times agree, but insufficient nsat
        assert_piksi_mode(piksi_mode_t::nsat_error);

        //unexpected baseline flag, should only be 0 or 1
        tow = 200;
        tf.set_read_return(1);
        tf.set_gps_time(tow);
        tf.set_pos_ecef(tow, pos, 4);
        tf.set_vel_ecef(tow, vel);
        tf.set_baseline_ecef(tow, baseline);
        tf.set_baseline_flag(2);
        tf.execute();
        //times agree, but insufficient nsat
        assert_piksi_mode(piksi_mode_t::data_error);
}

//test executions that should yield some sort of fix/lock
void test_task_execute()
{
        TestFixture tf;

        std::array<double, 3> pos = {1000.0, 2000.0, 3000.0};
        std::array<double, 3> vel = {4000.0, 5000.0, 6000.0};
        std::array<double, 3> baseline = {7000.0, 8000.0, 9000.0};

        tf.set_read_return(2);
        tf.execute();
        assert_piksi_mode(piksi_mode_t::no_fix);
        check_nan_set(tf);    

        //fixed RTK
        unsigned int tow = 200;
        tf.set_read_return(1);
        tf.set_gps_time(tow);
        tf.set_pos_ecef(tow, pos, 4);
        tf.set_vel_ecef(tow, vel);
        tf.set_baseline_ecef(tow, baseline);
        tf.set_baseline_flag(1);
        tf.execute();
        //times should now agree, and be in baseline
        assert_piksi_mode(piksi_mode_t::fixed_rtk);
        TEST_ASSERT_TRUE(gps_time_t(0,200,0) == tf.time_fp->get());
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(pos),mag_2(tf.pos_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(vel),mag_2(tf.vel_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(baseline),mag_2(tf.baseline_fp->get()));

        //float RTK
        tow = 300;
        pos = {1200.0, 2200.0, 3200.0};
        vel = {4200.0, 5200.0, 6200.0};
        baseline = {7200.0, 8200.0, 9200.0};

        tf.set_read_return(1);
        tf.set_gps_time(tow);
        tf.set_pos_ecef(tow, pos, 4);
        tf.set_vel_ecef(tow, vel);
        tf.set_baseline_ecef(tow, baseline);
        tf.set_baseline_flag(0);
        tf.execute();
        //float rtk test
        assert_piksi_mode(piksi_mode_t::float_rtk);
        TEST_ASSERT_TRUE(gps_time_t(0,300,0) == tf.time_fp->get());
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(pos),mag_2(tf.pos_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(vel),mag_2(tf.vel_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(baseline),mag_2(tf.baseline_fp->get()));

        //SPP check
        tow = 500;
        pos = {1230.0, 2230.0, 3230.0};
        vel = {4230.0, 5230.0, 6230.0};

        tf.set_read_return(0);
        tf.set_gps_time(tow);
        tf.set_pos_ecef(tow, pos, 4);
        tf.set_vel_ecef(tow, vel);
        tf.execute();
        //check in SPP
        assert_piksi_mode(piksi_mode_t::spp);
        TEST_ASSERT_TRUE(gps_time_t(0,500,0) == tf.time_fp->get());
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(pos),mag_2(tf.pos_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(vel),mag_2(tf.vel_fp->get()));
}

// test to make sure the piksi fault is throwable
void test_fault(){
        TestFixture tf;

        std::array<double, 3> pos = {1000.0, 2000.0, 3000.0};
        std::array<double, 3> vel = {4000.0, 5000.0, 6000.0};
        std::array<double, 3> baseline = {7000.0, 8000.0, 9000.0};  

        //get a good reading from driver
        unsigned int tow = 200;
        tf.set_read_return(1);
        tf.set_gps_time(tow);
        tf.set_pos_ecef(tow, pos, 4);
        tf.set_vel_ecef(tow, vel);
        tf.set_baseline_ecef(tow, baseline);
        tf.set_baseline_flag(1);
        tf.execute();
        //times should now agree, and be in baseline
        assert_piksi_mode(piksi_mode_t::fixed_rtk);
        TEST_ASSERT_TRUE(gps_time_t(0,200,0) == tf.time_fp->get());
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(pos),mag_2(tf.pos_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(vel),mag_2(tf.vel_fp->get()));
        TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(baseline),mag_2(tf.baseline_fp->get()));

        //simulate that the piksi is not sending any data for 1000 control cycles.
        //Make sure that the counter state fields are set correctly.
        tf.set_read_return(4);
        for(int i = 0;i<1000;i++) {
                TimedControlTaskBase::control_cycle_count++;
                tf.execute();
        }
        assert_piksi_mode(piksi_mode_t::no_data_error);
        TEST_ASSERT_FALSE(tf.piksi_fault_fp->is_faulted());

        // one more execution to throw fault
        TimedControlTaskBase::control_cycle_count++;
        tf.execute();
        TEST_ASSERT(tf.piksi_fault_fp->is_faulted());
        assert_piksi_mode(piksi_mode_t::no_data_error);

        // one good execution releases the fault
        tf.set_read_return(1);
        TimedControlTaskBase::control_cycle_count++;
        tf.execute();
        assert_piksi_mode(piksi_mode_t::fixed_rtk);
        TEST_ASSERT_FALSE(tf.piksi_fault_fp->is_faulted());
}

void test_data_mute(){
    TestFixture tf;

    std::array<double, 3> pos = {1000.0, 2000.0, 3000.0};
    std::array<double, 3> vel = {4000.0, 5000.0, 6000.0};
    std::array<double, 3> baseline = {7000.0, 8000.0, 9000.0};  

    unsigned int tow = 200;
    tf.set_read_return(1);
    tf.set_gps_time(tow);
    tf.set_pos_ecef(tow, pos, 4);
    tf.set_vel_ecef(tow, vel);
    tf.set_baseline_ecef(tow, baseline);
    tf.set_baseline_flag(1);
    
    // set the quake mode from last cycle as transceive
    tf.radio_state_fp->set(static_cast<unsigned char>(radio_state_t::transceive));

    tf.execute();
    // times should now agree, and be in baseline
    assert_piksi_mode(piksi_mode_t::fixed_rtk);

    // data is muted
    check_nan_set(tf);

    // relase piksi muting, data is fine even with radio in transceive
    tf.data_mute_fp->set(false);
    tf.execute();
    assert_piksi_mode(piksi_mode_t::fixed_rtk);
    TEST_ASSERT_TRUE(gps_time_t(0,200,0) == tf.time_fp->get());
    TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(pos),mag_2(tf.pos_fp->get()));
    TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(vel),mag_2(tf.vel_fp->get()));
    TEST_ASSERT_FLOAT_WITHIN(0.1,mag_2(baseline),mag_2(tf.baseline_fp->get()));
}
int test_control_task()
{
        UNITY_BEGIN();
        RUN_TEST(test_task_initialization);
        RUN_TEST(test_read_errors);
        RUN_TEST(test_normal_errors);
        RUN_TEST(test_task_execute);
        RUN_TEST(test_fault);
        RUN_TEST(test_data_mute);
        return UNITY_END();
}

#ifdef DESKTOP
int main()
{
        return test_control_task();
}
#else
#include <Arduino.h>
void setup()
{
        delay(2000);
        Serial.begin(9600);
        test_control_task();
}

void loop() {}
#endif