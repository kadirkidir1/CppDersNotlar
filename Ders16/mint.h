//
// Created by test2 on 6/6/2022.
//
#include <iosfwd>

#ifndef DERS16_MINT_H
#define DERS16_MINT_H
// BASLIK DOSYASINDA ASLA ASLA ASLA NE USING NAMESPACE BILDIRIMI NE DE HERHANGI BIR
// USING BILDIRIMI YAPILACAK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
--
// GEREKSIZ BASLIK DOSYALARINI INCLUDE ETMEYIN

// FONKSIYONLARIN TANIMINDA DUMMY PARAMETRELERE ISIM VERMEYIN HATTA HATTA DUMMY
// ISMI DE VERMEYIN.
class Mint {
public:
    explicit Mint(int x) : m_x{ x } {}
    // XXX
    // BUNU NEDEN EXPLICIT KULLANIYOR ANLAMADIM!!!

    // ++ operatorunun degeri lValue olustrudugundan geri donus degeri kesinlikle T& olacak!
    Mint& operator++()  // prefix
    {
        ++m_x;
        return *this;
    }

    Mint operator++(int)    // postfix ++ rValue exp oldugundan T& degil T return edilecek
    {
        Mint retval{ *this};
        ++*this;
        return retval;
    }

    Mint& operator--()  // prefix
    {
        --m_x;
        return *this;
    }

    Mint operator--(int)    // postfix -- rValue exp oldugundan T& degil T return edilecek
    {
        Mint retval{ *this};
        --*this;
        return retval;
    }

    Mint operator+()const
    {
        return *this;
    }

    Mint operator-()const
    {
        return Mint{ -m_x}; // mandatory copy allision
    }

    Mint& operator+=(const Mint&other)
    {
        m_x += other.m_x;
        return *this;
    }

    Mint& operator-=(const Mint&other)
    {
        m_x -= other.m_x;
        return *this;
    }

    friend std::ostream&operator<<(std::ostream&, const Mint&);
    friend std::istream&operator>>(std::istream&, Mint&);

    friend bool operator<(const Mint &lhs, const Mint &rhs)
    {
        // bu yazdigimiz global oluyor cunku glboal olmasa friend'lik veremem.
        return lhs.m_x < rhs.m_x;
    }
    friend bool operator==(const Mint &lhs, const Mint &rhs)
    {
        // bu yazdigimiz global oluyor cunku glboal olmasa friend'lik veremem.
        return lhs.m_x == rhs.m_x;
    }
private:
    int m_x;
};

// Tum karsilastirma operatorleri bir yana, < ve == bir yana. Cunku C++ standart library'sinde bazi

// C++20 oncesi icin Boiler-plate code kullanin. Ama 20'ye kadar. 20de her sey degisti.

// C++20 standartlari ile bu konudaki kurallar ciddi degisiklere ugradi. Ilk basta C++20 kurallarini
// dikkate almayacagiz
// ogeleri kullanabilmek icin sinifimizin < isaretini implemente etmemiz gerekiyor.

inline Mint operator+(const Mint& lhs, const Mint& rhs)
{
    return Mint{lhs} += rhs;
}

inline Mint operator-(const Mint& lhs, const Mint& rhs)
{
    return Mint{lhs} -= rhs;
    // Mint library'sine de koyduktan sonra error kalkti ama neco direkt kopyaladi. Anlamadim
}

inline bool operator!=(const Mint &lhs,const Mint &rhs)
{
    return !(lhs == rhs);
}

// Buyuk esit kucugun degili!!
inline bool operator>=(const Mint &lhs,const Mint &rhs)
{
    return !(lhs < rhs);
}

inline bool operator>(const Mint &lhs,const Mint &rhs)
{
    return rhs < lhs;
}

inline bool operator<=(const Mint &lhs,const Mint &rhs)
{
    return !(rhs < lhs);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////



#endif //DERS16_MINT_H
