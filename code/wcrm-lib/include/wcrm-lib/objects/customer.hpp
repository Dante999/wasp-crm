#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include "base_object.hpp"

enum class Gender {
    UNDEFINED,
    MALE,
    FEMALE,
    OTHER
};

static inline const std::string gender_to_string(Gender gender)
{
    switch(gender) {
        case Gender::UNDEFINED : return "undefined";
        case Gender::MALE      : return "male";
        case Gender::FEMALE    : return "female";
        case Gender::OTHER     : return "other";
        default                : return "<?>";
    }
}

static inline Gender gender_from_string(const std::string& gender)
{
    if (gender == "undefined"  ) return Gender::UNDEFINED;
    if (gender == "male"       ) return Gender::MALE;
    if (gender == "female"     ) return Gender::FEMALE;
    if (gender == "other"      ) return Gender::OTHER;

    return Gender::UNDEFINED;
}

struct Customer : public BaseObject {
    Customer(uint64_t id) : BaseObject{id} {}

    std::string get_id_prefix() const override { return "K-"; }

    std::string firstname;
    std::string lastname;
    Gender      gender;
    std::string description;

    std::string street;
    std::string zip_code;
    std::string city;
    std::string country;

    std::string email;
    std::string homepage;
    std::string phone;
};




#endif // CUSTOMER_HPP
