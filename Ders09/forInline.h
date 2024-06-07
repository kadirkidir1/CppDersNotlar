//
// Created by test2 on 5/6/2022.
//

#ifndef DERS9_FORINLINE_H
#define DERS9_FORINLINE_H

inline int x = 5;

inline int showX(){
    return x;
}

class kadir{
public:
    void set(int x);
    // inline void set(int x); --> Bu şekilde kullanılarak da ODR'den kaçınılabilirdi.
private:
    int mx;
};

inline void kadir::set(int x) {
    mx = x;
    // Bu fonkisyonun ODR'yi ihlal etmemesi için inline anahtar sözcüğü ya burada olduğu gibi fonksiyonun tanımında,
    // ya class içerisinde ya da her ikisinde birden olabilir.
}

class kadir002{
public:
    void set(int x){
        mx = x; // Fonksiyonu sınıfın içerisinde tanımlamak da ODR'den kaçınmanın bir yoludur. Inline koysak da koymasak
        // da ODR ihlal edilmemiş oluyor. Ama üretimde böyle yapmamak daha mantıklı. Implicitly Inline. Inline anahtar
        // sözcüğü de kullanılabilir ama gerek yok gerek yok.
    }

private:
    int mx;
};

#endif //DERS9_FORINLINE_H
