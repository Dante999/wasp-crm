#ifndef ARTICLE_EDITOR_HPP
#define ARTICLE_EDITOR_HPP

#include <gtkmm/box.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>

#include "wcrm-lib/objects/article.hpp"

#include "object_editor_panel.hpp"
#include "util_gtk.hpp"

class ArticleEditor : public ObjectEditorPanel<Article> {
    private:
        util_gtk::Placeholder             ui_placeholder;

        util_gtk::FrameFormGridRow<1>     ui_frame_system_info{"system_info"};
        util_gtk::TextInputReadonly       ui_article_id{"id"};
        util_gtk::TextInputReadonly       ui_created_at{"created_at"};
        util_gtk::TextInputReadonly       ui_last_modified{"last_modified"};
        Gtk::Image                        ui_image;

        util_gtk::FrameFormGrid2      ui_frame_base_info{"article"};
        util_gtk::TextInput           ui_article_name{"name", "", };
        util_gtk::TextInput           ui_article_unit{"unit", "", };
        util_gtk::TextInput           ui_article_material{"material", "", };
        util_gtk::TextMultilineInput  ui_article_description{"description", "", };
        util_gtk::TextInput           ui_article_width{"width_cm", ""};
        util_gtk::TextInput           ui_article_length{"length_cm", ""};
        util_gtk::TextInput           ui_article_height{"height_cm", ""};
        util_gtk::TextInput           ui_article_weight{"weight_kg", ""};

        util_gtk::FrameFormGrid2      ui_frame_vendor{"purchasing"};
        util_gtk::TextInput           ui_vendor_name{"vendor", ""};
        util_gtk::TextInput           ui_vendor_article_id{"article_id", ""};
        util_gtk::TextInput           ui_vendor_article_name{"article_name", ""};
        util_gtk::TextInput           ui_vendor_article_description{"article_description", ""};
        util_gtk::TextInput           ui_vendor_article_weblink{"weblink", ""};
        util_gtk::TextInput           ui_vendor_article_price{"unit_price_euro", ""};

    private:
        void write_to_gui(const Article &article) override;
        void read_from_gui(Article &article) override;

    public:
        ArticleEditor(AppContext &context);
};

#endif // ARTICLE_EDITOR_HPP
