#ifndef VENDOR_MANAGER_JSON_HPP
#define VENDOR_MANAGER_JSON_HPP

#include "manager_interface.hpp"

#include "wcrm-lib/objects/vendor.hpp"

#include <spdlog/spdlog.h>

#include <filesystem>


class VendorManagerJson : public IManager<Vendor> {
    private:
        const std::filesystem::path m_vendors_basedir;

        Vendor read_json_file(const std::filesystem::path &filepath);

        void do_refresh_list() override;
        Vendor do_save_element(Vendor element) override;

    public:
        VendorManagerJson(const std::filesystem::path vendors_basedir) : m_vendors_basedir{vendors_basedir} {
            if (!std::filesystem::exists(m_vendors_basedir)) {
                std::filesystem::create_directories(m_vendors_basedir);
                SPDLOG_INFO("vendors basedir created since it didn't exist: {}", m_vendors_basedir.string());
            }
        }
        ~VendorManagerJson() {}

};

#endif // IARTICLE_MANAGER_HPP
