//
// Created by test2 on 6/6/2022.
//
// IMPLEMENTATION FILE, SOURCE FILE
// SOURCE FILE ILE TRANSLATION UNIT FARKLI SEYLER.

#include "mint.h"
#include <ostream>
#include <istream>

std::ostream&operator<<(std::ostream& os, const Mint& mint)
{
    return os << '(' << mint.m_x << ')';  // Bu tur fonksiyonlarda new line vermeyin
                        // Bunu cagiracak fonksiyon karar versin!!!1bir!!!1!

                        //// Mesela buralarda neden referans olarak alıyor??
}

std::istream&operator>>(std::istream& is, Mint& mint)
{
    return is >> mint.m_x;
}