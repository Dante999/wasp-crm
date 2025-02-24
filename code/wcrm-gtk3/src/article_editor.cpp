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
}

void ArticleEditor::read_from_gui(Article &article)
{
    SPDLOG_INFO("reading from gui '{} {}'", article.get_id_as_string(), article.name);

    article.name        = ui_article_name.input.get_text();
    article.description = ui_article_description.input.get_text();
}

ArticleEditor::ArticleEditor()
{
    add(ui_frame_system_info);
    ui_frame_system_info.add_element(ui_article_id);
    ui_frame_system_info.add_element(ui_created_at);
    ui_frame_system_info.add_element(ui_last_modified);
    ui_frame_system_info.show();

    add(ui_frame_base_info);
    ui_frame_base_info.add_element(ui_article_name);
    ui_frame_base_info.add_element(ui_article_description);
    ui_frame_base_info.add_element(ui_article_length);
    ui_frame_base_info.add_element(ui_article_width);
    ui_frame_base_info.add_element(ui_article_height);
    ui_frame_base_info.add_element(ui_article_weight);
    ui_frame_base_info.show();

    add(ui_frame_vendor);
    ui_frame_vendor.add_element(ui_vendor_name);
    ui_frame_vendor.add_element(ui_vendor_article_id);
    ui_frame_vendor.add_element(ui_vendor_article_name);
    ui_frame_vendor.add_element(ui_vendor_article_weblink);
    ui_frame_vendor.show();
}