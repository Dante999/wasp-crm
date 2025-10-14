#ifndef INVOICE_MANAGER_JSON_HPP
#define INVOICE_MANAGER_JSON_HPP

#include "manager_interface.hpp"

#include "wcrm-lib/objects/invoice.hpp"

#include <spdlog/spdlog.h>

#include <filesystem>


class InvoiceManagerJson : public IManager<Invoice> {
    private:
        const std::filesystem::path m_invoices_basedir;

        Invoice read_json_file(const std::filesystem::path &filepath);

        void do_refresh_list() override;
        Invoice do_save_element(Invoice element) override;

    public:
        InvoiceManagerJson(const std::filesystem::path invoices_basedir) : m_invoices_basedir{invoices_basedir} {
            if (!std::filesystem::exists(m_invoices_basedir)) {
                std::filesystem::create_directories(m_invoices_basedir);
                SPDLOG_INFO("invoices basedir created since it didn't exist: {}", m_invoices_basedir.string());
            }
        }
        ~InvoiceManagerJson() {}

};

#endif // IARTICLE_MANAGER_HPP
