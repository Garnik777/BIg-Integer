#include "big_int.hpp"
#include <cstdlib>
#include <cctype>
#include <climits>

const int base = 10;

big_integer::big_integer()
	: my_sign(positive),
	  my_digits(1,'0'),
	  my_num_digits(1)
{}

big_integer::big_integer(int num)
	: my_sign(positive),
	  my_digits(1,'0'),
  	  my_num_digits(0)
{
	// check if num is negative, change state and num accordingly
	if (num < 0) {
		my_sign = negative;
		num = -1 * num;
	}
	
	//handle least-significant digit of num (handles num == 0)
	
	add_sig_digit(num % base);
	num = num / base;
	// handle remaining digits of num
	 while (num != 0)
	 {
		add_sig_digit(num % base);
		num = num / base;
	 }
}

big_integer::big_integer(const std::string&  s)

	//s consist of digits only,optionaly preceded by +or -
	//big_integer initialized to integer represented to integer represented by s
	//if s is not a well formed big_integer (contains non-digits characters) 
	//than an error message is printed and abort called
	: my_sign(positive),
	  my_digits(s.length(),'0'),
  	  my_num_digits(0)
{
	int k;	
	int limit = 0;

	if (s.length() == 0) {
		my_digits.resize(1);
		add_sig_digit(0);
		return;
	}
	if (s[0] == '-') {
		my_sign = negative;
		limit = 1;
	}
	if (s[0] == '+') {
		limit = 1;
	}
	std::cout << "s length = " << s.length()<< std::endl;
	//start at least significant digit
	for (k = s.length() -1; k >= limit; k--)
	{
		if (! isdigit(s[k])) {
			std::cerr << "badly formed big_integer value =" << s << std::endl;
			abort();
		}
		add_sig_digit(s[k] - '0');
	}
	
	normalize();
}



int big_integer::get_digits(int k) const
{
	if (0 <= k && k < num_digits()){
		return my_digits[k]-'0';
	}
	return 0;
}


void big_integer::print(std::ostream & os) const 
//big_integer inserted onto stream os
{
	os << to_string();
}

std::string big_integer::to_string() const 
{
	int k;
	int len = num_digits();
	std::string s = "";
	
	if (is_negative()) {
		s = '-';
	}
	for (k = len-1; k >= 0; k--)
	{
		s += char('0' + get_digits(k));
	}
	return s;

}


int big_integer::to_int() const
//INT_MIN <= SELF <= INT_MAX
{
	int result = 0;
	int k;
	if (INT_MAX < *this) return INT_MAX;
	if (*this < INT_MIN) return INT_MIN;
	for (k = num_digits() - 1; k >= 0; k--)
	{
		result = result * 10 + get_digits(k);
	}
	if (is_negative())
	{
		result *= -1;
	}
	return result;
}

double big_integer::to_double() const
//DBL_MIN <= self <= DBL_MAX
{
	double result = 0.0;
	int k;
	for (k = num_digits() -1; k >= 0; k--)
	{
		result = result * 10 + get_digits(k);
	}
	if (is_negative())
	{
		result *= -1;
	}
	return result;
}

std::ostream & operator << (std::ostream & out, const big_integer & big)
{
	big.print(out);
	return out;
}

std::istream & operator >> (std::istream & in, big_integer & big)
	//postcondition: big extracted from in, must be whitespace delimited
{
	std::string s;
	in >> s;
	big = big_integer(s);
	return in;
}

bool operator == (const big_integer & lhs, const big_integer & rhs)
{
	return lhs.equal(rhs);
}

bool big_integer::equal(const big_integer & rhs) const
{
	// return true if self == rhs, else return false
	if (num_digits() != rhs.num_digits() || is_negative() != rhs.is_negative()) {
		return false;
	}
	// same sign ,same number of digits
	int k;
	int len = num_digits();
	for (k = 0; k < len; k++)
       	{
		if (get_digits(k) != rhs.get_digits(k))
	       	{
			return false;
		}
	}
	return true;
}

bool operator != (const big_integer & lhs, const big_integer & rhs)
{
	return ! (lhs == rhs);
}



