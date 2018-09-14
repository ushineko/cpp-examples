/**
 * test program
 */
#include <iostream>
#include <iomanip>
#include <map>
#include <string>

/**
 * This function is a template for printing the map. It will work for
 * any type for which the map declaration T1,T2 is valid.
 *
 * @tparam T1 first type in the map
 * @tparam T2 second type in the map
 * @param os reference to ostream
 * @return ostream
 */
template <class T1, class T2>
std::ostream & operator << (std::ostream &os, std::map<T1, T2> &map) {
    int n = 0;
    os << "hi map! " << sizeof(T1) << " " << sizeof(T2) << std::endl;
    for (auto p : map) {
        os << "[" << n++ << "] " << p.first << " "
            << p.second << std::endl;
    }
    return os;
}

int main() {

    std::map<std::string, std::string> strmap;
    strmap.insert(std::make_pair("hello","world"));
    strmap.insert(std::make_pair("hell1","worl1"));
    strmap.insert(std::make_pair("hell2","worl2"));
    strmap.insert(std::make_pair("hell3","worl3"));
    strmap.insert(std::make_pair("hell4","worl4"));
    strmap.insert(std::make_pair("hell5","worl5"));

    std::map<uint32_t, uint32_t> intmap;
    intmap.insert(std::make_pair(1,2));
    intmap.insert(std::make_pair(3,4));
    intmap.insert(std::make_pair(5,6));
    intmap.insert(std::make_pair(7,8));
    intmap.insert(std::make_pair(9,0));
    intmap.insert(std::make_pair(0,0));

    std::cout << strmap << std::endl;
    std::cout << intmap << std::endl;

    return 0;
}