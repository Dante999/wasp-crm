#ifndef ARTICLE_EDITOR_HPP
#define ARTICLE_EDITOR_HPP

#include <gtkmm/box.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>

#include <functional>

#include "wcrm-lib/objects/article.hpp"

#include "gtkmm/button.h"
#include "gtkmm/buttonbox.h"
#include "object_editor_panel.hpp"
#include "util_gtk.hpp"

class ArticleEditor : public ObjectEditorPanel<Article> {
    private:
        util_gtk::FrameFormLayout   ui_frame_system_info{"system_info"};
        util_gtk::TextInputReadonly ui_article_id{"id"};
        util_gtk::TextInputReadonly ui_created_at{"created_at"};
        util_gtk::TextInputReadonly ui_last_modified{"last_modified"};

        util_gtk::FrameFormLayout    ui_frame_base_info{"base_info"};
        util_gtk::TextInput          ui_article_name{"name", "", 80};
        util_gtk::TextMultilineInput ui_article_description{"description", "", 80};
        util_gtk::TextInput          ui_article_width{"width_cm", ""};
        util_gtk::TextInput          ui_article_length{"length_cm", ""};
        util_gtk::TextInput          ui_article_height{"height_cm", ""};
        util_gtk::TextInput          ui_article_weight{"weight_gram", ""};

        util_gtk::FrameFormLayout ui_frame_vendor{"vendor"};
        util_gtk::TextInput       ui_vendor_name{"vendor_name", "", 80};
        util_gtk::TextInput       ui_vendor_article_id{"article_id", "", 80};
        util_gtk::TextInput       ui_vendor_article_name{"article_name", "", 80};
        util_gtk::TextInput       ui_vendor_article_description{"article_name", "", 80};
        util_gtk::TextInput       ui_vendor_article_weblink{"weblink", "", 80};
        util_gtk::TextInput       ui_vendor_article_price{"unit_price", "", 80};

    private:
        void write_to_gui(const Article &article) override;
        void read_from_gui(Article &article) override;

    public:
        ArticleEditor();
};

#endif // ARTICLE_EDITOR_HPP