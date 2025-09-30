#include "article_editor.hpp"

#include <spdlog/spdlog.h>
#include "object_referencer_dialog.hpp"
#include "wcrm-lib/objects/vendor.hpp"
#include "vendor_selector.hpp"

#include <cassert>

namespace
{
    std::string vendor_to_displayname(const Vendor& vendor)
    {
        return vendor.name + " (" + vendor.get_id_as_string() + ")";
    }

    uint64_t vendor_id_from_displayname(const std::string& displayname)
    {
        if (displayname.empty()) return 0;

        size_t pos_start = displayname.find('(');
        size_t pos_end   = displayname.find(')');

        assert(pos_start != std::string::npos);
        assert(pos_end   != std::string::npos);
        assert(pos_start < pos_end);
        pos_start++;
        auto substr = displayname.substr(pos_start, pos_end-pos_start);

        pos_start = substr.find('-');
        assert(pos_start != std::string::npos);
        assert(pos_start < substr.length());
        pos_start++;
        substr = substr.substr(pos_start, substr.length()-pos_start);

        return std::stoul(substr);
    }
}

void ArticleEditor::write_to_gui(const Article &article)
{
    SPDLOG_INFO("writing to gui '{} {}'", article.get_id_as_string(), article.name);

    value_to_gui(article.get_id_as_string() , ui_article_id);
    value_to_gui(article.created_at         , ui_created_at);
    value_to_gui(article.modfied_at         , ui_last_modified);

    value_to_gui(article.name        , ui_article_name);
    value_to_gui(article.description , ui_article_description);
    value_to_gui(article.unit        , ui_article_unit);
    value_to_gui(article.material    , ui_article_material);
    value_to_gui(article.weight_kg   , ui_article_weight);
    value_to_gui(article.length_cm   , ui_article_length);
    value_to_gui(article.width_cm    , ui_article_width);
    value_to_gui(article.height_cm   , ui_article_height);

    auto vendor = m_app_context.vendor_manager->get_element_by_id(article.vendor_id);
    std::string vendor_displayname = vendor.has_value() ? vendor_to_displayname(*vendor) : "";
    value_to_gui(vendor_displayname                 , ui_vendor_name);
    value_to_gui(article.vendor_article_id          , ui_vendor_article_id);
    value_to_gui(article.vendor_article_name        , ui_vendor_article_name);
    value_to_gui(article.vendor_article_description , ui_vendor_article_description);
    value_to_gui(article.vendor_article_price       , ui_vendor_article_price);
    value_to_gui(article.vendor_article_weblink     , ui_vendor_article_weblink);

    value_to_gui(article.sell_price, ui_sell_price);
}

void ArticleEditor::read_from_gui(Article &article)
{
    SPDLOG_INFO("reading from gui '{} {}'", article.get_id_as_string(), article.name);

    value_from_gui(article.name        , ui_article_name);
    value_from_gui(article.description , ui_article_description);
    value_from_gui(article.unit        , ui_article_unit);
    value_from_gui(article.material    , ui_article_material);
    value_from_gui(article.weight_kg   , ui_article_weight);
    value_from_gui(article.length_cm   , ui_article_length);
    value_from_gui(article.width_cm    , ui_article_width);
    value_from_gui(article.height_cm   , ui_article_height);

    article.vendor_id = vendor_id_from_displayname(ui_vendor_name.input.get_text());

    value_from_gui(article.vendor_article_id          , ui_vendor_article_id);
    value_from_gui(article.vendor_article_name        , ui_vendor_article_name);
    value_from_gui(article.vendor_article_description , ui_vendor_article_description);
    value_from_gui(article.vendor_article_weblink     , ui_vendor_article_weblink);
    value_from_gui(article.vendor_article_price       , ui_vendor_article_price);

    value_from_gui(article.sell_price, ui_sell_price);
}

ArticleEditor::ArticleEditor(AppContext &context) : ObjectEditorPanel(context)
{
    ui_flowbox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);

    ui_image = Gtk::Image{m_app_context.basepath / "resources/image-placeholder.svg"};
    ui_flowbox.add(ui_frame_system_info);
    ui_frame_system_info.add_element(ui_article_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.m_grid.attach(ui_image, 2, 0, 1, 3);


    int row = 0;
    ui_flowbox.add(ui_frame_base_info);
    ui_frame_base_info.add_full_width(row++, ui_article_name);
    ui_frame_base_info.add_full_width(row++, ui_article_description);
    ui_frame_base_info.add_left(row, ui_article_unit);
    ui_frame_base_info.add_right(row++, ui_article_material);
    ui_frame_base_info.add_left(row, ui_article_length);
    ui_frame_base_info.add_right(row++, ui_article_weight);
    ui_frame_base_info.add_left(row++, ui_article_width);
    ui_frame_base_info.add_left(row++, ui_article_height);


    row = 0;
    ui_flowbox.add(ui_frame_vendor);
    ui_frame_vendor.add_full_width(row++, ui_vendor_name);
    ui_frame_vendor.add_left( row, ui_vendor_article_id);
    ui_frame_vendor.add_right(row++, ui_vendor_article_price);
    ui_frame_vendor.add_full_width(row++, ui_placeholder);
    ui_frame_vendor.add_full_width(row++, ui_vendor_article_name);
    ui_frame_vendor.add_full_width(row++, ui_vendor_article_description);
    ui_frame_vendor.add_full_width(row++, ui_vendor_article_weblink);

    row = 0;
    ui_flowbox.add(ui_frame_sales);
    ui_frame_sales.add_left(row++, ui_sell_price);

    write_to_gui(m_object);

    ui_vendor_name.cb_on_choose_object = [&]() {
        ObjectReferencerDialog<Vendor> dialog(std::make_unique<VendorSelector>(m_app_context),
                m_app_context.vendor_manager,
                *m_app_context.main_window);

        const auto vendor = dialog.run();

        if (vendor.has_value()) {
            ui_vendor_name.input.set_text( vendor_to_displayname(*vendor));
        }

    };
}
