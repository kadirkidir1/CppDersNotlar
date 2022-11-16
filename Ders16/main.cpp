#include <iostream>

// OPERATOR OVERLOADING
// Siniflarin static uye fonksiyonlarini operator overloading olarak kullanamayiz!!
// yalnizca non-static fonksiyonlar
// Const bu dilin en muhim seylerden birisi!!!

// Sadece uye operator fonksiyonu olsaydı da global operator fonksiyonu olmasaydı?
// Bunun nedeni cok onemli.
// Mesela x + 5 yazip + operatorune overload ettigimizde uye fonksiyona//
// x.operator+(5) olarak gecebilir ama 5 + x yazdigimiz zaman
// 5.operator+(x) gibi bir sey soz konusu olamaz. Bunun icin global operator overloading'leri
// cagirmak zorunludur.
// operator(5,x) --> bu sekilde global operator fonksiyonu cagirilir.
// Bu nedenlerden bir tanesi.

// 2.
// Bunu cok kotu anlatti anlamadim.

class bigint{

};

std::ostream& operator<<(std::ostream&, const bigint&);

///////////////////////////////////////////////////////////////////////////////////////

// simetrik operatorleri kesinlikle global operator olarak yaziyor NECO. Ne demek
// simetrik operator. Bir binary operator.
// a op b ne anlamina geliyorsa
// b op a ayni anlama geliyorsa bu simetrik operatordur.
// Ornegin a + b ile b + a ayni islemi yapiyorsa bu simetrik operatordur.

// Sinif nesnesini degistiren operatorler kesinlikle uye operator fonksiyon olmali.
// Unary operatorler genelde uye fonksiyon olarak yaziliyor.

// diyelimki sinifin atama operator fonksiyonu var, toplama operator fonksiyonu da var.
// bu ikisi var diye += var anlamina gelmez.

class kdk {
public:
    kdk& operator=(int);
    kdk  operator+(int)const;
    // bu ikisi var diye += operatoru var diyemeyiz!!!
};
///////////////////////////////////////////////////////////////////////////////////////

// nesneleri int gibi kullanilacak bir sinif olsun.
// yani int wrapper'i olacak. C++'in en iyi yonlerinden birisi wrapper'lar.

// BU WRAPPER'LAR NE ACABA!SORSAM YA DA ARASTIRSAM IYI OLABILIR //

// STRONG TYPES --> Ileri C++ kursu konusu.
// singleton'i da C++ kursunda çok detayli isliyorlarmis!!


#include "mint.h"
void f_mint(){

    // std::cout << mx;    // mx'in degerini yazdirmak istiyorum bu yuzden operator
    // overloading yapmam gerekiyor. Bu sekilde yazdirirsam Mint turu tanimli
    // olmadigindan yani custom tip oldugundan yazdirma islemi yapmayacaktir.
    // GOTO CLASS XXX

    Mint m1{12};
    Mint m2{15};
    std::cout << m1 << " " << m2 << "\n";

    // Bu kod, mint.cpp ve mint.h calistiginda mint turunden bir degiskenin
    // cout ile yazdirilabilecegini gorduk. Bunu << token'inin operator overload
    // edilmesi ile yapabildik.
}

void fcn33()
{
    using namespace std;

    std::cout.setf(std::ios::boolalpha);    // bool degeri true olarak yazar.
                                                 // eger boolnoalpha secilirse true yerine 1 yazilir!!!

    Mint m1{12},m2{22}, m3 {38};

    // std::cout << m1 == m2; Bu sekilde yazim hatalidir cunku operator onceligi ihlal edilir. Asagidaki gibi yazilmali.
    std::cout << (m1 == m2) <<"/n";
    std::cout << (m2 == m3) <<"/n";
    std::cout << (m2 < m3)  <<"/n";
}

//// C++20 sonrasi kurallar icin spaceship'li bir seyler varmis onu anlatmiyor. <=>

////////////////////////ARITMETIK OPERATORLER////////////////////////////

// x = x + y yazabiliyiorsam x+=y de yazabilmeliyim.

//
// Prefix           Postfix
//  ++x               x++
//  --x               x--
// lValue           rValue
// derleyici son ek ++ oldugunu dummy int'ten anliyor.

// global function ile - free function  ya da stand-alone function ayni seyleri ifade ediyor.
//class scope'ta olmayan fonksiyonlar. Bunlar namespace scope'ta

// Global bir fonksiyonu friend degilse sinif icinde tanimlayamazsiniz.
// Ama friend anahtar sozcuguyle tanimlanmissa ve sinifin icinde tanimlanmissa artik global function
// yani member function degil.

// global degiskenler multithread fonksiyonda senkronize edilmesi gerekir. Otomatik omurlu bir degiskenin
// isinizi gordugu yerde global degisken kullanirsaniz bu size sorunlar yaratabilir!

