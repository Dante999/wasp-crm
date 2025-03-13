#ifndef IMANAGER_HPP
#define IMANAGER_HPP

#include <cstdint>
#include <vector>
#include <algorithm>

#include "utils/datetime_utils.hpp"

template <class T>
struct IManager {
    private:
        uint64_t m_next_id{1};

    protected:
        std::vector<T> m_elements;

        virtual void do_refresh_list()          = 0;
        virtual T    do_save_element(T element) = 0;

    public:
        virtual ~IManager() {}

        T create_element()
        {
            T element{m_next_id++};

            element.created_at = utils::get_current_datetime();
            element.modfied_at = utils::get_current_datetime();

            return element;
        }

        std::vector<T> get_list() { return m_elements; }

        void refresh_list()
        {

            m_elements.clear();

            do_refresh_list();

            std::sort(std::begin(m_elements), std::end(m_elements),
                      [](const T &lhs, const T &rhs) { return lhs.get_id() < rhs.get_id(); });

            if (!m_elements.empty()) {
                m_next_id = m_elements.at(m_elements.size() - 1).get_id() + 1;
            }
        }

        T save_element(T element)
        {
            return do_save_element(element);
        }
};

#endif // IMANAGER_HPP