bool big_integer::less_than(const big_integer & rhs) const
{
	// if sign aren'nt equal, self < rhs only if is negative
	if (is_negative() != rhs.is_negative()) {
		return is_negative();
	}

	if (num_digits() != rhs.num_digits()) {
		return (num_digits() < rhs.num_digits() && is_positive()) ||
		       (num_digits() > rhs.num_digits() && is_negative()); 	
	}
	// digits same , sign the same
	int k;
	int len = num_digits();
	for (k = len -1; k >= 0; k--)
	{
		if (get_digits(k) < rhs.get_digits(k)) return is_positive();
		if (get_digits(k) > rhs.get_digits(k)) return is_negative();
	}
	return false; // self == rhs	
}

bool operator < (const big_integer & lhs, const big_integer & rhs)
{
	return lhs.less_than(rhs);
}

bool operator <= (const big_integer & lhs, const big_integer & rhs)
{
	return lhs == rhs || lhs < rhs;
}

bool operator > (const big_integer & lhs, const big_integer & rhs)
{
	// returns true if lhs > rhs ,else returns false
	return rhs < lhs;
}

bool operator >= (const big_integer & lhs, const big_integer & rhs)
{
	return lhs == rhs || lhs > rhs;
}

void big_integer::normalize()
{
	//all leading zeros removed	
	int k ;
	int len = num_digits();
	for (k =len -1; k >= 0; --k ){           // find a non zero digit
		if(0 != get_digits(k)) break;
		my_num_digits--;                //chop off zeros
	}
	if (k < 0) {
			my_num_digits = 1;
			my_sign = positive;
	}
}

void big_integer::change_digit(int k, int value)
{
	//precondition: 0 <= k < num_digits()
	//postcondition:k- th digit changed to value (0 digit is least signifisant digit)
	if (0 <= k && k < num_digits())
	{
		my_digits[k] = char('0' + value);
	}else{
		std::cerr << "error change_digit " << k << " " << my_num_digits << std::endl;
	}
	 
}

int big_integer::num_digits() const
{
	//postcondition: return # digits in big_integer
	return my_num_digits;
}

void big_integer::add_sig_digit(int value)
{
//value added to big_integer as most significant digit
//note:0th digit is least signifisant
	if (my_num_digits >= my_digits.size())
	{
		my_digits.resize(my_digits.size() * 2);
	}
	my_digits[my_num_digits] = char('0' + value);
	my_num_digits++;
}

bool big_integer::is_negative() const 
{
	//postcondition: returns true iff big_int is negative
	return my_sign == negative;
}

bool big_integer::is_positive() const
{
	return my_sign == positive;
}

const big_integer & big_integer::operator +=(const big_integer & rhs)
	//return value of bigint + rhs after addition
{
	int sum;
	int carry = 0;
	int k;
	int len = num_digits();            //length of larger added
	if (this == &rhs) 
	{
		*this *=2;
		return *this;
	}
	if (is_positive() != rhs.is_positive()) //sign not the same subtruct
	{
		*this -= (-1 * rhs);
		return *this;
	}
	if ( len < rhs.num_digits())
	{
		len = rhs.num_digits();
	}
	for (k = 0; k < len; k++)
	{
		sum = get_digits(k) + rhs.get_digits(k) + carry;
		carry = sum / base;
		sum = sum % base;
		if (k < my_num_digits)
		{
			change_digit(k,sum);
		}
		else{
			add_sig_digit(sum);
		}
	}
	if (carry != 0)
	{
		add_sig_digit(carry);
	}
	return *this;
}

big_integer operator +(const big_integer & lhs, const big_integer & rhs)
{
	big_integer result(lhs);
	result += rhs;
	return result;
}

const big_integer & big_integer::operator -=(const big_integer & rhs)
{
	int diff;
	int borrow = 0;
	int k;
	int len = num_digits();
	
	if (this == &rhs)              //subtructing self?
	{
		*this = 0;
		return *this;
	}
	// sign opposite? then lhs - (-rhs) = lhs + rhs
	if (is_negative() != rhs.is_negative() )
	{
		*this += (-1 * rhs);
		return *this;
	}
	// sign are the same, check which number is larger and swich to get 
	// larger number "on top" since sign can change when subtructing
	//ex: 7-3 no sign change, 3-7 sign changes
	if (is_positive() && (*this) < rhs ||
	    is_negative() && (*this) > rhs   )
	{
		*this = rhs - *this;
		if (is_positive() ) my_sign = negative;
		else                my_sign = positive;
		return *this;	
	}
	//same sign and larger number on top
	for (k = 0;k < len; k++)
	{
		diff = get_digits(k) - rhs.get_digits(k) - borrow;
		borrow = 0;
		if (diff < 0)
		{
			diff += 10;
			borrow = 1;
		}
		change_digit(k,diff);
	}
	normalize();
	return *this;
}

