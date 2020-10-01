#pragma once

#include <boost/filesystem.hpp>

namespace components {

    enum class operating_mode : std::uint8_t {
        master = 0x00,
        worker
    };

    struct configuration final {
        configuration() {
            operating_mode_ = operating_mode::master;
        }

        operating_mode operating_mode_;
        unsigned short int port_http_;
    };

} // namespace cosmoport