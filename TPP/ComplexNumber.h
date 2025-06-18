#pragma once
#include <string>

class ComplexNumber
{
  public:
    ComplexNumber();
    ComplexNumber(double real, double imaginary);

    /*
     * The current value of m_real.
     *
     * @return The value of m_real.
     */
    double getReal() const;

    /*
     * The current value of m_imaginary.
     *
     * @return The value of m_imaginary.
     */
    double getImaginary() const;

    /*
     * Sets the m_real to a new value.
     *
     * @param real [IN] The new value for m_real.
     */
    void setReal(double real);

    /*
     * Sets the m_imaginary to a new value.
     *
     * @param imaginary [IN] The new value for m_imaginary.
     */
    void setImaginary(double imaginary);

    /*
     * Adds this ComplexNumber with another ComplexNumber.
     *
     * @param z [IN] The ComplexNumber to add to this number.
     * @return A new ComplexNumber that is the result of the addition.
     */
    ComplexNumber operator+(ComplexNumber& z);
    
    /*
     * Subtracts this ComplexNumber with the given ComplexNumber.
     *
     * @param z [IN] The ComplexNumber to subtract from this number.
     * @return A new ComplexNumber that is the result of the substraction.
     */
    ComplexNumber operator-(ComplexNumber& z);

    /*
     * Multiplys this ComplexNumber with the given ComplexNumber.
     *
     * @param z [IN] The ComplexNumber to multiply with this number.
     * @return A new ComplexNumber that is the result of the multiplication.
     */
    ComplexNumber operator*(ComplexNumber& z);

    /*
     * The string represention of the ComplexNumber.
     *
     * @return A string represention of the ComplexNumber.
     */
    std::string to_string();

  private:
    double m_real;
    double m_imaginary;
};