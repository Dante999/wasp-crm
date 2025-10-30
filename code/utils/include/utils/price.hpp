#ifndef PRICE_HPP
#define PRICE_HPP


#include "utils/currency.hpp"

class Price {
private:
    double   m_vat_percent = 19.0;
    Currency m_value;
    bool     m_vat_included{false};

public:
    Price() = default;
    Price(double _vat_percent, Currency _value, bool _vat_included)
        : m_vat_percent{_vat_percent}
        , m_value{_value}
        , m_vat_included{_vat_included}
        {}

        auto get_value() const {return m_value;}
        auto get_vat_percent() const {return m_vat_percent;}
        auto is_vat_included() const {return m_vat_included;}



        static Price create_from_price_without_vat(Currency _without_vat, double _vat)
        {
            return Price{ _vat, _without_vat, false};
        }

        static Price create_from_price_with_vat(Currency _with_vat, double _vat)
        {
            return Price{ _vat, _with_vat, true};
        }
};

#endif // PRICE_HPP
