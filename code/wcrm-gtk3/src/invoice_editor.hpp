#ifndef INVOICE_EDITOR_HPP
#define INVOICE_EDITOR_HPP

#include <gtkmm/box.h>
#include <gtkmm/enums.h>
#include <gtkmm/flowbox.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/image.h>
#include <gtkmm/liststore.h>
#include <gtkmm/notebook.h>
#include <gtkmm/treeview.h>

#include "src/util_translate.hpp"
#include "wcrm-lib/objects/invoice.hpp"

#include "object_editor_panel.hpp"
#include "util_gtk.hpp"

class InvoiceItemTable : public Gtk::ScrolledWindow {
        class ModelColumns : public Gtk::TreeModel::ColumnRecord {
            public:
                ModelColumns()
                {
                    add(m_col_id);
                    add(m_col_name);
                    add(m_col_quantity);
                    add(m_col_price);
                    add(m_col_total);
                }

                Gtk::TreeModelColumn<unsigned int>  m_col_id;
                Gtk::TreeModelColumn<Glib::ustring> m_col_name;
                Gtk::TreeModelColumn<float>         m_col_quantity;
                Gtk::TreeModelColumn<Glib::ustring> m_col_price;
                Gtk::TreeModelColumn<Glib::ustring> m_col_total;
        };

        ModelColumns                 m_Columns;
        Gtk::ScrolledWindow          m_ScrolledWindow;
        Gtk::TreeView                m_TreeView;
        Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
        std::vector<Invoice::Item>   m_items{};

    public:
        InvoiceItemTable()
        {
            add(m_TreeView);

            // Only show the scrollbars when they are necessary:
            set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
            set_hexpand();
            set_vexpand();

            m_refTreeModel = Gtk::ListStore::create(m_Columns);
            m_TreeView.set_model(m_refTreeModel);

            m_TreeView.append_column("ID", m_Columns.m_col_id);
            m_TreeView.append_column("Name", m_Columns.m_col_name);
            m_TreeView.append_column_numeric("Quantity", m_Columns.m_col_quantity, "%.2f");
            m_TreeView.append_column("Price", m_Columns.m_col_price);
            m_TreeView.append_column("Total", m_Columns.m_col_total);
        }

        void set_items(const std::vector<Invoice::Item>& items) { m_items = items; }
        auto get_items() { return m_items; }

        void refresh()
        { // clang-format off

            for(size_t i=0; i < m_items.size(); ++i) {
                auto row = *(m_refTreeModel->append());

                const auto &item = m_items.at(i);
                spdlog::debug("displaying item[{}]: id={} name={} quantity={} price={}",
                        i, i+1, item.name, item.quantity, item.single_price.get_value().as_string());

                row[m_Columns.m_col_id] = static_cast<unsigned int>(i+1);
                row[m_Columns.m_col_name] = item.name;
                row[m_Columns.m_col_quantity] = item.quantity;
                row[m_Columns.m_col_price] = item.single_price.get_value().as_string();
                row[m_Columns.m_col_total] = (item.single_price.get_value()* item.quantity).as_string();

            }

        } // clang-format on
    private:
#if 0
        Gtk::Label ui_position_header{util_translate::translate("position")};
        Gtk::Label ui_name{util_translate::translate("name")};
        Gtk::Label ui_quantity{util_translate::translate("quantity")};
        Gtk::Label ui_price{util_translate::translate("price")};
        Gtk::Label ui_total{util_translate::translate("total")};

    public:
        InvoiceItemTable()
        {
            set_row_spacing(2);
            set_column_spacing(10);
            set_margin_top(10);
            set_margin_bottom(10);
            set_margin_left(10);
            set_margin_right(10);
            set_border_width(1);
            set_vexpand();
            refresh();
        }


        void refresh()
        { // clang-format off
            attach(ui_position_header, 0, 0);
            attach(ui_name           , 1, 0);
            attach(ui_quantity       , 2, 0);
            attach(ui_price          , 3, 0);
            attach(ui_total          , 4, 0);
        } // clang-format on
#endif
};

class InvoiceEditor : public ObjectEditorPanel<Invoice> {
    private:
        Gtk::Notebook ui_notebook;
        Gtk::Box      ui_base_info_pane{Gtk::ORIENTATION_VERTICAL};
        Gtk::Box      ui_payee_text_pane{Gtk::ORIENTATION_VERTICAL};
        Gtk::Box      ui_article_pane{Gtk::ORIENTATION_VERTICAL};

        util_gtk::Placeholder ui_placeholder;

        util_gtk::FrameFormGridRow<1> ui_frame_system_info{"system_info"};
        util_gtk::TextInputReadonly   ui_invoice_id{"id"};
        util_gtk::TextInputReadonly   ui_created_at{"created_at"};
        util_gtk::TextInputReadonly   ui_last_modified{"last_modified"};
        Gtk::Image                    ui_image;

        util_gtk::FrameFormGrid2     ui_frame_base_info{"payee"};
        util_gtk::ObjectChooser      ui_customer{"customer", ""};
        util_gtk::TextMultilineInput ui_payee_field{"receiver", ""};

        util_gtk::TextInput          ui_text_subject{"subject", ""};
        util_gtk::TextMultilineInput ui_text_opening{"opening_text", ""};
        util_gtk::TextMultilineInput ui_text_closing{"closing_text", ""};

        InvoiceItemTable ui_article_table;

    private:
        void write_to_gui(const Invoice &invoice) override;
        void read_from_gui(Invoice &article) override;

    public:
        InvoiceEditor(AppContext &context);
};

#endif // INVOICE_EDITOR_HPP
