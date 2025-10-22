#ifndef PRICE_HPP
#define PRICE_HPP

#include "utils/currency.hpp"
#include <stdexcept>

struct Price {
        double   vat = 19.0;
        Currency without_vat;
        Currency with_vat;

        Price() = default;

        Price(Currency _without_vat, double _vat, Currency _with_vat)
            : vat{_vat}, without_vat{_without_vat}, with_vat{_with_vat}
        {
            if (with_vat.as_raw_value() != (without_vat * vat).as_raw_value()) {
                char msg[255];

                snprintf(msg, sizeof(msg), "Expected %s * %f = %s", _without_vat.as_string().c_str(), vat,
                         _with_vat.as_string().c_str());

                throw std::invalid_argument(msg);
            }
        }

        static Price create_from_price_without_vat(Currency _without_vat, double _vat)
        {
            return Price{_without_vat, _vat, (_without_vat * (1 + (_vat / 100)))};
        }

        static Price create_from_price_with_vat(Currency _with_vat, double _vat)
        {
            return Price{(_with_vat * (1 - (_vat / 100))), _vat, _with_vat};
        }
};

#endif // PRICE_HPP