// static initialization fiasco'ya dikkat! Arastir bi nedir ne degildir

// LAZY INITIALIZATION
//
/*
    inline Myc363& get_instance{
        static Myc363 m;
        return m;
    };
    // initialization only need!!
    // Buna lazy init deniyor, global yerine kullanilabilen daha avantajli bir init turu ama
    // ileride daha fazla detayli anlatacagini dusunuyorum. Burada static degiskenler yalnizca
    // get_instance fonksiyonu cagirildiginde olusturulacak ama global degiskenler programin
    // basladigindan beri programa maaliyet olusturacak
    // singletone deyip deyip duruyor ama tam olarak anlatmiyor Bir design pattern!
*/

#include <random>

std::mt19937& rg19937(){
    //std::random_device{} --> Temporary object!!!
    static std::mt19937 eng{std::random_device{}() };
    return eng;
    // bu konuyla alakali degildi, telegram grubundan soru sorduklari icin derste buralari anlatti
    // global degiskenlerle alakli. Bu ornekte random sinifini anlatti. Yalnizca cagirdigimizda
    // bize bir random uretiyor burada onu gorduk!
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// [] overload edilmesi
// * overload edilmesi
// -> operatorunun overload edilmesi
// Bunlar biraz farkli kurallara sahip ve farkli amaclarla kkullaniliyor.

// () overload edilmesi
// type-cast operator function

// enum turleri icin overloading

// & operatorunun overload edilmesini Neco onermiyor. Bir seyin yapilabilir olmasi onun yapilmasi
// gerektigi anlamina gelmiyoR!!!

////////////////////////////////////////////////////////////////////////////////////////////////////

// [] fonksiyonu dogal bir cagrisim yapiyorsa overload edilmesi.
// primitif turler icin hangi cagrisimi yapiyorki? [] bir pointer operatoru!!!

// ptr[n] --> *(ptr + n) // Bunlar ayni anlama donusur.
// yukaridaki ikisini ayni yerde yazabilirsiniz.

// array-like siniflar
// 1.si vector sinifi. Bir dinamik diziyi temsil ediyor.

////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>

void fcn3345(){
    using namespace std;

    vector<int> ivec(12);

    ivec[5];    // burada ivec'in 5. degerine ulasiyorum vector sinfinda.
    ivec.operator[](5); // Aslinda yukaridaki cagrisimda koseli parantez tokeni operator
    // overload olarak kullaniliyor.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
int g;

class kdr_54{
public:
    int& operator[](int i)
    {
        std::cout << "kdr:: operator[]() i =" << i << std::endl;
        return g;
    }
};

void koseprntz()
{
    kdr_54 asd;
    asd[5]; // burada overload edilir ve yukaridaki fonksiyon calisir. Ayrica bunu su sekilde de cagirabilirdim.

    asd.operator[](5);  // ikisi de ayni anlama gelmektedir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// string sinifi da array-like bir class'tir.

void for_string()
{
    std::string name{"kadir kidir"};

    for (size_t i{}; i < name.size(); i++)
    {
        std::cout << name[i] << " ";
    }
}

// map sinifi da [] operatorunu overload eder ama en guzel ornegi array sinifi.
// array sinifi bi wrapper C dizilerini kullaniyor.

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>

void fcn_array()
{
    std::array<int , 10> ar;
    for(int i = 0; i<10; i++)
    {
        ar[i] = i;
        // bunun yerine
        ar.operator[](i) = i;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void fcn656() {
    const std::vector<int> ivec{1, 2, 3, 4, 5, 6};
    auto val = ivec[3];
    ivec[4] = 999;  // const oldugu icin bu kullanimda hata mevcuttur.
    // hata olmasinin sebebi const overloading.
}
////////////////////////////////////////////////////////////////////////////////////////////////////

class asd234{
public:
    void func()const;
    void func();
};

void fcn_asd234()
{
    asd234 a;
    const asd234 b;

    a.func();
    b.func();

}

////////////////////////////////////////////////////////////////////////////////////////////////////

class ivector{
public:
    int& operator[](std::size_t idx);
    const int& operator[](std::size_t idx)const;
};

void f_ivector()
{
    ivector asd1;

    auto val = asd1[2];
    asd1[3] = 24;   // herhangi bir kata ile karsilasilmaz. const olmayan function cagirildi.

    const ivector asd2;

    auto val2 = asd2[5];    // su an const olmayan fonksiyon cagirildi.
    asd2[3] = 45;   // su an const olan fonksiyon cagirildi ve hata ile karsilasildi.
}

int main() {
        std::cout << "esit "  << std::endl;

    return 0;
}

















































