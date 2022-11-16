#include <iostream>
#include <vector>
#include <cstring>
// basit bir sekilde array class'ini taklit ediyoruz!!!

using namespace std;

class intarray{
public:
    explicit intarray(size_t size) : msize(size) , mp(new int[size]){
        std::memset(mp,0,msize*sizeof(int));    // bunun icin cstring library'i include ettik.
    }

    ~intarray()
    {
        delete[]mp;
    }

    intarray(const intarray&) = delete;
    intarray operator=(const intarray&) = delete;

    int& operator[](std::size_t idx){
        return mp[idx];
    }

    const int& operator[](std::size_t idx)const {
        return mp[idx];
    }

    std::size_t size()const{
        return msize;
    }

    friend std::ostream& operator<<(std::ostream& os, const intarray& ar)
    {
        os << '[';
        for ( auto i = 0u; i < ar.size() -1; i++){
            os << ar.mp[i] << ", ";
        }
        os << ar[ar.size() - 1] << ']';
    }
private:
    int *mp;
    std::size_t msize;
};

void main_1(){
    intarray a(10);

    std::cout << a << '\n';

    for (size_t i = 0; i < a.size(); i++)
    {
        a[i] = i*2;
    }

    std::cout << a << '\n';

    a.operator[](5) =   43;

}

///////////////////////////////////////////////////////////////////////////////////

#include <string>

using namespace std;

void main_2(){
    string name{"kadir kidir"};

    for(size_t i{};i < name.size(); ++i)
    {
        std::cout << name[i] << ' ';
    }
}

///////////////////////////////////////////////////////////////////////////////////
// icerik, dereferencing operatorunun overload edilmesi
// pointer-like siniflari 2-3'e ayirmamiz mumkun.
// bunlardan bir tanesi smart pointer.

// *ptr bir lValue'dur.
// &ptr.operator*()

class sStrPtr{
public:
    // dinamik omurlu nesne adresi istiyor
    explicit sStrPtr(std::string *p) : mp{p}{}

    // * carpma isleminin overloadingi degil cunku oyle olsaydi
    // hem global bir fonksiyon olurdu hem de 2 tane parametre alacagindan
    // parametre sayisi ile de belli olurdu.
    //
    std::string& operator*()
    {
        return *mp;
    }
    ~sStrPtr(){
        delete mp;
    }


private:
    std::string *mp;
};

void main_3(){
    {
        sStrPtr ptr{new std::string{"kadir kidir"}};
        std::cout << *ptr <<"\n";
        std::cout << (*ptr).size() << "n";
        for (size_t i{}; i< (*ptr).size();i++){
            std::cout << (*ptr)[i] << ' ';
        }

    }   // bu noktada dinamik string nesnesi delete edilecek.
        // adeta garbage collector varmis gibi hareket ettiriyoruz.
}

///////////////////////////////////////////////////////////////////////////////////

// ok operatoru binary operator. Binary olarak overload edilseydi, (global olarak
// overload edilemiyor) 1 tane parametresi olmasi gerekirdi!!!
// normalde ok operatoru binary bir operator olmasina karsin unary operator gibi
// overload edilir. Bu dilin ozel bir kurali. Yani sinifin ok operator fonksiyonunun
// parametresi olmaz.

// ptr->x

// derleyici ok operatorunun sol tarafinin bir sinif turunden oldugunu gordugunde
// yani raw pointer degil de bir sinif turunden oldugunu gordugunde gidiyor bu sinifin
// ok operator fonksiyonu var mı yok mu ona bakıyor! Eger var ise nesne icin ok operator
// fonksiyonunu cagiriyor.

// Cok anlamadim ama necatinin dedigine gore
// ptr->x ifadesini
// ptr.operator->()->x ifadesine cevriliyormus. Bu ikisini yazmak arasinda bir fark yok.


