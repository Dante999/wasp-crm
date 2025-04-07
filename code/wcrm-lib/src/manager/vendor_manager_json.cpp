#include "wcrm-lib/manager/vendor_manager_json.hpp"

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

Vendor VendorManagerJson::read_json_file(const std::filesystem::path &filepath)
{
    std::ifstream f(filepath);

    json data = json::parse(f);

    Vendor vendor{data["id"].get<uint64_t>()};

    vendor.created_at = data["created_at"];
    vendor.modfied_at = data["last_modified_at"];

    vendor.name        = get_or_default<std::string>(data, "name", "");
    vendor.description = get_or_default<std::string>(data, "description", "");
    vendor.street      = get_or_default<std::string>(data, "street", "");
    vendor.zip_code    = get_or_default<std::string>(data, "zip_code", "");
    vendor.city        = get_or_default<std::string>(data, "city", "");
    vendor.country     = get_or_default<std::string>(data, "country", "");
    
    vendor.email     = get_or_default<std::string>(data, "email", "");
    vendor.homepage  = get_or_default<std::string>(data, "homepage", "");
    vendor.phone     = get_or_default<std::string>(data, "phone", "");

    return vendor;
}

void VendorManagerJson::do_refresh_list()
{
    SPDLOG_INFO("loading vendors...");

    for(const auto & entry : std::filesystem::directory_iterator(m_vendors_basedir)) {

        m_elements.emplace_back(read_json_file(entry.path()));

        SPDLOG_DEBUG("successfully loaded {}", vendor_filepath.string());
    }
    SPDLOG_INFO("finished loading {} Vendors", m_elements.size());
}

Vendor VendorManagerJson::do_save_element(Vendor vendor)
{

    SPDLOG_INFO("saving vendor {}...", vendor.get_id_as_string());

    const std::string filename                   = vendor.get_id_as_string() + ".json";
    const std::filesystem::path vendor_filepath = m_vendors_basedir / filename;

    vendor.modfied_at = utils::get_current_datetime();

    // clang-format off
    json data = {
        {"id"              , vendor.get_id()},
        {"created_at"      , vendor.created_at},
        {"last_modified_at", vendor.modfied_at},
        {"name"            , vendor.name},
        {"description"     , vendor.description},
        {"street"          , vendor.street},
        {"zip_code"        , vendor.zip_code},
        {"city"            , vendor.city},
        {"country"         , vendor.country},
        {"email"           , vendor.email},
        {"homepage"        , vendor.homepage},
        {"phone"           , vendor.phone},
    };
    // clang-format on

    std::ofstream o(vendor_filepath);
    o << data.dump(4) << std::endl;
    SPDLOG_INFO("successfully saved {}", vendor_filepath.string());

    return vendor;
}
