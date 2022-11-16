#include <iostream>
// Bugun string sinifini bitirip kalilima gecilecek.
// C++20 ile spaceshift operatorune gecildi ama burada onu anlatmiyor. <=> spaceshift
// ileride stringview mi ne gorecekmisiz!!!
#include <string>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Replace fonksiyonu kaldi.
using namespace std;
void f_kdr1(){
    string str{"kadir kidir"};
    string str1{"kadir kidir"};

    str.replace(3,3,"ASDWER");
    cout << str1 << "\n";        //  --> kkadASDWERkidir

    str1.replace(0,5,10,'X');
    cout << str1 << "\n";        //  --> XXXXXXXXXX kidir

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void f_kdr2(){
    string str{"kadir kidir"};
    string str1{" ne yapacagini bilmiyor"};

    auto result = str + str1 + '&' + "kafasi cok karisik";
    cout << result << "\n";        //   kadir kidir ne yapacagini bilmiyor&kafasi cok karisik
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// iki string'i swap etmek icin kesinlikle soyle bir sey yazmayin dedi NECO
void f_kdr33333(){
    string s1;
    string s2;

    auto temp = s1;
    s1 = s2;
    s2 = temp;  // Neden boyle yazmayalim? Cunku boyle yazarsak kopyalama gerceklesir. Sinifin swap'ini cagirmaliyiz.

    s1.swap(s2);    // burada sadece pointerlar takas ediliyor!!! Bu veya
    swap(s1,s2); // Bunu da yapalim ama kesinlikle ilk ornekteki gibi yapmayalim cunku kopyalama yapildigindan
                        // dolayi cok maliyetli!!!
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cstring'den stringe ortulu donusum var. Cunku snifin cstring parametreli constructor'i explicit degil.
// Ama string'den cstring'e ortulu donusum yok
// string sinifindan const char * turune implicit type conversion yok!

void foo3(const char* p);
void f_kdr3(){
    string str33{"kadir kidir"};
    //  foo3(str); Bu sekilde cagirirsam hata olur cunku otomatik donusum yok
    //  foo3( str33.c_str() );

    puts(str33.c_str()); // bu sekilde kullanirsam eger sorun yok. NTBS gondermis oluyorum.
    // c_str kullanirken cok dikkatli olmak gerekiyor cunku kullandigimiz string sonrasinda reallocation olursa
    // c_str invalid olacak.
}

void f_kdr4(){
    string str{"kadir kidir"};
    auto x = str.c_str();

    puts(x);

    str+=" reallocation yapmasi icin uzun bir yazi yazmam lazim ve ben de yaziyorum.";

    puts(x);    // burada yazarken hata ile karsilasacagiz.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// asagidaki 3 fonksiyon ayni islevi gorur.

void f_kdr5(){
    string str{"kadir kidir"};
    auto p1 = str.data();   // p1 , char*
    auto p2 = &str[0];
    auto p3 = &*str.begin();    // eger yazdirirsak ucunun da ayni adres satiri oldugunu goruruz.
    // ama dikkat etmemiz gereken bir nokta daha var. Eger str nesnemiz bos ise yukaridaki 3 fonksiyonu da kullanmama-
    // liyiz. data fonksiyonu null karakter gonderir.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// .contains dile c++20 standartlari ile eklendi.
// contains aslinda bir arama fonksiyonu ama bize adres dondurmuyor, aranan sey var mi yok mu onu donduruyor!
// clion'da cikmiyor ilginc. Geri donus degeri boolean'dir. True ya da False

// string'in baslangictaki kontrolunu yapmak icin belli fonksiyonlar eklendi.
// starts_with gibi

void f_kdr6(){
    string str{"kadir kidir"};
    auto x = str.starts_with("kadir");
    if(x)
    {
        cout << "Varmis\n";
    }else{
        cout << "Yokmus\n";

    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Yazilar ve sayilar arasindaki donusumler
void f_kdr7(){
    int ival = 2'342'342;
    auto y = to_string(ival);
    cout << y+".jpg"<< "\n";
}

// string'den sayiya dondurmek biraz daha karisik. Bunun icin, isimlendirilmis bazi fonksiyonlari kullaniyoruz.
// stoi, stol, stoul, stoll, stof, stod,stold gibi fonksiyonlar mevcut.

void f_kdr8(){
    string str = "9737akadir";   // k'ye geldigi an orayi kullanmayacak yalnizca sayi kisimlarini kullanacak.
                                // eger kullanilamayan ilk digitin yani k'nin adresini ogrenmek istiyorsak bu sefer
                                // fonksiyonun 2. parametresini de set ediyoruz.
    auto ival = stoi(str);
    //  auto ival = stoi(str,nullptr,10); Yukaridaki ifade buna esittir. 10'luk sayi sistemi
    cout << ival<< "\n";

    std::size_t idx;
    auto ival2 = stoi(str, &idx ,10);
    cout << ival2<< " idx = "<< idx << "\n";    // burada idx'i 4 olarak yazdirir. cunku a 4. karakterdir.

    std::size_t idx2;
    auto ival3 = stoi(str, &idx2 ,16);
    cout << ival3<< " idx = "<< idx2 << "\n";    // 16'lik karakter sistemini kullaniyorum. Idx bu yüzden 5 olur
                                                 //cunku a karakterini de 16'lik sistem olarak alir.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// shrink to fit
// String ya da vektor dibi dinamik dizi konteynirlarinin size'u buyudugunda kapasitesi de otomatik olarak reallocation
// islemiyle beraber artiyor ama size'i kuculttugumuzda kapasite ayni oranda azalmiyor. Gereksiz kapasiteyi geri vermek
// icin shring to fit algoritmasini kullaniyoruz.

void f_kdr9(){
    string str(1'000'000,'A');
    cout << "str.size() = " << str.size() << "\n";
    std::cout << "str.cap : " << str.capacity() << "\n";

    str.erase(1);   // 1 indeksinden baslayarak geriye kalan tum her seyi silecek.
    cout << "str.size() = " << str.size() << "\n";
    std::cout << "str.cap : " << str.capacity() << "\n";

    str.shrink_to_fit();
    cout << "str.size() = " << str.size() << "\n";
    std::cout << "str.cap : " << str.capacity() << "\n";
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// yaziyi ters cevirmek istiyorum.
void f_kdr10(){
    string str{"kadir kidir"};
    cout << "-->"<<str<<"<--\n";
    reverse(str.begin(), str.end());    // ters ceviriyor
    cout << "-->"<<str<<"<--\n";

    sort(str.begin(),str.end());    // buyukten kucuge siraliyor
    cout << "-->"<<str<<"<--\n";    // --> addiiikkrr<--

    sort(str.begin(),str.end(),greater<char>{});    // buyukten kucuge siraliyor
    cout << "-->"<<str<<"<--\n";    // -->rrkkiiidda <--

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// C++20 ile gelen arrays fonksiyonu eklendi global fonksiyon. On bilgi
void f_kdr11() {
    string str{"ben bugun cok fazla calisamadim maalesef ve canim yaniyor"};
    cout << "-->" << str << "<--\n";    // -->ben bugun cok fazla calisamadim maalesef ve canim yaniyor<--
    auto x = erase(str, 'a');   // -->ben bugun cok fzl clismdim mlesef ve cnim yniyor<--
    cout << "-->" << str << "<--\n";




}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////KALITIM////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////KALITIM////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OOP'nin onemli konularindan bir tanesi. ( C++ Kalitim > OOP Kalitim )
// is - a relationship
// has - a relationship
// Kalitim bir nesnenin ayni zamanda baska turden bir nesne olarak kullanilabilecegine isaret ediyor.
// Kalitimin iki ana faydasi var. Birincil ana faydasi eski kodlarin yeni kodlari kullanabilmesi. Ust seviyedeki kodlarin
// alt seviyedeki kodlara bagimliligini kaldirmak. Bunun yaninda bir de code reviews avantaji var. Yani daha once yazilmis
// kodlari yeni bir sinif olustururken tekrar yazmadan var olan kodlari kullanabiliyoruz. Ama code reviews buradaki
// ana fayda degil. Adeta bir bonus gibi geliyor. Konunun tam anlanmasi icin birkac cumle yeterli degil. Yavas yavas
// ve yedire yedire ilerleyecegiz.

// Elimizde olan sinifin public interface'ini kendi class'imiza eklemek istiyoruz.
// Parent class     -- Elde ettigimiz class'a child class
// super class      -- ya da sub class diyoruz.


// Base class - Derived class ise c++ta kullanilan isimlendirme.
// kalitim islemine ise C++'ta derivation deniyor.

// C++'ta inheritance 3'e ayriliyor
// 1. Public inheritance
// 2. Protected inheritance
// 3. Private inheritance

// Inheritance tek seviyeli ya da birden fazla seviyeli olabilir.
// Tek katlı kalitim
// multi level inheritance gibi.
// Car <-- Mercedes <-- Mercedes_s500 gibi. Bu bir cok katli kalitim ornegidir.
// Birde multiple inheritance var. Bir sinifi kalitim yoluyla elde ediyorum ama iki ya da daha fazla
// parent class'i kalitim yoluyla kullaniyorum kaynak olarak.

// Class hierarcy.
// Class'larin kullanilmasi vs yani OOP'te boyle deniliyor.

// Taban sinif olarak kullanilacak sinif bir complete type olmak zorunda.
class kdr123;   // bu sekilde bir sinifi taban sinif olarak kullanamam cunku complete degil.

class Base{

};

class Der : public Base{

};

class Der2 :  Base{
    // Bu class default olarak private bir inheritance ornegidir.
};

struct Der3 :  Base{
    // Bu class default olarak public bir inheritance ornegidir.
};

// Public kalitiminda turemis sinif taban sinifin public interface'ini kendi interface'ine katiyor.

class main_kdr{
public:
    void foo();
    void func();
};

class sec_kdr : public main_kdr  {

};

void f_kdr12(){
    sec_kdr asdf;
//    asdf.foo();     // burada, main_kdr sinifindan fonksiyonu kullanabildim.
}
// kalitimda ben bunu istemiyorum yok. Public interface'de tum interface'i oldugu gibi devraliyoruz.

// protecteed bolum, kalitimin kullanildiginin garantisidir adeta.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class kdr_k1{
public:
    void foo();
    void func();
};

class kdr_k2 : public kdr_k1{

};

void f_kdr13(){
    kdr_k2 myder;
    // myder.x; // bu sekilde bir kullanim yapildigi zaman oncelikle kdr_k2 scope'unda aranacak. Bulunamazsa
                // Der'in taban sinifinda yani kdr_k1 sinifinda aranacak. Yani hem sub class'ta hem de super class'ta
                // ayni isimde bir degisken kullanirsak super class'taki degiskeni gizleyecektir.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// sub ve super class'taki ayni fonksiyonlar overloading degildirler.

class kdr_s1{
public:
    void foo(int);
};

class kdr_s2 : public kdr_s1{
public:
    void foo(double);
};

void f_kdr14(){
    kdr_s2 sub1;
    //sub1.foo(23);   // Burada super class'in degil sub class'in double parametreli fonksiyonu cagirilacak.
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ayni isimde fonksiyon varsa ve super class'takini cagirmak istiyorsak niteleyerek cagirmamiz gerekir.

class kdr_s3{
public:
    void fxyz(){
        std::cout << " selamun aleykum\n";
    }
};

class kdr_s4: public kdr_s3{
public:
    void fxyz(){
        std::cout << " aleykum selam\n";
    }
};

void f_kdr15(){
    kdr_s4 deneme;
    deneme.kdr_s3::fxyz();  // bu sekilde taban sinifi cagirabiliriz. || Selamun Aleykum
    deneme.fxyz();  // aleykum selam
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class sau{
private:
    void f_x();
};

class sau_1{
protected:
    void f_x();
};

class sau_2 : public sau{
public:
    void derfunc(){
        // f_x();  // Bu kullanim hatalidir cunku private bolume erisemem.
    }
};

class sau_3 : public sau_1{
public:
    void derfunc(){
         f_x();  // Bu kullanim hatali degildir cunku protected bolume bu sekilde erisebilirim. Protected'i ilk defa
                 // kullaniyorum!!!
    }
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sub class turunden super class turune ortulu olarak donusum var. Buna geleneksel olarak Upcasting conversion
// deniyor.
// Taban siniftan turemis sinifa donusum yaptiracaksaniz buna da downcasting deniyor.
// Upcasting bir operatore ihtiyac duymuyor.

class akdr{

};

class bkdr : public akdr{};

void f_kdr16(){
    bkdr mykdr;

    akdr* akdrptr = &mykdr; // dikkatli bakilirsa subclass'in adresi super class turunden pointer'a atanmis.
    // su an bunun neden yapildigini degil legal oldugunu goruyoruz!!!

    // Bu referans semantigiyle de mumkun.

    akdr& ak = mykdr;   // Referans semantigi ile yapilmis sekli.

    // ama bunun tam tersi olmayabilir hata aliriz.
    akdr myakdr;    // superclass turunden bir nesne olusturuldu.
//    bkdr* bkdrx = &myakdr;  // Burada hata vardir

    // Ozetle subclass'tan superclass'a ortulu donusum var ama superclass'tan subclass'a ortulu donusum yok!!!

    // Pointer ya da referans kullanmadan da donusume neden olabilirsiniz. Donusturebilirsiniz degil, neden olabilirsnz.
    // yani aslinda iyi bir sey degil.

    myakdr = mykdr; // bu da legal ama ileride ogrenecegimiz nedenlerden bunu cok cok cok ozel durumlarin disinda
    // asla kullanmiyoruz.
    // Yukaridaki olaya object slicing deniyor.


}

// void car_game(Car &cr);
// Yukaridaki fonksiyondan sunu anliyorum. Car bir base class ise, Car ile olusturulmus tum sub class'lari
// bu fonksiyon ile kullanabiliyorum!

int main() {
    f_kdr15();
    return 0;
}