class skdrPtr{
public:
    // dinamik omurlu nesne adresi istiyor
    explicit skdrPtr(std::string *p) : mp{p}{}
    // * carpma isleminin overloadingi degil cunku oyle olsaydi
    // hem global bir fonksiyon olurdu hem de 2 tane parametre alacagindan
    // parametre sayisi ile de belli olurdu.
    //

    std::string* operator->()
    {
        return mp;
    }

    std::string& operator*()
    {
        return *mp;
    }
    ~skdrPtr(){
        delete mp;
    }


private:
    std::string *mp;
};

void main_4(){
    {
        skdrPtr ptr{new std::string{"kadir kidir"}};

        std::cout << "uzunluk = " << ptr->length() << "\n";
        std::cout << "uzunluk = " << ptr.operator->()->length() << "\n";
        // yukaridaki ikili arasinda hicbir fark yok!!!
//        std::cout << *ptr <<"\n";
//        std::cout << (*ptr).size() << "n";
//        for (size_t i{}; i< (*ptr).size();i++){
//            std::cout << (*ptr)[i] << ' ';
//        }

    }   // bu noktada dinamik string nesnesi delete edilecek.
    // adeta garbage collector varmis gibi hareket ettiriyoruz.
}

// akilli pointer siniflari da aslinda bir pointeri kullaniyor. O pointera bir interface atiyor.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// template = meta kod  derleyiciye kod yazdiran kod
// derleyici eger bir sablondan bir sinifin kodunu yaziyorsa yani sablonun amaci derleyiciye bir sinif kodu yazdirmaksa
// boyle sablonlara class template deniyor AMA
// sadece class template yok
// 1. Class template
// 2. function template
// 3. variable template
// 4. alias template

template <typename T>
class akilliPtr{
public:
    // dinamik omurlu nesne adresi istiyor
    explicit akilliPtr(T *p) : mp{p}{}
    // * carpma isleminin overloadingi degil cunku oyle olsaydi
    // hem global bir fonksiyon olurdu hem de 2 tane parametre alacagindan
    // parametre sayisi ile de belli olurdu.
    //

    T* operator->()
    {
        return mp;
    }

    T& operator*()
    {
        return *mp;
    }
    ~akilliPtr(){
        delete mp;
    }


private:
    T* mp;
};

//void main_5(){
//    {
//        akilliPtr<int>;
//    }
//    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// swap ornegi templatelerde en cok duyulan ihtiyac.
//
template <typename T>
void Swap(T& r1, T&r2){
    T temp = std::move(r1);
    r1 = std::move(r2);
    r2 = std::move(temp);
}

