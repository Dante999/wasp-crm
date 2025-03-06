#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <cstdint>
#include <string>

class BaseObject {
    private:
        uint64_t m_id;

    public:
        std::string created_at;
        std::string modfied_at;


    public:
        BaseObject(uint64_t id) : m_id{id} {};

        virtual ~BaseObject() {}

        [[nodiscard]] uint64_t    get_id() const { return m_id; }
        [[nodiscard]] std::string get_id_as_string() const
        {
            char tmp[255];
            snprintf(tmp, sizeof(tmp), "%s%05lu", get_id_prefix().c_str(), m_id);
            return tmp;
        }

        [[nodiscard]] virtual std::string get_id_prefix() const = 0;
};

#endif // BASE_OBJECT_HPP
