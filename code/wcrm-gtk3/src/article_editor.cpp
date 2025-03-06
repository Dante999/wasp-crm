#include "article_editor.hpp"

#include <spdlog/spdlog.h>

void ArticleEditor::write_to_gui(const Article &article)
{
    SPDLOG_INFO("writing to gui '{} {}'", article.get_id_as_string(), article.name);

    ui_article_id.input.set_text(article.get_id_as_string());
    ui_created_at.input.set_text(article.created_at);
    ui_last_modified.input.set_text(article.modfied_at);

    ui_article_name.input.set_text(article.name);
    ui_article_description.input.set_text(article.description);
    ui_article_unit.input.set_text(article.unit);
    ui_article_weight.input.set_text(std::to_string(article.weight_kg));
    ui_article_length.input.set_text(std::to_string(article.length_cm));
    ui_article_width.input.set_text(std::to_string(article.width_cm));
    ui_article_height.input.set_text(std::to_string(article.height_cm));
}

void ArticleEditor::read_from_gui(Article &article)
{
    SPDLOG_INFO("reading from gui '{} {}'", article.get_id_as_string(), article.name);

    article.name        = ui_article_name.input.get_text();
    article.description = ui_article_description.input.get_text();
    article.unit        = ui_article_unit.input.get_text();
    article.weight_kg   = std::stof(ui_article_weight.input.get_text());
    article.length_cm   = std::stof(ui_article_length.input.get_text());
    article.width_cm    = std::stof(ui_article_width.input.get_text());
    article.height_cm   = std::stof(ui_article_height.input.get_text());
}

ArticleEditor::ArticleEditor(AppContext &context) : ObjectEditorPanel(context) 
{
    /*
     * Material
     *
     * Verkauf
     * - Preis
     * - Mehrwertsteuer
     */


    ui_flowbox.set_selection_mode(Gtk::SelectionMode::SELECTION_NONE);

    ui_image = Gtk::Image{m_app_context.basepath / "resources/image-placeholder.svg"};
    ui_flowbox.add(ui_frame_system_info);
    ui_frame_system_info.add_element(ui_article_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.m_grid.attach(ui_image, 2, 0, 1, 3);

    ui_flowbox.add(ui_frame_base_info);

    int row = 0;
    ui_frame_base_info.add_full_width(row++, ui_article_name);
    ui_frame_base_info.add_full_width(row++, ui_article_description);
    ui_frame_base_info.add_left(row, ui_article_unit);
    ui_frame_base_info.add_right(row++, ui_article_weight);
    ui_frame_base_info.add_left(row++, ui_article_length);
    ui_frame_base_info.add_left(row++, ui_article_width);
    ui_frame_base_info.add_left(row++, ui_article_height);


    ui_flowbox.add(ui_frame_vendor);
    row = 0;
    ui_frame_vendor.add_full_width(row++, ui_vendor_name);
    ui_frame_vendor.add_left( row, ui_vendor_article_id);
    ui_frame_vendor.add_right(row++, ui_vendor_article_price);

    ui_frame_vendor.add_full_width(row++, ui_placeholder);

    ui_frame_vendor.add_full_width(row++, ui_vendor_article_name);
    ui_frame_vendor.add_full_width(row++, ui_vendor_article_description);
    ui_frame_vendor.add_full_width(row++, ui_vendor_article_weblink);

}
