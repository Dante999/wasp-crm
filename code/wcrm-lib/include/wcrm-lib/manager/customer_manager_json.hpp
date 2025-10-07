#ifndef CUSTOMER_MANAGER_JSON_HPP
#define CUSTOMER_MANAGER_JSON_HPP

#include "manager_interface.hpp"

#include "wcrm-lib/objects/customer.hpp"

#include <spdlog/spdlog.h>

#include <filesystem>


class CustomerManagerJson : public IManager<Customer> {
    private:
        const std::filesystem::path m_customers_basedir;

        Customer read_json_file(const std::filesystem::path &filepath);

        void do_refresh_list() override;
        Customer do_save_element(Customer element) override;

    public:
        CustomerManagerJson(const std::filesystem::path customers_basedir) : m_customers_basedir{customers_basedir} {
            if (!std::filesystem::exists(m_customers_basedir)) {
                std::filesystem::create_directories(m_customers_basedir);
                SPDLOG_INFO("customers basedir created since it didn't exist: {}", m_customers_basedir.string());
            }
        }
        ~CustomerManagerJson() {}

};

#endif // CUSTOMER_MANAGER_HPP
