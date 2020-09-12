#pragma once

#include <boost/filesystem.hpp>

namespace components {

    enum class operating_mode : std::uint8_t {
        master,
        worker
    };

    struct configuration final {
        configuration() = default;
        operating_mode operating_mode_;
        unsigned short int port_http_;
    };

} // namespace rocketjoe