#include "big_int.hpp"
#include <cstdlib>
#include <cctype>
void test_big_to_int_and_double(big_integer a)
{
	while (true)
	{
		std::cout << "enter big:";
		std::cin >> a;
		std::cout << "a = " << a << " as int = " << a.to_int() << std::endl;
		std::cout << "as double = " << a.to_double() << std::endl;
	}

}

void test_comparison(big_integer a, big_integer b)
{
	while (true)
	{
		std::cin >> a >> b;
		std::cout << "first is less than second " << (a < b)  << std::endl;
		std::cout << "first is greater than second " << (a > b)  << std::endl;
		std::cout << "first is equal to second " << (a == b)  << std::endl;
	}
}

void test_add(big_integer a, big_integer b)
{
	std::cin >> a >> b;
	std::cout << "sum = " << a + b << std::endl;
}
void test_subtruct(big_integer a, big_integer b)
{
	std::cin >> a >> b;
	std::cout << " a - b = " << a - b << std::endl;
}

void test_mult(big_integer a, big_integer b)
{
	std::cin >> a >> b;
	std::cout << "a * b = " << a * b << std::endl;
}

void test_division(big_integer a, big_integer b)
{
	std::cin >> a >> b;
	std::cout << "a / b = " << a / b << std::endl;
}

void test_prefix_increment(big_integer & a)
{
	std::cin >> a;
	++a;
	std::cout << a << std::endl;
	
}

void test_postfix_decrement(big_integer a)
{
	std::cin >> a;
	a--;
	std::cout << a << std::endl;
}

int main()
{
	int  c;                        
	big_integer a, b;             
	
	while (1)
       	{
	      std::cout<<"1.Add two big_integer"<<std::endl;
	      std::cout<<"2.Subtract two big integer"<<std::endl;
	      std::cout<<"3.Multiply two big integer"<<std::endl;
	      std::cout<<"4.Divide   two big integer"<<std::endl;
	      std::cout<<"5.Prefix increment\n";
	      std::cout<<"6.Postfix decrement\n";
	      std::cout<<"7.Exit\n"; 
	      std::cout<<"Enter your choice: ";
	      std::cin >> c;
	
		switch (c)
		{
			case 1 :
				std::cout <<"enter two value delimited with space:\n";
				test_add(a,b);
				break;
			case 2:
				std::cout <<"enter two value delimited with space:\n";
				test_subtruct(a,b);
				break;
			case 3:
				std::cout <<"enter two value delimited with space:\n";
				test_mult(a,b);
				break;
			case 4:
				std::cout <<"enter two value delimited with space:\n";
				test_division(a,b);
				break;
			case 5: 
				std::cout << "enter value for prefix increment\n";
				test_prefix_increment(a);
				break;
			case 6: 
				std::cout << "enter value for postfix decrement\n";
				test_postfix_decrement(a);
				break;
			case 7: 
				exit(1);	
			default:
				std::cerr << "\nEnter correct option\n";	
		}
	}

	return 0;
}

