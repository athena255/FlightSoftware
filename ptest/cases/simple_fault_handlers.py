from .base import SingleSatOnlyCase
from .utils import FSWEnum, Enums, TestCaseFailure, BootUtil

class ADCSWheelFaultHandler(SingleSatOnlyCase):
    @property
    def initial_state(self):
        return "standby"

    @property
    def fast_boot(self):
        return True

    def setup_post_bootsetup(self):
        self.ws("fault_handler.enabled", True)

    def suppress_adcs_faults(self):
        self.ws("adcs_monitor.wheel1_fault.suppress", True)
        self.ws("adcs_monitor.wheel2_fault.suppress", True)
        self.ws("adcs_monitor.wheel3_fault.suppress", True)
        self.ws("adcs_monitor.wheel_pot_fault.suppress", True)

    def assert_safehold(self):
        if not self.mission_state == "safehold":
            raise TestCaseFailure("Satellite failed to go to safehold after a wheel ADC failure.")
        self.logger.put("Satellite went to safehold.")

    def fail_wheel(self, wheel_no):
        self.logger.put(f"Failing wheel {wheel_no} ADC.")
        self.suppress_adcs_faults()
        self.ws(f"adcs_monitor.wheel{wheel_no}_fault.suppress", False)

        # The Wheel ADCs are failed by default in HOOTL
        self.cycle()
        self.cycle()
        self.assert_safehold()

    def run_case_singlesat(self):
        self.fail_wheel(1)
        self.fail_wheel(2)
        self.fail_wheel(3)

        self.logger.put("Going back to standby, and failing wheel potentiometer.")
        self.suppress_adcs_faults()
        self.ws("adcs_monitor.wheel_pot_fault.suppress", False)
        self.cycle()
        self.cycle()
        self.assert_safehold()

        self.finish()

class LowBattFaultHandler(SingleSatOnlyCase):
    @property
    def sim_duration(self):
        return 0

    @property
    def initial_state(self):
        return "standby"

    @property
    def fast_boot(self):
        return True

    def setup_post_bootsetup(self):
        self.ws("fault_handler.enabled", True)

    def run_case_singlesat(self):
        self.logger.put("Deliberately reducing the Gomspace battery voltage to below the safehold minimum.")
        self.ws("gomspace.low_batt.suppress", False)

        # The Gomspace battery voltage is zero in HOOTL, so after
        # two cycles the fault should be signaled.
        self.cycle()
        self.cycle()

        if not self.mission_state == "safehold":
            raise TestCaseFailure("Satellite failed to go to safehold after a low-battery fault.")

        self.logger.put("Satellite went to safehold.")
        self.finish()
