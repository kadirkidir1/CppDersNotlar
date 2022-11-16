#include <iostream>

class Nec{
public:
    void func();
    static void sfunc();
};

void func_001(){
    Nec mynec;
    mynec.func();
    mynec.sfunc();  // C++'ta static nesneler bu sekilde cagirilabilir!!!
                    // Ama bu sekilde kullanima dikkat etmek gerekir.
                    // Okudugun zaman neden hatali oldugunu fark etmeden gecme!!!
};

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class kdr_001{
    kdr_001();

public:
    static kdr_001 create_object();
};

void fkdr_001(){
    // kdr_001 k;      // bu bir syntax hatasi cunku private'a erismeye calisiyoruz.
    auto m = kdr_001::create_object();  // Ctor private oldugu icin bu sekilde
    // cagirmaktan baska carem kalmiyor.

}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class Complex{
public:
    Complex(double distance, double angle); // polar
    //Complex(double r, double i);            // cartesian
    // Eger bu sekilde public kalirlarsa ambiguity'den dolayi hata olusur.
    // Bundan kacmak icin bunlari private'a alabilirim. ( Complex_2)
};

class Complex_2{
private:
    Complex_2(double distance, double angle); // polar
    Complex_2(double r, double i , int);       // cartesian, en sondaki Dummmy
public:
    static Complex_2 create_polar(double d, double a)
    {
        return Complex_2(d,a);
    }
    static Complex_2 create_cartesian(double r, double i)
    {
        return Complex_2(r, i ,0);  // burada overload hatasindan kurtulmus oluruz.
        // Bu sekilde islem yapmaya named constructor deniyor!
    }
};

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class DynamicOnly{
private:
    DynamicOnly();
public:
    static DynamicOnly* create_object(){    // dinamik nesneleri raw pointer'larla cagirmak
        // cok fazla kullanacagimiz bir sey degil aslinda
        return new DynamicOnly{};
    }
};
// dinamik omurlu nesneleri genellikle smart pointer sinif nesneleriyle kontrol ediyoruz.
// Smart pointer'lar Cpp'nin en onemli olaylarindan bir tanesi!!!

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

#include <memory>

class kdr_002{
public:
    kdr_002(){
        std::cout << "def ctor \n";
    }
    ~kdr_002(){
        std::cout << "def destructor \n";
    }
};

void f_kdr_002(){
    std::cout << "fonksiyon basladi\n";
    {
        auto uptr = std::make_unique<kdr_002>();
        // uniq ptr turunden smart pointer bir nesne
    }
    std::cout << "fonksiyon bitti\n";
}
// oylesine gosterdi, ileride detayli gorecegiz.

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
// FRIEND DECLERATIONS
// sinifin uye bildirimi olmayan fonksiyonlara arkadaslik verebiliyoruz. Derleyiciye diyoruzki
// su su su fonksiyon, benim private bolumume erisebilir. Derleyici u bildirime dayanarak orada
// private'a erisim syntax hatasi olacakken, syntax hatasi vermiyor.

int fr_func(){
    using namespace std;
    string s1{"kadir"} , s2{"kidir"};

    auto s3 = s1 + s2; // aslinda bu fonksiyon asagidaki sekilde cagirilir
    auto s4 = operator+(s1,s2);

}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
/*
 * 3 ayri sekilde friend function bildirimi yapabiliriz.
 * a) free function- global function
 * b) bir sinifin uye fonksiyonuna - Baska bir sinifin
 * c) bir sinifin tum uye foksiyonlarina yani tum sinifa
 * en sik kullanilan a c b siralamasiyla gidiyor.
 */

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class asd1{
public:
    friend void g_func();   // ismi g_func olan fonksiyon benim friend'imdir private bolumume erisebilir.
private:
    int mx,my;
    void foo();
};

void g_func(){
    asd1 asd1;
    asd1.mx = 43;   // friend bildirimi olmadiginda hata veriyorken su an hata vermiyor.
}

// friend bildiriminin sinifin public, private ya da protected kisminda yapilmasi bir farklilik yaratmıyor.

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class kdr43{
public:
    friend void asd35();
};

int f_kdr35(){
    //asd35();    // friend function'i bu sekilde bildiremem. Olan bir fonksiyonu bildirebilirim ama
                // class icerisinde sifirdan bildiremem!!!

}

// AMA ILGINCTIR KI

class kdr44{
public:
    friend void asd44(kdr44);

private:
    int mx,my;
};

