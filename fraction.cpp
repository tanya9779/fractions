#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

class Fraction {
        private:
                int nominator; // числитель
                int denominator; // знаменатель

                void simplify() {
                        if (denominator < 0) {
                                nominator *= -1;
                                denominator *= -1;
                        }
                        if ( abs(nominator) < 2 ) return;
                        int gcd = getGCD( abs(nominator), denominator ); // НОД
                        nominator /= gcd;
                        denominator /= gcd;
                }
        public:
                Fraction( int n, int d ) : nominator(n), denominator(d) {
                        simplify(); // упростить дробь
                }

                Fraction() : nominator(0), denominator(1) {}
                Fraction( const Fraction &other ) : nominator( other.getNominator() ), denominator( other.getDenominator() ) {}

                Fraction( int value ) : nominator(value), denominator(1) {}

                int getNominator() const { return nominator; }
                int getDenominator() const { return denominator; }

                double getValue() const {
                        return static_cast<double>(getNominator()) / static_cast<double>(getDenominator());
                }

                int compareTo( const Fraction &other ) const {
                        return getNominator() * other.getDenominator() - getDenominator() * other.getNominator();
                }

                int getGCD( int a, int b ) {
                        while( a != b ) {
                                if (a > b) a -= b; else b -= a;
                        }
                        return a;
                }
                Fraction operator-() {
                        return Fraction(-getNominator(), getDenominator());
                }
                Fraction operator+(const Fraction &a) {
                        int commonDenominator = a.getDenominator() * getDenominator();
                        int commonNominator = a.getNominator() * getDenominator() + getNominator() * a.getDenominator();
                        return Fraction(commonNominator, commonDenominator);
                }

  // Упр.2 - недостающая функция - оператор-   
                Fraction operator-(const Fraction &a) {
                        int commonDenominator = a.getDenominator() * getDenominator();
                        int commonNominator = a.getNominator() * getDenominator() - getNominator() * a.getDenominator();
                        return Fraction(commonNominator, commonDenominator);
                }

                Fraction operator*(const Fraction &a) {
                        return Fraction(getNominator() * a.getNominator(), getDenominator() * a.getDenominator());
                }

                Fraction operator/(const Fraction &a) {
                        return Fraction(getNominator() * a.getDenominator(), getDenominator() * a.getNominator());
                }

                friend Fraction operator+(Fraction &a, const int b);
                friend Fraction operator+(const int b, Fraction &a);
                                                            
                friend Fraction operator-(Fraction &a, const int b);
                friend Fraction operator-(const int b, Fraction &a);
                                                            
                friend Fraction operator*(Fraction &a, const int b);
                friend Fraction operator*(const int b, Fraction &a);
                                                            
                friend Fraction operator/(Fraction &a, const int b);
                friend Fraction operator/(const int b, Fraction &a);
               
                bool operator==(const Fraction &a) { return compareTo(a) == 0; }
// Упр. 1 - перегрузка операторов сравнения
                bool operator<(const Fraction &a) { return compareTo(a) < 0; }
                bool operator>(const Fraction &a) { return compareTo(a) > 0; }
                bool operator<=(const Fraction &a) { return compareTo(a) <= 0; }
                bool operator>=(const Fraction &a) { return compareTo(a) >= 0; }
                
}; // end of class Fraction

// Упр. 3 - используем уже написнные операторы с Fraction (operator) Fraction
Fraction operator+(Fraction &a, const int b) { return a.operator+( Fraction(b) ); }         
Fraction operator+(const int b, Fraction &a) { return a.operator+( Fraction(b) ); }
         
Fraction operator-(Fraction &a, const int b) { return a.operator-( Fraction(b) ); }         
Fraction operator-(const int b, Fraction &a) { return Fraction(b).operator-(a); }         

Fraction operator*(Fraction &a, const int b) { return a.operator*( Fraction(b) ); }         
Fraction operator*(const int b, Fraction &a) { return a.operator*( Fraction(b) ); }         

Fraction operator/(Fraction &a, const int b) { return a.operator/( Fraction(b) ); }         
Fraction operator/(const int b, Fraction &a) { return Fraction(b).operator/(a); }         

// оператор вывода в поток для дроби
std::ostream &operator<<(std::ostream &stream, const Fraction& a) {
        return stream << a.getNominator() << "/" << a.getDenominator();
}

// функция возведения в степень
Fraction power(const Fraction &fraction, int power) {
        return (power < 0) ?
                        Fraction((int)pow(fraction.getDenominator(), -power), (int)pow(fraction.getNominator(), -power)) :
                        Fraction((int)pow(fraction.getNominator(), power), (int)pow(fraction.getDenominator(), power));
}

int main(int argc, char **argv) {
        Fraction a(-4, 7), b(1, 3), c(0, 4);
        std::cout << "a = " << a << "    b= " << b << "    c = " << c << std::endl;
        std::cout << "a * c = " << (a * c) << std::endl;
        std::cout << "a + b = " << (a + b) << std::endl;
        std::cout << "a - b = " << (a - b) << std::endl;
        std::cout << "a * b = " << (a * b) << std::endl;
        std::cout << "a / b = " << (a / b) << std::endl;

        std::cout << "a + 1 = " << (a + 1) << std::endl;
        std::cout << "1 + a = " << (1 + a) << std::endl;
        std::cout << "a - 1 = " << (a - 1) << std::endl;
        std::cout << "1 - a = " << (1 - a) << std::endl;
        std::cout << "a * 2 = " << (a * 2) << std::endl;
        std::cout << "2 * a = " << (2 * a) << std::endl;
        std::cout << "a / 2 = " << a / 2 << std::endl;
        std::cout << "2 / a = " << 2 / a << std::endl;
        std::cout << "(a < b) = " << (a < b) << std::endl;
        std::cout << "(a <= b) = " << (a <= b) << "    (a <= a) = " << (a <= a) << std::endl;
        std::cout << "(a > b) = " << (a > b) << std::endl;
        std::cout << "(a >= b) = " << (a >= b) << "    (a >= a) = " << (a >= a) << std::endl;
        std::cout << "(1/4)^(-1) = " << power(Fraction(1, 4), -1) << std::endl;

  // только для отладки, чтобы окно запущенной программы не закрывалось
  std::cout << "enter any integer number...";
  int z;
  std::cin >> z;


}
