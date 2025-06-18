#include "ComplexNumber.h"
#include <string>

ComplexNumber::ComplexNumber(double real, double imaginary) : m_real(real), m_imaginary(imaginary)
{
    // This is empty on purpose!
}

ComplexNumber::ComplexNumber() : ComplexNumber(0, 0)
{
    // This is empty on purpose!
}

/*
* The current value of m_real.
* 
* @return The value of m_real.
*/
double ComplexNumber::getReal() const
{
    return this->m_real;
}

/*
 * Sets the m_real to a new value.
 *
 * @param real [IN] The new value for m_real.
 */
void ComplexNumber::setReal(double real)
{
    this->m_real = real;
}

/*
 * The current value of m_imaginary.
 *
 * @return The value of m_imaginary.
 */
double ComplexNumber::getImaginary() const
{
    return this->m_imaginary;
}

/*
* Sets the m_imaginary to a new value.
* 
* @param imaginary [IN] The new value for m_imaginary.
*/
void ComplexNumber::setImaginary(double imaginary)
{
    this->m_imaginary = imaginary;
}


/*
 * Adds this ComplexNumber with another ComplexNumber.
 *
 * @param z [IN] The ComplexNumber to add to this number.
 * @return A new ComplexNumber that is the result of the addition.
 */
ComplexNumber ComplexNumber::operator+(const ComplexNumber& z) const
{
    return ComplexNumber(this->getReal() + z.getReal(), this->getImaginary() + z.getImaginary());
}

/*
 * Subtracts this ComplexNumber with the given ComplexNumber.
 *
 * @param z [IN] The ComplexNumber to subtract from this number.
 * @return A new ComplexNumber that is the result of the substraction.
 */
ComplexNumber ComplexNumber::operator-(const ComplexNumber& z) const
{
    return ComplexNumber(this->getReal() - z.getReal(), this->getImaginary() - z.getImaginary());
}


/*
* Multiplys this ComplexNumber with the given ComplexNumber.
* 
* @param z [IN] The ComplexNumber to multiply with this number.
* @return A new ComplexNumber that is the result of the multiplication.
*/
ComplexNumber ComplexNumber::operator*(const ComplexNumber& z) const
{
    double real = (this->getReal() * z.getReal()) - (this->getImaginary() * z.getImaginary());
    double imaginary = (this->getReal() * z.getImaginary()) + (this->getImaginary() * z.getReal());
    return ComplexNumber(real, imaginary);
}

/*
* The string represention of the ComplexNumber.
* 
* @return A string represention of the ComplexNumber.
*/
std::string ComplexNumber::to_string() const
{
    std::string numStr = std::to_string(this->getReal());
    numStr += " + ";
    numStr += std::to_string(this->getImaginary());
    numStr += "i";
    return numStr;
}