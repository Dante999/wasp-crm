#include "wcrm-lib/manager/invoice_manager_json.hpp"

// std
#include <algorithm>
#include <cstdlib>
#include <fstream>

// thirdparty
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "utils/filesystem_utils.hpp"
#include "utils/string_utils.hpp"

using json = nlohmann::json;

template <typename T>
T get_or_default(json &data, const std::string &name, T default_value)
{
    if (data.contains(name)) {
        return data[name].get<T>();
    }
    else {
        return default_value;
    }
}

Invoice InvoiceManagerJson::read_json_file(const std::filesystem::path &filepath)
{
    std::ifstream f(filepath);

    json data = json::parse(f);

    Invoice invoice{data["id"].get<uint64_t>()};

    invoice.created_at = data["created_at"];
    invoice.modfied_at = data["last_modified_at"];

    invoice.payee_field  = data["payee_field"];
    invoice.text_subject = get_or_default<std::string>(data, "text_subject", "");
    invoice.text_opening = get_or_default<std::string>(data, "text_opening", "");
    invoice.text_closing = get_or_default<std::string>(data, "text_closing", "");
    invoice.customer_id  = data["customer_id"].get<uint64_t>();
    // invoice.payee_city      = get_or_default<std::string>(data, "payee_city", "");
    // invoice.payee_country   = get_or_default<std::string>(data, "payee_country", "");

    // TODO: remove me and load from file, this is just for demo!
    for (size_t i = 0; i < 10; ++i) {
        Currency c;
        c.from_cents(static_cast<uint64_t>(rand() % 1000));
        invoice.items.emplace_back(Invoice::Item{.article_id   = "A-000001",
                                                 .name         = "Item " + std::to_string(i),
                                                 .description  = "my description",
                                                 .quantity     = static_cast<size_t>(rand() % 100),
                                                 .single_price =
                                                 Price::create_from_price_with_vat(Currency::create_from_cents(120), 19)});
    }

    return invoice;
}

void InvoiceManagerJson::do_refresh_list()
{
    SPDLOG_INFO("loading invoices...");

    for (const auto &entry : std::filesystem::directory_iterator(m_invoices_basedir)) {

        m_elements.emplace_back(read_json_file(entry.path()));

        SPDLOG_DEBUG("successfully loaded {}", invoice_filepath.string());
    }
    SPDLOG_INFO("finished loading {} Invoices", m_elements.size());
}

Invoice InvoiceManagerJson::do_save_element(Invoice invoice)
{

    SPDLOG_INFO("saving invoice {}...", invoice.get_id_as_string());

    const std::string           filename         = invoice.get_id_as_string() + ".json";
    const std::filesystem::path invoice_filepath = m_invoices_basedir / filename;

    invoice.modfied_at = utils::get_current_datetime();

    // clang-format off
    json data = {
        {"_version"        , 1},
        {"id"              , invoice.get_id()},
        {"created_at"      , invoice.created_at},
        {"last_modified_at", invoice.modfied_at},
        {"customer_id"     , invoice.customer_id},
        {"payee_field"     , invoice.payee_field},
        {"text_subject"    , invoice.text_subject},
        {"text_opening"    , invoice.text_opening},
        {"text_closing"    , invoice.text_closing},
    };
    // clang-format on

    std::ofstream o(invoice_filepath);
    o << data.dump(4) << std::endl;
    SPDLOG_INFO("successfully saved {}", invoice_filepath.string());

    return invoice;
}
