#ifndef UPLINK_DESERIALIZER_HPP_
#define UPLINK_DESERIALIZER_HPP_

#include "../state/device_states.hpp"
#include "uplink_struct.hpp"
#include <bitset>

namespace Comms {
void deserialize_uplink(const std::bitset<Comms::UPLINK_SIZE_BITS> &mes,
                        Uplink *uplink);
}

#endif