void f_kdr44(){
    kdr44 kdr44;
    asd44(kdr44);   // Ama bu legal. ADL konusu aslinda. Namespace'lerda daha detayli gorecegiz bunu ileride.
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// basksa bir sinifin uye fonksiyonuna friend'lik verecekseniz derleyici bu sinifi bir complete type
// olarak gormek zorunda.


class A{
public:
    void foo(int);
};

class kdr45{
public:
    friend void A::foo(int);    // gecersiz. Incomplete type kullanamayiz.
private:
    int mx,my;
};

void A::foo(int) {
    kdr45 mykdr;
    mykdr.mx = 43;      // A sinifinin kdr45 sinifina friend fonksiyonu vasitasiyla atanmasi hasebiyle
                        // kdr45 sinifinin private kismina erisebiliyoruz!!!
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class A2{
public:
    //void foo(int);
};

class dsg {
public:
    friend A2::A2();    // hata degil aslinda ama clion burada hata gosteriyor.
                        // ama derleme konusunda bi sikintisi yok yani serbest!!!
private:
    int mx,my;
};

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class dsg2{
public:
    friend class A2;
private:
    int mx, my;
};

// burada komple bir sinifa friend'lik verdik.

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// Karsilikli friend'lik vermek mumkun olabilir!
// A B'ye friendlik verdi diye B A'ya friend degildir.
// A B'ye versin, B C'ye versin. A C'ye vermis olmaz. Burasi ONEMLI. Ornegini yazmadim.

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// OPERATOR OVERLOADING
// Bu cok onemli bir arac. C++'in en onemli araclariindan bir tanesi. Gunluk kullanimda
// her an onumuze cikacak. Standart kutuphaneninin cok buyuk bir cogunlugu operator
// overloading'ten faydalaniyor.

// operator overloading fonksiyon cagirmanin baska bir alternatifi de diyebiliriz.
// Bir sinif nesnesi bir operatorun operandi oldugunda derleyici bu ifadeyi bir fonksiyon
// cagrisina donusturuyor.

#include <string>

// Operator Overloading General Rules
/*
 1. Olmayan operator overload edilemez. Mesela "@" gibi. Bunu yalnizca dilin var olan operatorleri icin kullanabiliriz.
 2. Bu mekanizma tum operatorleri dahil etmiyor. Her oparator overload edilemez. sizeof, nokta operatoru .
    scope resolution operator :: , ? :  ternary operator, .* operatoru C++'ta olan bir operator , typeid operator

 3. Bu mekanizmadan faydalanabilmek icin eger binary operatorse operandlarindan en az birinin, unary operator ise
    operandın kesinlikle bir sinif turunden ya da enum turunden olmasi gerekiyor. Yani primitif turler icin dogrudan
    operator overloading kullanamazsiniz.

 4. operator overloading'te kullanilan serler keyfi olarak isimlendirilemez. Bir kurala bagli olarak yapabiliyor.
 5. bir operator fonksiyonu sinifin statik fonksiyonu olarak bildirilemez.
    - global operator fonksiyonu ( global operator function )
    - uye operator fonksiyonu   ( member operator function )
 6. tum operator fonksiyonlari operator notasyonunu kullanmadan normal diger fonksiyonlar gibi isimleriyle
    cagirilabilirler.
    a + b       a.operator+(b)
    x > y       operator>(x,y)

    Bazi operatorlerin overload edilmesi yasaklanmisken bazilarinin global kullanilmasi yasaklanmistir.
    Sadece uye operator olarak overload edilebilir.

 7. BAzi operatorler icin yalnizca uye operator fonksiyonu bildirilebilir.
        - [ ]
        - ( )
        - ->
        - tur donusturme operator fonksiyonları
        - special member function atama operator fonksiyonları

 8. Arity of operator
    Operatorun unary ya da binary olmasi demek. Unary'ler unary gibi binary'ler binary gibi overload edilecek.
    "/" isareti binary oldugundan binary overload edilecek. iki parametresi olmak zorunda.

    Unary --> BigInt operator/(const BıgInt& x, const BigInt& y);
    Binary -> !a     operator(a)

    Eger buna uymazsak derleyici hata verir.

};

 */

class Biggy{

};

Biggy operator/(Biggy,Biggy,Biggy);   // hata var
Biggy operator/(Biggy,Biggy);   // hata yok
Biggy operator/(Biggy);   // hata var

bool operator!(Biggy);   // hata yok
bool operator!(Biggy, Biggy);   // hata var

int funcxs(){
    Biggy x,y;

    auto z1 = x/y;
    auto z2 = operator/(x,y);

    bool b1 = !x;
    bool b2 = operator!(x);

}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class kdr33 {
public:
    kdr33 operator/(kdr33); // hata yok
    // kdr33 operator/(); // hata var
    // kdr33 operator/(kdr33, kdr33); // hata var
    // class'ta islem yaptigimiz zaman eger iki parametreliyse yalnizca birisini gonderecegiz. Eger
    // tek parametreliyse gondermemize gerek yok!!

    bool operator!()const;  // Hata yok cunku member function oldugundan direkt tihs* adresi gelecektir.
};

int f_kdr33(){
    kdr33 x,y;
    auto b1 = !x;
    auto b2 = x.operator!();
    // yukaridaki iki fonksiyon ayni isi yapmaktadir.
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

// + tokeni iki islemde kullanilabilir.
//      +x      sign operator
//      x + y   addition operator

//////////////////////////////////////////////////////////////////////////////////////

// - tokeni iki islemde kullanilabilir.
//      -x      sign operator
//      x - y   subtraction operator

//////////////////////////////////////////////////////////////////////////////////////

// *ptr     dereferencing operator
// x * y    multiplication operator

//////////////////////////////////////////////////////////////////////////////////////

// &x       Address of
// a & b    bitwise and

//////////////////////////////////////////////////////////////////////////////////////

// operator fonksiyonlari icin (biri haric) varsayilan arguman bildirilemez.
// Haric olan da function call operator!!!

//////////////////////////////////////////////////////////////////////////////////////

class mds{
public:
    mds operator+(int)const;
    mds operator+(double)const;
    mds operator+(std::string)const;
};
//////////////////////////////////////////////////////////////////////////////////////

int fks(){
    int x = 0;
    int y = 20;

    auto b = x && y++;
    // short circuit behaviour
}

//////////////////////////////////////////////////////////////////////////////////////

// En onemli nokta burasi. Necoya gore kafamizi karistiracak!!!!!!!!!!!!!!!!!!!!!!!!!

// operatorlerin onceligini degistiremezsiniz! Operator oncelik yonunu de degistiremezsiniz.

//////////////////////////////////////////////////////////////////////////////////////

class Myc32{

};

Myc32 operator+(const Myc32&, const Myc32&);
Myc32 operator*(const Myc32&, const Myc32&);
Myc32 operator>(const Myc32&, const Myc32&);

int f_Myc32(){
    Myc32 m1,m2,m3,m4;
    auto b = m1 + m2 * m3 > m4; // operatorlerin oncelik sirasi normalde nasilsa simdi de aynisi olacak.
    // ( ( m1 + ( m2 * m3 ) ) > m4; )  // islem once carpma sonra toplama sonrasinda ise buyuktur seklinde ilerleyecek.
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

class Myc33{
public:
    Myc33 operator+(const Myc33&)const;
    Myc33 operator*(const Myc33&)const;
    Myc33 operator>(const Myc33&)const;
};

int f_Myc33(){
    Myc33 m1,m2,m3,m4;
    auto b1 = m1 + m2*m3 > m4;

    auto b2 = m1.operator+(m2.operator*(m3)).operator>(m4);

    m1 = m2;
    m1.operator=(m2);
}

//////////////////////////////////////////////////////////////////////////////////////
int asd33() {
    int x = 1;
    double dval = 3.4;
    char c = 'A';

    std::cout << x; // ESITTIR
    std::cout.operator<<(x); // bununla yukaridaki ayni anlama gelmekte.
}
//////////////////////////////////////////////////////////////////////////////////////
int asd378() {
    using namespace std;

    char c = 'S';
    operator<<(cout,c);
    cout.operator<<(c); // bununla yukaridaki farkli iki fonksiyonlar. Yukaridaki global operator fonksiyonu iken
                            // asagidaki ise uye fonksiyon
}

int asd373() {
    using namespace std;

    int x = 23;
    char c = 'S';
    double dval = 44;

    cout<< x << " " << dval << " " << endl;     // bunun yazilimi aslinda asagidaki gibidir.
    operator<<(operator << (cout.operator<<(x) , " ").operator<<(dval), " ").operator<<(endl);
    // Bu ikisi ayni anlamdadir. Bazisinda global operator fonksiyonunu kullanirken bazisinda uye fonksiyonunu kullanir.
}

//////////////////////////////////////////////////////////////////////////////////////

int asd3709() {
    using namespace std;

    string s1{"ali"}, s2{"can"};
    //if ( s1 + s2 == "alican") // bununla asagidaki kod aynidir!!!
    if ( operator==(operator+( s1,s2) , "alican"))
    {
        cout << "evet esit\n";
    }else{
        cout << "hayir esit degil\n";
    }
}

//////////////////////////////////////////////////////////////////////////////////////

// fonksiyonlarin geri donus degerleri eger o ifade dilin kurallari icinde lValue exp ise & turu olacak
// eger rValue exp ile & turu olmayacak.

// burada parantez ici? lValue oldugu icin ref turunden deger donduruyoruz.
// rValue olsa idi

 class dt2{
public:
    dt2& operator=(const char*);
};

int f_dt2()
{
    dt2 datem;
    datem =" 06-06-2022";
}

//////////////////////////////////////////////////////////////////////////////////////

class bigint {
public:
    bigint operator+()const;
};

int f_bigint(){
    bigint x;
    //
    //+x    // burada hicbir sey anlamadim.
}


////////////////////////////////////////////////////////////r//////////////////////////

int main() {


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