void main_006(){
    int x = 10;
    int y = 20;
    Swap(x,y);

    std::string s1{"kadir"};
    std::string s2{"kidir"};
    Swap(s1,s2);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <memory>

class afh{
public:
    afh(){
        std::cout << "afk caghirildi\n";
    }
    ~afh(){
        std::cout << "afk yikildi\n";
    }
    void afh_f()
    {
        std::cout << "myc\n";
    }
};

int main_7(){
    std::cout << "main devam basliyor " << std::endl;

    {    // dinamik omurlu bir nesnenin bir tane sahibi olur o sahibi olan pointerin hayati bittiginde dinamik omurlu nesneyi
        // ya da kaynagi delete eder. Buradaki uygulanan stratejiye exclusive ownership strategy deniyor.
        std::unique_ptr<afh> afh2(new afh);
        afh2->afh_f(); // ya da
        (*afh2).afh_f();
    }
    std::cout << "main devam ediyor " << std::endl;

    //
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void main_8()
    {
        vector<int> ivec{ 1, 2, 3, 4, 5, 7 };
        vector<int>::iterator iter = ivec.begin();

        cout << *iter << "\n";
        ++iter;
        cout << *iter << "\n";
        cout << iter[2] << "\n";


    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// fonksiyon cagri operatoru
// fonksiyon cagri operatoru stl'de en cok overload edilen operator. Buradaki overloading mekanizmasindan bir fayda
// saglamak cogu zaman generic programlama ile alakali.

// func()
// func bir fonksiyon ismi olabilir. function designator
// func bir function pointer olabilir.
// func bir (function like) makro olabilir.
// C'de bu ucu cok yogun olarak kullanilir.

// func bir sinif trunden nesnedir ve bu sinif icin fonksiyon cagri operatoru overload edilmistir.
// func.operator()() = func() bu ikisi birbirine aynidir!!!!!!!!!!!!!!!

/*
 * []
 * ->
 * ()
 * type cast || bu dortlu operatorler global olarak overload edilemezler.
 * atama operator fonksiyonu
 */

//
class dsa1{
public:// varsayilan arguman alan tek overload operator ve global operator fonksiyonu olarak overload edilemiyor.
    void operator()()
    {
        std::cout << "operator()() cagirildi \n";
    }
    void operator()(int x)
    {
        std::cout << "operator()(int x) cagirildi \n";
    }
};

// operator fonksiyon zimbirtisinin ()() parametreleri olabilir!
// default arguman da alabilir!!! Bunun icin asagida yeni bir sinif yapiyorum!

class dsa2{
public:// varsayilan arguman alan tek overload operator ve global operator fonksiyonu olarak overload edilemiyor.

    void operator()(int x = 0)
    {
        std::cout << "operator()(int x) cagirildi x : "<<x<< "\n";
    }

    void operator()(int x = 0)const
    {
        std::cout << "operator()(int x) cagirildi x : "<<x<< "\n";
    }
};

// Functor class
// function object --> daha yaygin kullaniliyor!

// neden bu mekanizmayi kullaniyorum? normal fonksiyonlarla yapamadigim bir sey mi var??? diye soruyor neco
// ya da edindigim bir avantaj mi var!!!

class Random{
    // cagirilan function rasttgele bir sayi uretecek!!
public:
    Random(int low, int high) : mlow{low} , mhigh{high} { }

    int operator()()
    {
        return std::rand() % (mhigh - mlow + 1) + mlow;
    }
private:
    int mlow,mhigh;
};

// bu program tam aciklamada yeterli gelmeyebilir cunku bunun asil ve onemli kullanim yeri
// generic programlama!!!



void main_9()
{
    dsa1 mx;
    mx(5);

    std::cout << "----------------------------------------------------------\n";
    dsa2 my;
    my();
    std::cout << "----------------------------------------------------------\n";
    my.operator()(5);  // boyle de cagirabilirim!!!!!!


    Random rand1(37,56);
    for (int i = 0; i<100;i++) {
        std::cout << rand1() << " ";
    }

    Random rand2(1000,1435 );
    for (int i = 0; i<100;i++) {
        std::cout << rand2() << " ";
    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <random>

void main_10()
{
    mt19937 eng;
    uniform_int_distribution dist{7000,7700};

    for (int i = 0; i < 100; ++i) {
        std::cout << dist(eng) << " ";
    }
}
// Bu include ettigimiz random library'sinde yukarida kullandigimiz ornekte () overload ettigi icin
// bu ornegi verdi. Ne yaptigini cok muhtesem anlamasan da olur!
// dikkat turden bagimsiz programlama araclari olmadan fonksiyon cagri operatorunun overload edilmesi
// cok fazla fayda saglayamayabilir!

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Tur donusturme operator fonksiyonlari

// bir sinif nesnesi ortulu olabileek sekilde (implicity ) ya da explicit olarak tur donusturme operator
// fonksiyonlariyla baska bir ture donusturulebilecek!

class kdw{
public:
    operator int()const;
};

void main11(){
    kdw mykdw;

    int x;

//     x = mykdw;  // burada error verecektir cunku kdw turunden int turune donusum yok!!!
                 // ama class icerisinde bir iki ayarlama yaparsam fonksiyon yazarsam hata gider.
}

// operator double
// operator int gibi neye donustureceksem basa onu yazmaliyim.

// C++'ta tur donusturme operatoruyle referans turune de donusturme yapilabilir.
// dolayisiyla tur donusturme operator fonksiyonlarinin geri donus degeri eger donusturmede kullanilan hedef tur
// referans turu degilse fonksiyonun geri donus degeri turu de referans turu olmayacak. ama donusturmede
// hedef tur kendisi bir referans turuyse fonksiyonun geri donus degeri turu referans turu olacak!

// fonksiyonun geri donus degerini yazmadik!! Geri donus degerinin olmamasi, contructor'daki gibi geri donus
// degerinin olmadigi anlamina gelmesin, zaten operator keyword'unden sonra kullanilan tur, fonksiyonun
// geri donus turudur.

// double operator double(); // yazamayiz, syntax hatasidir!!!
// tur donusturme operatorunun yan etkisi var mi?

// bir tur donusturme operator fonksiyonunun anatomisini cikartmis olduk.
// geri donus turunu yazmiyoruz !
// const olmasi gerekyiro

class ASDFG{};

class fikibok{
public:
    operator ASDFG()const;  // yalnizca int double degil basksa bir sinifi da tur olarak gosterbilirim.
};

// onemli bir kural degisikligi c++11 ile geldi. C++ 11 oncesinde fonksiyon cagri operator fonksiyonuyla
// isteseniz de istemeseniz de implicit conversion da explicit conversion da yapabiliyorduk. Yani implicit
// donusumu engellemeye yonelik bir mekanizma yoktu. Bu da hataya sebep oldugundan tur donusturme operator
// fonksiyonlarinin da explicit olabilmesi olanagi kazandirildi modern C++ ile. Modern C++'tan once
// explicit anahtar sozcugu sadece ve sadece constructorlar icin kullanilabiliyordu. Ama simdi explicit anahtar
// sozcugu sadece constructorlar icin degil tur donusturme operator fonksiyonlari icin de kullaniliyor.

class kdz{
public:
    operator int()const;
};

void main12(){
    // eger bir donusum once standart conversion ardindan user defined conversion kullanilarak yapiliyorsa
    // derleyici bu donusumu ortulu olarak yapmak zorunda.
    // ne zaman derleyici bir donusumu otamatik olarak yapmaz??? Eger o donusum user defined conversion +
    // user defined conversion seklindeyse.

    kdz mykdz;
//    double dval = mykdz; // burada kdz'den int'e user defined, int'cen double'a ise standart conversion yapti
}

class zel{
public:
    operator int()const;
};

void main13(){
    zel myzel;
    //double dval = myzel; // burada kdz'den int'e user defined, int'cen double'a ise standart conversion yapti
    // explicit oldugu icin burada hata verecek. Cunku operator donusturme fonksiyonumu explicit tanimladigimdan
    // oturu!!! explicit conversion only demis oluyorum.
    // bu fonksiyonu ismiyle de cagirabilirdim.
    int asd;
//    asd = myzel;    // boyle cagirabildigim gibi
//    asd = myzel.operator int(); // seklinde de cagirabilirdim!!!
}


class zel2{
public:
    explicit operator int()const;
};

void main14(){
    zel2 myzel2;
    //double dval = myzel; // burada kdz'den int'e user defined, int'cen double'a ise standart conversion yapti
    // explicit oldugu icin burada hata verecek. Cunku operator donusturme fonksiyonumu explicit tanimladigimdan
    // oturu!!! explicit conversion only demis oluyorum.
    // bu fonksiyonu ismiyle de cagirabilirdim.
    int asd;
    // asd = myzel2;    // explicit oldugundan dolayi syntax hatasi ama bu hatadan kurtulmak icin static_Cast
                        // yapabilirim

//   asd = static_cast<int>(myzel2);
//   asd = myzel2.operator int();
}


/////////////////////////////////////////////////////////////////////////////////

class Counter{
public:
    explicit Counter(int val = 0) : m_c{val} { }

    Counter& operator++()       // prefix ++ operatoru
    {
        ++m_c;
        return *this;
    }

    Counter operator++(int)    // postfix ++ operatoru
    {
        auto temp{*this};
        ++*this;
        return temp;
    }

    Counter& operator--()       // previous -- operatoru
    {
        --m_c;
        return *this;
    }

    Counter operator--(int)    // postfix -- operatoru
    {
        auto temp{*this};
        --*this;
        return temp;
    }

    Counter& operator+=(int val)
    {
        m_c+= val;
        return *this;
    }

    Counter& operator-=(int val)
    {
        m_c-= val;
        return *this;
    }

    explicit operator int()const{
        return m_c;
    }

    friend std::ostream& operator<<(std::ostream& os, const Counter& cnt)
    {
        os << '[' <<cnt.m_c << ']';
    }
private:
    int m_c;
};

void main_13(){
    Counter c;
    std::cout << "c = " << c << "\n";
    ++c;
    ++c;
    ++c;
    ++c;
    ++c;
    std::cout << "c = " << c << "\n";
    c+=10; 
    std::cout << "c = " << c << "\n";

    int ival = static_cast<int>(c);

    std::cout << "ival = " << ival << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void asdfgd(){
    string name{"bilgi sayar"};

//    const char *p = name;   // bu hatali kullanim, donusum yok. Bunun yerine sinifa
    const char *p = name.c_str();   // bu sekilde kullanirsam hata almam.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class khk{
public:
    int z;
private:

};

void main_14()
{
    int x = 23;
    khk y{23};

    if (x )
    {
        // bunun icerisine girer
    }

//    if(y)
//    {
//        // buraya girmez cunku sinif turunden bool turune sinif icerisinde otomatik donusum olmöadigi icin
//        // bool operator overload mekanizmasini iceri koymamiz gerekir!
//    }

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// dikkat! operator bool islevi lojik ifade beklenen yerlerde bu islev explicit olsa da gecerli olarak kullanilabilir.
// Ama lojik ifade beklenen yerlerin disinda bi contextte kullanildigi zaman otomatik donusumu yapmayacak!
class khb{
public:
    int z;
    operator bool()const
    {
        std::cout << "operator bool func\n";
        return true;
    }
private:

};

void main_15()
{
    double x;
    khb mykhb;

    x = mykhb;  // mykhb'den x'e donusum var. mykhb'den boola user defined conversion.

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 void main_16()
 {
    std::cout << "tamsayi gir : ";
    int x;

    cin >> x;

    if (cin){   // nasil oluyor da cin sinif zimbirtisi bool gibi davraniyor?!
                // cunku operator bool fonksiyonu vardir!!!
        std::cout << "giris basarili : \n";
    }else{
        std::cout << "giris basarisiz : \n";
    }


 }

 void main_17(){
     int x;
     while( cin.operator>>(x).operator bool() ){    // bunu boyle yazman ile
                                                        // while (cin) yazmam arasinda bir fark yok!
         std::cout << x << " * " << x << " = " << x * x << '\n';
     }
}

void main_18()
{
    cin && cout;    // syntax hatasi vermez cunku istream sinifinin da ostream sinifininda operator bool fonksiyonlari
                    // var. Bunu boyle yazmam ile asagidaki giib yazmam arasinda herhangi bir fark yok!
    cin.operator bool() && cout.operator bool();

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//scoped enum
enum class wday{
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
};

std::ostream& operator<<(std::ostream& os, const wday& wd)
{
    const char *const pdays[] = {"sunday", "monday","Tuesday","Wednesday", \
    "Thursday","Friday","Saturday"};
    return os << pdays[static_cast<int>(wd)];
}

wday&operator++(wday& wd){
       return wd = (wd == wday::Saturday ? wday::Sunday : static_cast<wday>(static_cast<int>(wd) + 1));
    }

void main_19(){
    wday aw{wday::Sunday};

    for ( ; ;) {
        ++aw;
        std::cout << aw << "\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    main_19();

//    std::cout << "Hello, World!" << std::endl;
    return 0;
}
