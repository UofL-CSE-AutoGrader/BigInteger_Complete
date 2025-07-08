#include "Integer.hpp"
#include <iostream>
static std::tuple<Integer, Integer, Integer> extended_gcd(const Integer& a, const Integer& b) {
    Integer r0 = a, r1 = b;
    Integer s0 = Integer(1), s1 = Integer(0);
    Integer t0 = Integer(0), t1 = Integer(1);

    while (r1 != Integer(0)) {
        Integer q = r0 / r1;

        Integer remainder = r0 - q * r1;
        r0 = q;
        r1 = remainder;;

        Integer s_temp = s0 - q * s1;
        s0 = s1;
        s1 = s_temp;

        Integer t_temp = t0 - q * t1;
        t0 = t1;
        t1 = t_temp;
    }

    return {r0, s0, t0};  // gcd, x, y such that ax + by = gcd(a,b)
}



int main() {
    Integer a(1234567890);
    Integer b("98765432109876543210");

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    Integer aa("11111111111111111111111111111111111111111111111111111111111111111111");
    Integer bb("22222222222222222222222222222222222222222222222222222222222222222222");
    std::cout << "aa = " << aa << std::endl;
    std::cout << "bb = " << bb << std::endl;
    Integer c = aa + bb;
    std::cout << "a + b = " << c << std::endl;

    Integer d("12345678901234567890123456789012345678901234567890");
    Integer dd = d;
    for (int i = 0; i < 10; ++i) {
        dd *= d;
    }
    Integer ddd = dd * d;
    std::cout << "ddd/d = " << (ddd / d) << std::endl;
    if (ddd/d == dd) {
        std::cout << "ddd/d == dd" << std::endl;
    } else {
        std::cout << "ddd/d != dd" << std::endl;
    }

    Integer e = ddd % d;
    std::cout << "ddd % d = " << e << std::endl;
    if (e == Integer(0)) {
        std::cout << "ddd is divisible by d" << std::endl;
    } else {
        std::cout << "ddd is not divisible by d" << std::endl;
    }


    Integer bbb("48585747373838484843993282838457575748483829292938448");
    Integer ccc("3949494494838382839459595848328283894949049439383");
    std::cout << Integer::gcd(bbb,ccc)<<std::endl;
    std::cout << Integer::lcm(bbb,ccc)<<std::endl;

    std::cout << mod_inverse(Integer(17), Integer(3120)) << std::endl;    

    Integer val1("4855234577788899234509871023409817234098172350987690227473");
    Integer val2("44854567892341234123409850987908709869876123409812734987654321113893929239484");
    std::cout<<mod_inverse(val1, val2) << std::endl;

    Integer p1 = bbb.power(Integer(300)) % ccc;
    Integer p2 = bbb.power_mod(Integer(300), ccc);
    if (p1 == p2) {
        std::cout << "Power and modular power functions are consistent." << std::endl;
    } 
    p2 = -p2; 
    if (p2.abs() == -p2 && p1 == -(-p1)) {
        std::cout << "Assignment and negation appears consistent." << std::endl;
    } 
    Integer pp1 = p1;
    if (++p1 == pp1 + 1 && --p1 == pp1 && p1++ == pp1 && p1-- == pp1+1) {
        std::cout << "Increment and decrement operators appear consistent." << std::endl;
    } 
    return 0;
}
