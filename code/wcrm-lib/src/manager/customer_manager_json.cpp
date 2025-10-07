#include "wcrm-lib/manager/customer_manager_json.hpp"

// std
#include <algorithm>
#include <fstream>

// thirdparty
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "utils/filesystem_utils.hpp"
#include "utils/string_utils.hpp"

using json = nlohmann::json;


template<typename T>
T get_or_default(json &data, const std::string& name, T default_value)
{
    if (data.contains(name)) {
        return data[name].get<T>();
    }
    else {
        return default_value;
    }
}

Customer CustomerManagerJson::read_json_file(const std::filesystem::path &filepath)
{
    std::ifstream f(filepath);

    json data = json::parse(f);

    Customer customer{data["id"].get<uint64_t>()};

    customer.created_at = data["created_at"];
    customer.modfied_at = data["last_modified_at"];

    customer.firstname   = get_or_default<std::string>(data, "firstname", "");
    customer.lastname    = get_or_default<std::string>(data, "lastname", "");
    customer.gender      = gender_from_string(get_or_default<std::string>(data, "gender", "undefined"));
    customer.description = get_or_default<std::string>(data, "description", "");
    customer.street      = get_or_default<std::string>(data, "street", "");
    customer.zip_code    = get_or_default<std::string>(data, "zip_code", "");
    customer.city        = get_or_default<std::string>(data, "city", "");
    customer.country     = get_or_default<std::string>(data, "country", "");

    customer.email     = get_or_default<std::string>(data, "email", "");
    customer.homepage  = get_or_default<std::string>(data, "homepage", "");
    customer.phone     = get_or_default<std::string>(data, "phone", "");

    return customer;
}

void CustomerManagerJson::do_refresh_list()
{
    SPDLOG_INFO("loading customers...");

    for(const auto & entry : std::filesystem::directory_iterator(m_customers_basedir)) {

        m_elements.emplace_back(read_json_file(entry.path()));

        SPDLOG_DEBUG("successfully loaded {}", customer_filepath.string());
    }
    SPDLOG_INFO("finished loading {} Customers", m_elements.size());
}

Customer CustomerManagerJson::do_save_element(Customer customer)
{

    SPDLOG_INFO("saving customer {}...", customer.get_id_as_string());

    const std::string filename                   = customer.get_id_as_string() + ".json";
    const std::filesystem::path customer_filepath = m_customers_basedir / filename;

    customer.modfied_at = utils::get_current_datetime();

    // clang-format off
    json data = {
        {"_version"        , 1},
        {"id"              , customer.get_id()},
        {"created_at"      , customer.created_at},
        {"last_modified_at", customer.modfied_at},
        {"firstname"       , customer.firstname},
        {"lastname"        , customer.lastname},
        {"gender"          , gender_to_string(customer.gender)},
        {"description"     , customer.description},
        {"street"          , customer.street},
        {"zip_code"        , customer.zip_code},
        {"city"            , customer.city},
        {"country"         , customer.country},
        {"email"           , customer.email},
        {"homepage"        , customer.homepage},
        {"phone"           , customer.phone},
    };
    // clang-format on

    std::ofstream o(customer_filepath);
    o << data.dump(4) << std::endl;
    SPDLOG_INFO("successfully saved {}", customer_filepath.string());

    return customer;
}
