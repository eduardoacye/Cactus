/// *title* Programa en C++
/// *author* Eduardo Acuña Yeomans
/// *about* Este programa es una demostración para el programa c-cactus
/// derivado de cactus (generador de código \LaTeX  a partir de código en
/// Scheme).

#include <iostream>

using namespace std;

/// *contract* f : Real -> Real
/// *description* Function defined as $f(x)=x^2+3x-\frac{x}{0.23}+9.2$.
double f(double x)
{
    return x*x + 3x - x/.23 + 9.2;
}

/// *contract* main : Integer , String -> Integer
/// *description* Un `holamundo` común y corriente.
int main(int argc, char ** argv)
{
    cout << "Hola mundo";

    // Imprime en pantalla el valor de f evaluado en 2.
    cout << f(2) << endl;
    
    return 0;
}
