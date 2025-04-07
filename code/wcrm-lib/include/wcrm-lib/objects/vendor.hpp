#ifndef VENDOR_HPP
#define VENDOR_HPP

#include "base_object.hpp"

struct Vendor : public BaseObject {
    Vendor(uint64_t id) : BaseObject{id} {}

    std::string get_id_prefix() const override { return "L-"; }

    std::string name;
    std::string description;

    std::string street;
    std::string zip_code;
    std::string city;
    std::string country;

    std::string email;
    std::string homepage;
    std::string phone;
};




#endif // VENDOR_HPP