big_integer operator -(const big_integer & lhs,const big_integer & rhs)
{
	big_integer result(lhs);
	result -= rhs;
	return result;
}

const big_integer & big_integer::operator *=(int num)
{
//postcondition:returns num * value of big_int after multiplication
	int carry = 0;
	int result;
	int k;
	int len = num_digits();

	if (0 == num)            // treat zero as special case and stop
	{
		*this = 0;
		return *this;
	}
	if (base < num || num < 0)  //handle precondition failure
	{
		*this *= big_integer(num);
		return *this;
	}
	if (1 == num)               // treat one as special case no work
	{
		return *this;
	}

	for (k = 0; k < len; k++)   //once for each digit
	{
		result = num * get_digits(k) + carry;
		carry = result/base;
		change_digit(k, result % base);
	}
	while (carry != 0)
	{
		add_sig_digit(carry % base);
		carry /= base;
	}
	return *this;
}

big_integer operator *(const big_integer & a, int num)
{
	big_integer result(a);
	result *= num;
	return result;
}

big_integer operator *(int num, const big_integer & a)
{
	big_integer result(a);
	result *= num;
	return result;
}

const big_integer & big_integer::operator *=(const big_integer & rhs)
{
	if (is_negative() != rhs.is_negative() )
	{
		my_sign = negative;
	}
	else
	{
		my_sign = positive;
	}

	big_integer self(*this);          //copy of self
	big_integer sum(0);               //to accumulate sum 
	int k;
	int len = rhs.num_digits();       //# digits in multiplier
        for ( k = 0; k <len; k++)
	{
		sum += self * rhs.get_digits(k);
		self *= 10;                      // add a zero
	}
	*this = sum;
	return *this;	
}

big_integer operator *(const big_integer & lhs, const big_integer & rhs)
{
	big_integer result(lhs);
	result *= rhs;
	return result;
}


const big_integer & big_integer::operator /= (const big_integer & divisor)
{
	if (divisor == 0)
	{
		std::cerr <<" divide by 0 error" << std::endl;
	}
	big_integer dividend(*this);        //copy of self, handles aliasing
	big_integer temp_divisor(divisor);
	big_integer quotient(0);
	dividend.my_sign = positive;
	temp_divisor.my_sign = positive;
	while (dividend >= temp_divisor)
	{
		dividend -= temp_divisor;
		quotient += 1;
	}
	if (is_negative() != divisor.is_negative() )
	{
		quotient.my_sign = negative;
		quotient.normalize();                // clean up -0 answer to 0
	}
	*this = quotient;
	return *this;
}

big_integer operator / (const big_integer & lhs, const big_integer & rhs)
{
	big_integer result(lhs);
	result /= rhs;
	return result;
}

big_integer& big_integer::operator ++()
{
	*this += 1;
	return *this;
}

big_integer& big_integer::operator --()
{
	*this -= 1;
	return *this;
}

big_integer big_integer::operator ++(int)
{
	big_integer temp;
	temp = *this;
        *this = *this + 1;
	return temp;

}

big_integer big_integer::operator --(int)
{
	big_integer temp;
	temp = *this;
	*this = *this - 1;
	return temp;
}

/*big_integer & big_integer::operator ++()
{
	if ( is_positive() )                  //add one to big int
	{
		int curr_pos = 0;
		while (get_digits(curr_pos) == base -1)
		{
			change_digit(curr_pos,0);
			curr_pos++;
		}
		if (curr_pos < num_digits() )
	       	{
			change_digit(curr_pos,get_digits(curr_pos) + 1);
		}else
	       	{
			add_sig_digit(1);
		}else if (*this == -1)         //in this case the sign changes
		{
			change_digit(0,0);
			my_sign = positive;	
		}else                         // subtruct 1 from its abs val,keep same sign
		{
			int curr_pos = 0;
			while (get_digits(curr_pos) == 0)
			{
				change_digit(curr_pos, base -1);
				curr_pos++;
			}
			change_digit(curr_pos, get_digits(curr_pos) - 1);
			(*this).normalize();        // leading zero could be added		
		}
		return *this;
	}
}
*/

