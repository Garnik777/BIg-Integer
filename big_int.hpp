#ifndef BIG_INT__
#define BIG_INT__
#include<iostream>
#include <vector>
#include <string>

class big_integer 
{
private:
	//private state /instance variables
	enum Sign{positive, negative};
	Sign my_sign;
	std::vector<char> my_digits;
	int my_num_digits;

	//other helper functions
	bool is_negative() const;  //return true if number is negative
	bool is_positive() const;  // return true if number is positive
	int num_digits()   const;  // store # of digits in number

	int get_digits(int k) const;        // return digits or(0)
	void add_sig_digit(int value);      // add new most sig digit
	void change_digit(int k, int value); // change digit to value
	void normalize();

public:
	big_integer();
	big_integer(int);
	big_integer( const std::string& );
	// operators: arithmetic, relational
	
	const big_integer& operator +=(const big_integer&);
	const big_integer& operator -=(const big_integer&);
	const big_integer& operator *=(const big_integer&);
	const big_integer& operator *=(int num);
	const big_integer& operator /=(const big_integer&);
	big_integer & operator ++();
	big_integer & operator --();
	big_integer   operator --(int);
	big_integer   operator ++(int);
	std::string to_string() const;                 //convert to string
	int      to_int()    const;                 //convert to int
        double 	 to_double() const;		    // convert to double
	// facilitate operators ==, <, << without friends
	
	bool equal(const big_integer& rhs)     const;
	bool less_than(const big_integer& rhs) const;
	void print(std::ostream& os)           const;

	friend std::ostream & operator <<(std::ostream &, const big_integer &);
	friend std::istream & operator >>(std::istream &,  big_integer &);
	friend big_integer operator +(const big_integer & lhs, const big_integer & rhs);
	friend big_integer operator -(const big_integer & lhs, const big_integer & rhs);
	friend big_integer operator *(const big_integer & lhs, const big_integer & rhs);
	friend big_integer operator *(const big_integer & lhs, int num);
	friend big_integer operator *(int num, const big_integer & rhs);
	friend big_integer operator /(const big_integer & lhs, const big_integer & rhs);
	friend big_integer operator /(const big_integer & lhs, int num);

	friend bool operator == (const big_integer & lhs, const big_integer & rhs);
	friend bool operator <  (const big_integer & lhs, const big_integer & rhs);
	friend bool operator != (const big_integer & lhs, const big_integer & rhs);
	friend bool operator >  (const big_integer & lhs, const big_integer & rhs);
	friend bool operator >= (const big_integer & lhs, const big_integer & rhs);
	friend bool operator <= (const big_integer & lhs, const big_integer & rhs);
};


#endif // BIG_INT__
