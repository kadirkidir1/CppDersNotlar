#include <iostream>
#include <string>
#include <iterator>

void f_kdr0()
{
    std::string s1;
    std::string s2{};

    auto len = s1.length();
    std::size_t len2 = s2.length();
    // size ile len tamamen ayni isi yapiyor.

    // c++17ile size artik global olarak da sunuluyor.
    std::size(s1);  // bu sekilde elde edebilirim.

    // EMPTY : container'in bos olup olmadigini kontrol eder. isempty anlaminda. Bool doner.
    bool bs1 = s1.empty();
    std::cout << std::boolalpha << bs1 << "\n"; // cevap olarak true doner.

    // Clear: Stringin elemanlarini silmek icin kullanilir. Konteyniri bosaltir. Member function

    // Capacity: Dinamik bellekte tahsis edilen total alan. Size'dan farkli. Bos alanlari da kapsar. Eger size
    // capacity'i gecerse, reallocation islemi uygulanir.

    // Reserve: Capacity'i bastan ayarlayabilirim.
    s1.reserve(10'000);  // gibi. Tam 10000 degil, minimum.

    // Erase ve clear fonksiyonu karakterleri siler, size boyutunu dusurur ama kapasiteyi dusurmez. Kapasiteyi dusurmek
    // icin baska fonksiyonlar kullanilmalidir.

    //
}

void f_kdr1()
{
    // Capacity'nin asim ornegidir. Size capacity'i gecince reallocation yapilir. Bunu goruyoruz.
    std::string str{"kadir kidir 1996 istanbul"};
    auto cap = str.capacity();
    int cnt{};
    std::cout << cnt++ << "size : " << str.size() << " cap : " << str.capacity() << "\n";

    while(1){
        str.push_back('a');
        if ( str.capacity() > cap ) // Reallocation yapilmistir.
        {
            std::cout << cnt++ << "size : " << str.size() << " cap : " << str.capacity() << "\n";
            cap = str.capacity();
            (void)getchar();
        }
    }
}

void f_kdr2()
{
    char s[] = "kadir kidirov";
    std::string s1{s + 6};  // burada adres'ten itibaren Null karakter gorene kadar olusturulur.
    std::cout << "s1.size " << s1.size() << "\n";
    std::cout << "[" << s1 << "]"<< "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_kdr3(){
    std::string s1{"kadir kidirov"};
    std::string s2 = s1;                // bunun icin copy ctor cagirilir
    std::string s3(s1);                 // bunun icin copy ctor cagirilir
    auto s4 = std::move(s1);   // bunun icin move ctor cagirilir
    std::cout << "[" << s1 << "]"<< "\n";   // kaynagi calindigi icin icerisi bos
    std::cout << "[" << s4 << "]"<< "\n";   // yazi burada yazdirilir
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string foo1(){
    std::string s2{"kadirkidir"};
    return s2;
}

void f_kdr4()
{
    std::string str;
    str = foo1();   // foo1() fonksiyonu rValue oldugundan burada tasima semantigi devreye girecek!!!

    //////////////////////////

    char str2[] = "bugun persembe haftanin dorduncu gunu";
    std::string s(str2,5);  // data constructor.
    std::cout << "s= " << s << "\n";

    std::string s3(str2+6,str2+14);  // range constructor.
    std::cout << "s3= " << s3 << "\n";

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void f_kdr5() {
    std::string str1;
    std::cout << "adini gir  ";
    getline(std::cin, str1); // eger cin kullansaydik yalnizca bosluk karakterine kadar alacakti.
    // yani cin ile kadir kidir alsaydim str1 icerisine yalnizca kadir'i alacakti.
    std::cout << "adin " << str1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// std::string str('A');   // boyle bir constructor yok. Parametresi char olan bir constructor yok
    // ama bir tane karakter almanin baska yollari da var!!!
    std::string s2("A");    // bu sekilde tke bir char alabilirim. YA DA
    std::string s3(1, 'A');  // bu sekilde de alabilirim.
    std::string s4{'A'};  // bu sekilde de alabilirim.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_kdr6(){  // Substring constructor
    std::string s1{"kadir kidirov"};
    std::string s2{s1,6};   // s1'in  6 karakterinden sonuna kadar s2'ye ata.
    std::string s3{s1,6,3};   // s1'in  6 karakterinden sonra 3 karakter al.
    std::string s4{s1,6,3000};   // s1'in  6 karakterinden sonra sonuna kadar git. UB degil

    std::cout << "[" << s2 << "]"<< "\n";   // kidirov
    std::cout << "[" << s3 << "]"<< "\n";   // kid
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//npos sinifin constexpr static veri elemani. Bunu cok iyi anlamaliyiz.
void f_kdr7(){
    std::cout << std::string::npos << "\n"; // 18446744073709551615 gibi bir sey yazdiriyor.
    // iki tane onemli islevi var.
    // birinci onemli islevi arama fonksiyonlari.

    std::string sdk{"kadir kidirov"};
    auto idx = sdk.find('v');   // find komutu bulursa buldugunu noktanin indeksini gonderiyor.
    auto idx2 = sdk.find('s');   //
    // Ama bulamazsa stringin npos'unu donduruyor. Nullptr ya da 0 degil.
    std::cout << "[" << idx << "]"<< "\n";   // 12 olarak yazar. Ama aranan deger bulunamasaydi!
    std::cout << "[" << idx2 << "]"<< "\n";   // burada ise npos degerini yazdirdi. if kontroluyle
    // ilgili aramanin true ya da false oldugu kontrol edilip ona gore islem yapilabilir. Ama bunun yerine
    // su sekilde bir kullanim yayginlasmistir ve necati de bu kullanimi tavsiye ediyor.

    if( sdk.find('t'); idx!= std::string::npos){
    //
    }else{

    }
    //=======================================================//
    // islev npos
    // indeksli substring'de tum degerleri yazdirmak istiyorsam en mantiklisi npos kullanmak yani
    std::string s4{sdk,6,std::string::npos};   // s1'in  6 karakterinden sonra sonuna kadar git. UB degil
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_kdr8(){
    std::string str{"kadir kidirov"};

    str[2] = '!';   // degisim bu sekilde yapilabilir ama gecerli indeks girilmezse exception throw etmez. UB olur.

    std::cout << static_cast<int>(str[str.size()]) << "\n"; // bu degerin null karakter olma garantisi var.

    // at komutu = koseli parantez ile ayni islevi gorur ama farki exception throw eder!!!

    try{
        auto c = str.at(34);    // bu exception throw'dur. Catch'e girer.
        auto d = str[76];       // bu exception throw degildir. Catch'e girmez.
    }
    catch (const std::exception& ex){
        /// buraya giriyor iste bir seyler yazilabilir!!!
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// str.front ilk ogeye eristirirken
// str.back son ogeye eristiyor.
// .begin baslangic adresini adresini verirken .end bitis adresini verir.

void f_kdr9() {
    std::string kdr{"kadir kidirova"};
    std::string khk{"seb vettel"};

    for (auto iter = kdr.begin(); iter != kdr.end(); iter++) {
        std::cout << *iter;
    }
    // ama bunu kullanmak yerine range base for loop da kullanabiliriz ve daha pratik!!!
    for(char c : kdr ){

    }

    for(char &c : khk ){
        // ref kullanirsam yaziyi degistirmis olurum dikkat
        c = '*';
    }
    std::cout << " "<< khk; // khk'nin tum elemanlari ******* olacak cunku dikkat


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_kdr10(){
    std::string str{"kadir kidir"};
    std::string stk{"cemal madan"};

    std::cout << str << "\n";

    str = stk;  /// copy assingment
    std::cout << str << "\n";       // str'nin icerigi degisti, stk ise ayni kaldi. Cunku copy ctor!!!

    std::string tkp;
    tkp = std::move(stk);

    std::cout << "tkp"<< tkp << "\n";
    std::cout << "stk"<< "stk" << "\n";

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// char parametreli constructor yok ama olusturulmus stringe tek bir karakter atayabiliriz.
// char parametreli constructor yok, char parametreli atama var!!!

// Nicolas'in kitabını telegramdan paylasmis, STL konusunda cok iyi oldugunu soyledi Neco.
// kesinlikle edinip STL tarafini 3-4 kez okumamizi soyledi.
// 1:31:00'da kitabi anlatiyor tablolarla birlikte.

// Kitapta ilgili tabloya bakildiginde string'e assign ile her seyin atandigini goruyoruz. Asagida
// onunla ilgili bir ornek var.
#include <vector>
void f_kdr11(){
    std::string str{"kadir kidir"};
    str.assign(20,'A'); // assing ile str stringine 20 tane A atadim
    std::cout << str << '\n';

    /////////////////////////////////

    std::string stk{" kadirov"};
    std::vector<char> vec{'a','b','c'};
    stk.assign(vec.begin(),vec.end());
    std::cout << stk << '\n';   // cikti abc olur.
    // assign ile geri donus degeri *this oldugu icin yine kendisiyle islem yapabiliriz!!!

    str.assign(str,5,3).size(); // goruldugu gibi .size kullanabiliyorum yukaridaki *this olayindan dolayi.

    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     pushback ile sondan ekleme yapabiliyorum.
//     += fonksiyonu ile stringimi buyultebilirim.
void f_kdr12(){
    std::string str{"kadi"};
    str+='r';   // kadi olan str dizisi bu hamleyle beraber kadir olur.
    std::cout<<str<<"\n";
}

// "\n" --> Bu bir string literally. Bunun turu const char[2] ||| Bunu bir pointer'a atayabilirsiniz.
// array decayle bunun elemanlarina erisip yazariz.

// '\n' -->Bunun turu ise char. Bu bir karakter sabiti. ||| Bunu bir tamsayiya atayabilirsiniz.

void f_kdr13(){
    std::string str{};

    for(char c = 'a'; c<='z'; c++)
    {// dizinin sonuna surekli yeni bir harf ekledi.
        str.push_back(c);
        std::cout << str << '\n';
    }

}

void f_kdr14(){
    std::string str{"basovksi "};
    std::string s{"freddy "};

    str.append(5,'X');  // tablo incelenirse, append fonksiyonu cok daha kabiliyetli.
    str.append("mozerensko ");
    str.append(s,0);
    str.append(s,3,4);

    std::cout << str << "\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// resize fonksiyonu. Bu fonksiyonu reserve ile karistirmayin. Reserve kapasiteyi arttiriyor.

void f_kdr15(){
    std::string str{"kadir"};

    std::cout << "str.length() = " << str.length() << '\n'; // output : 5
    str.resize(25);
    std::cout << "str.length() = " << str.length() << '\n'; // output : 25  // Sona null karakter atiyor.
    // resize fonksiyonu hem boyut buyulturken hem de boyutu kucultur.
    str.resize(2);
    std::cout << "str.length() = " << str.length() << '\n'; // output : 2   // sondaki karakterler siliniyor!!!
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Index parametreli insert fonksiyonlar
// Birde iterator isteyen insert fonksiyonlari var ama onu burada anlatmayacak!
void f_kdr16(){
    std::string str{"kadir"};

    str.insert(1, "ali");    // index tabanli insert fonksiyonlarinda birinci parametre herzaman
                                    // index'e isaret eder! Burada insert ettigi zaman kaliadir olacak.
    std::cout << "str = " << str << '\n';

    std::string str1{"kadir"};
    std::string strin{" kidirov"};
    str1.insert(str1.size(),strin);
    std::cout << "str1 = " << str1 << '\n';

    std::string str2{"kadir"};
    std::string strin2{" kidirov"};
    str2.insert(str2.size(),strin2,3);   // 3 parametreli substring ornegi
    std::cout << "str2 = " << str2 << '\n';

    // index parametreli indeks fonksiyonlari *this donduruyor.

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// iterator indeksiyle insert
void f_kdr17(){
    std::string str{"kadir"};
    std::cout << "[" << str << "]\n";

    str.insert(str.begin(),'!');    //
    str.insert(str.begin(),{'w','a','s','d'});    // Initializer list
    str.insert(str.begin(),20, 'N');    // 20 tane N karakteri ekliyorum
    std::cout << "str2 = " << str << '\n';



}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Silme islemlerine geciyoruz.
void f_kdr18(){
    std::string str{"kadir kidir"};

    auto x =str.erase(str.begin()+2);    // d karakterini siliyorum
                                        // burada str.erase'nin geri donus degeri, silinen ogeden sonraki adrestir.

    std::cout << str << "\n";           //kair kidir olur.
    std::cout << "silinen adresten sonraki karakter : " << *x << "\n";  // i yazdirilir.
}

            //*//*//*//*//*//*//*//*//*//*//*//*//*//
void f_kdr19()
{
    std::string sline;

    std::cout << "please, enter a text";
    std::getline(std::cin,sline);

    while(!sline.empty()){
        std::cout << "-->" <<  sline << "<--\n";
        sline.erase(sline.begin());
    }
}

//*//*//*//*//*//*//*//*//*//*//*//*//*//
void f_kdr20(){
    std::string str{"atakan"};

    str.erase(str.begin() + 1, str.end() - 1 ); // bastan 2. sondan 2. karaktarler arasindakini sil dedim
                                                         // yani range verdim.
    std::cout << "-->"  << str << "<--\n";               // burada yazdirilan yazi -->an<-- olacak.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void f_kdr21(){
    std::string str{"atakan"};
    // index ile yapilan islemlerde, bir indeks girdigimizde o indeksi silmiyor, o indeksten baslayarak geriye kalanlari
    // siliyor.

    str.erase(2);   // t 1. parametre ise at'den sonrakileri silecek.
    std::cout << "-->"  << str << "<--\n";               // burada yazdirilan yazi -->at<--

    std::string str1{"atakan"};
    // index ile yapilan islemlerde, bir indeks girdigimizde o indeksi silmiyor, o indeksten sonraki geriye kalanlari
    // siliyor.

    str1.erase(2 ,2);   // 2. parametreden sonra 2 karakter siliyorum
    std::cout << "-->"  << str1 << "<--\n";               // burada yazdirilan yazi -->atan<--

    str.erase();
    str.erase(0,str.npos);  // bu ve ustteki iki fonksiyon aslinda ayni islemleri yapiyor.


    // tek bir karakter silmek istiyorsam iteratore gore
    str.erase(str.begin() + 3 );    // seklinde yapabilirim. Indekse gore7
    str.erase(3 ,1 );    // seklinde yapabilirim. Yalnizca 3. karakteri siler!
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// silmenin bir yolu da pop_back fonksiyonu
void f_kdr22(){
    std::string str{"CANIM ANAM"};

    while (!str.empty())
    {
        std::cout << "-->" << str << "<--\n";
        str.pop_back(); // bunun bir geri donus degeri yok!!!
    }
}
    // karakter silmenin bir yolu da resize! Silme sondan yapilir
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MULAKAT SORUSU
// Kac farkli sekilde, string'in boyutunu 0'a indirebiliriz.
void f_34576(){
    std::string s{"kadirkidir"};

    s.clear();
    s.erase();
    s.erase(0,std::string::npos);
    s.erase(0,s.size());
    s.erase(s.begin(), s.end());
    s.resize(0);
    s = "";
    s = {};
    s = std::string{};
    s.assign("");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Cok kisa regex diye bir seyden bahsetti ileride anlatacakmis!!!
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void f_kdr23(){
    std::string s{"ISTANBUL ISTANBUL GUZEL ISTANBULX"};
    // arama fonksiyonlarinin hepsinin ortak ozelligi sonuc olarak adres donmesi, bulamazsa da npos donmesi!
    //find
    //rfind
    //find_first_of
    //find_last_of
    //find_first_not_of
    //find_last_not_of
    auto x1 = s.find('B');  // 0. indeksten baslayarak B karakterini arayacak ve adresini donecek.
    auto x2 = s.find('B',13);  // 13. indeksten baslayarak B karakterini arayacak ve adresini donecek.

    // find_first_of'ta olaylar biraz degisiyor. iki karakter giriyoruz diyelim, i ve l. Ilk olarak hangisini bulursa
    // onun adresini donduruyor

    auto x3 = s.find_first_of("XQ");
    std::cout << "ilgili dizin : "<< x3 << std::endl;   // Cevap 32 olur.

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// substring sinifi biraz maaliyetli bir islem
void f_kdr24(){
    std::string s{"ramazan gulmez"};
    auto str = s.substr(5,4);   // 5. karakterden baslayip 4 tane karakteri str'ye ata.

    std::cout << "-->" << str << "<--\n";     // an g yazdirilir.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// karsilastirma icin, ornegin ankara ve antalya'yi karsilastiralim. alfabetik olarak karsilastirir
// t > k oldugu oldugu icin antalya > ankara olurdu.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// .compare() fonksiyonu
// 0 donerse yazilar esit 1 donerse 1. yazi buyuk negatif donerse 2. yazi buyuk.

// Bundan sonraki derslerde kalitima gecilicek.

// Kitabın adi The C++ Standart Library Second Edition -- Nicolai M. Josuttis
int main() {
    f_kdr24();
    return 0;
}