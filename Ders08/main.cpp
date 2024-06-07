#include <iostream>
#include <cstdio>

int main() {

    int printf = 5;     // legal bir kullanimdir.
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


class A{
public:
    void foo(A);

private:
    int m_x;
};

A ga;

void A::foo(A pa){
    A ax;
    pa.m_x;
    m_x = 5;
    ax.m_x = 10;
    ga.m_x = 8;     // Hepsi geçerlidir.
}

// mutable --> değiştirilebilir.

struct Data{
    int a,b,c;
};

void func(struct Data*); // C'de bu bir mutater. Parametre struct Data*
void foo(const struct Data*); // Accesser. Nesneyi değiştirmeyecek.


class Myclass{
public:
    void func( /* Burada gizli bir Myclass *p var . ,*/int );
    void foo()const; // şuna işaret eder. foo(const Myclass *p); Gizli ögeyi const yapar.
private:
    int m_x;
};

void Myclass::func(int k) {
    m_x = 10; // yapılabilir çünkü herhangi bir const'luk yok.
}

void Myclass::foo() const {
    m_x = 10; // Syntax hatasıdır çünkü const.
    auto val = m_x; // Geçerli. Salt okuma yapiliyor sonucta.
}

// 1. Sınıfın const üye fonksiyonları (hangi nesne için çağırılmışlarsa) o nesnenin veri elemanlarını değiştiremezler.
// 2. Const olan ya da olmayan bir sınıf nesnesi ile sınıfın const üye fonksiyonları çağırılabilir. Ancak const bir
//    sınıf nesnesi ile sadece sınıfın const üye fonksiyonları çağırılabilir.

class A2{
public:
    void foo();
    void foo()const;
};

int klm(){
    const A2 ca;    // --> Burada overload vardır.
    ca.foo(); // Burada alttaki const olan çağırılacak.
    A2 cb;
    cb.foo(); // Burada da üstteki const olmayan fonksiyon çağırılacak.
}

class A3{
public:
    void func();
    void foo();
};

void A3::func() {
    foo(); // 1 bu çağrı ne anlama geliyor 2 derleyici bunun için nasıl bir kod üretiyor?
    // Önce name lookup yapılacak. Derleyici foo ismini arayacak. Class scope içerisinde arayacak ve bulacak. Böylece
    // foo'nun sınıfın non-static üye fonksiyonu olduğunu öğrenecek.
    // A->foo(); --> gibi çağıracak.
}

class A4{
public:
    void func();
};

void func(int x){

}

void A4::func() {
    func(10); // Class içerisindeki int parametresi almamış. Global scope'taki almış.
              // Bu bir syntax hatasıdır çünkü global scope'tan önce class scope'ta bulunur ve access kontrol'de
              // hata ile karşılaşılır.

    func();   // Böyle çağırılırsa recursive çağrı olur. Syntax hatası yok.
}

class A4{
public:
    void func();
    void func(int);
};

void A4::func() {
    func();   // Böyle çağırılırsa recursive çağrı olur. Syntax hatası yok.
    func(10); // Bu şekilde recursive fonksiyon olmaz.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A5{
public:
    void func();
    void foo()const;
};

void A5::func() {
    foo(); // --> Bunun cagirilmasinda herhangi bir sorun yok. Sinifin non-const uye fonksiyonu const uye fonksiyonunu
           // cagirabilir.


}

void A5::foo() const {
    // Const üye fonksiyon non-const uye fonksiyon cagirabilir mi? Tabiki hayır!!!
    func(); // --> Syntax hatası.

    // Bir sınıfın const uye fonksiyonu sinifin non-const uye fonksiyonunu cagiramaz. Ayni nesne icin!!!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <map>

void func(const std::map<int,int>& pmap){
    auto val = pmap[12]; // --> Buradaki hata, Function overload olmasina ragmen, pmap'in const olmasindandir. Cunku
                         // Const bir nesne const olmayan bir nesneye donusturulemez.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Fighter{
public:
    void print()const;
private:
    int m_debug{};
};

void Fighter::print() const {
    ++m_debug;  // Bu fonksiyonun parametresi const function*, sen böyle bir parametrenin gösterdiği veriyi değiştirmeye
                // kalktığında dilin kurallarına göre hata yapmış olursun.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Fighter2{
public:
    void print()const;
private:
    mutable int m_debug{};  // Bu veri elemanının sınıf nesnesinin problem domainindeki anlamıyla bir ilişkisi yok. Yani
                            // bu elemanın örneğin değerinin değişmesi sınınf nesnesinin problem domainindeki değerini
                            // değiştirmiyor.
};

void Fighter2::print() const {
    ++m_debug;  //
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Circle{
public:
    double get_area(); // diyelim dairenin alanını hesaplayacağız. hesaplayacağımız alanın değişmemesi gerekir ve burada
                       // const correctness'ın sağlanması gerekir. Yani kesinlikle böyle kullanmamak gerekiyor. Const
                       // ile kullanmak gerekiyor. || double get_area()const;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// this bir keywoard'tür. Yalnızca sınıfın non-static fonksiyonlarının tanımında kullanılır.

class A6{
public:
    void func();

private:
    int mx,my;
};

void A6::func() {
    std::cout << "func cagirildi this = " << this << "\n";
}

int main(){
    A6 m;

    std::cout << "m" << &m << "\n";
    m.func();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A7{
public:
    void func();
    void foo();
private:
    int mx, my;
};

void gf1(Myclass*);
void gf2(Myclass&);

void Myclass::fo()
{
    gf1(this); // Class'ın adresini ancak ve ancak this ile gönderebiliriz.
    gf2(*this);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A8{
public:
    A8& func();
};

A8 &A8::func() {        // beni hangi nesne için çağırmışlarsa beni o nesneye göndür!!! Çok sık karşılaşılan bir yapı.
    std::cout << "A8::func cagirildi\n";
    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A9{
public:
    A9& func();
    A9& foo();
    A9& bar();
};

A9 &A9::func() {
    return *this;
}

int main_func(){
    A9 m;
    m.func().foo().bar(); // yapabilirim. Bunu böyle yapmakla
    m.func();
    m.foo();
    m.bar(); // Yapmak arasinda herhangi bir farklilik yok!!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// std::cout << x << dval << lval; Eşittir
// std::cout.operator <<(x).operator << (y).operator(lval); Yukarıdakiyle aşağıdaki kod arasında anlamsal olarak herhangi
// bir farklılık yoktur.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Ostream{
public:
    Ostream& operator<<(int);
    Ostream& operator<<(double);
    Ostream& operator<<(long);
};

Ostream &Ostream::operator<<(int x) {

    //// code
    return *this;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 class A10{
public:
    A10* foo()
    {
        return this; // *this değil direkt this
    }
    void func();
};

int main_func10()
{
    A10 m;
    m.foo()->func(); // -> operatörüyle çağırdık çünkü return değeri *this değil this.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A11{
public:
    void func(const A11&);
};

void A11::func(const A11& a) {
    if (this == &a){
        std::cout << "gelen ayni \n";
    }
}


void main_func11(){
    A11 ax;
    A11 bx;

    ax.func(bx);        // Bu gonderildigi zaman farkli olacak adresler.
    ax.func(ax);        // Bu gonderildiginde ise "gelen ayni" ciktisi verecektir.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// *this pointer prValue'dur.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A12{
public:
    void func()const;
    void foo();
};

void A12::foo() {
// burada this pointer'ının türü A12*
}

void A12::func() const {
// burada this pointer'ının türü const A12*
    this->foo(); // Hatali kullanim cunku const A*' türünden A* türüne dönüşüm illegal.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class A13{
public:
    A13 *func()const;
};

A13 *A13::func() const {
    return this;    // Syntax hatasıdır çünkü const T*'dan T*'a dönüşüm hatası. Olması gereken;;;
}
/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/* */
class A13{
public:
    const A13 *func()const;
};

const A13 *A13::func() const {
    return this;    // Syntax hatasıdır çünkü const T*'dan T*'a dönüşüm hatası. Olması gereken;;;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INLINE FUNCTIONS
/*
 * iki kavram birbiriyle karıştırılıyor, birincisi inline expansion, ikincisi ODR
 *
 */