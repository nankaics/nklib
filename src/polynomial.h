/** @file polynomail.h
 *  @brief Defines the linear polynomail format and its solution format.
 *
 *  @author Li Jiaying
 *  @bug No known bugs.
 */

#ifndef POLYNOMIALH
#define POLYNOMIALH

#include <iostream>
#include <vector>
#include <string>
#include "color.h"
#include "z3++.h"
#include "common.h"
using namespace z3;
using namespace std;

/** \class Polynomial
 *  @brief This class defines an polynomail by storing all its coefficiencies.
 *		   An polynomail is regarded a hyperplane in math.
 *
 *  v[0] * 1 + v[1] * x1 + v[1] * x2 + ... + v[Cv1to4] * x{Cv0to4} >= 0
 */
class Polynomial {
	private:
		int dim;
		int power;
		vector<string> vars;
		vector<double> values;
		
	public:
		int nvars;

	public:
		Polynomial() : power(1) {}

		Polynomial(Polynomial& poly) : 
			power(poly.power), vars (poly.vars), values(poly.values), nvars(poly.nvars)  {}

		Polynomial& operator=(Polynomial& rhs);
		bool operator==(const Polynomial& rhs) const;

		double get_coef(int index) const;
		template<typename T>
		bool set_coef(int index, T c);

		vector<double> get_coefs() const;
		template<typename T>
		bool set_coefs(vector<T> cs);
		template<typename T>
		bool set_coefs(T cs, int size, double (* visit_function)(T& t, int i));

		int get_power() const {
			return power;
		}

		bool set_power(int e) {
			if (e > 4) {
				cout << "Can only support polynomial up to power 4. However, power " << e << " is called.\n";
				return false;
			}
			power = e;
			compute_dimension();
			return true;
		}

		inline int get_nvars() const {
			return nvars;
		}

		inline void set_nvars(int n) {
			nvars = n;
		}

		bool set_variable_name(int index, const string& name); 
		string get_variable_name(int index) const; 

		bool set_variable_name_list(const vector<string>& names); 
		bool set_anonymous_list(int nvars); 
		vector<string> get_variable_name_list() const; 

		int get_dimension() const;
		int compute_dimension();

		bool scale(double times);
		std::string to_string() const;

		/** @brief This method converts *this polynomail object to z3 expr object.
		 *
		 *  Introducing this method help to simplify imlementation of uniImply method.
		 *
		 *  @param name contains each variants vars.
		 *				If NULL, the name would be "x1", "x2" form.
		 *	@param c is z3::context, defines which context the return expr will be used.
		 *	@return z3::expr
		 */
		z3::expr to_z3expr(z3::context& c) const;

		 /*	*this ==> e2 ??
		 *  The default precision is set to E-8 (2.8f), which is changeable if need
		 *  @return bool true if yes, false if no.
		 */
		bool z3_implies(const Polynomial& e2) const;

		static bool z3_imply(const Polynomial* e1, int e1_num, const Polynomial& e2);

		double evaluate_item(int index, const double* givenvalues);

		double evaluate_coef(int x, int power, double* givenvalues);

		inline bool solve_polynomial(double* results);

		bool factor() {
			return true;
		}


		/** @brief This method is used to check whether *this polynomail is similar to given polynomail e or not.
		 *		   *this ~= e ???
		 *
		 * @param precision defines how much variance we can bare.
		 *		  The default is 4, which means we can bare 0.0001 difference.
		 *		  In this case 1 ~=1.00001, but 1!~=1.000011
		 */
		bool is_similar(Polynomial& e2, int precision = PRECISION);

		/** @brief Do roundoff job for an polynomail
		 *
		 *	Sompower the polynomail has ugly coefficiencies
		 *	we want to make it elegent, which is the purpose of involing this method
		 *	Currently we have not done much work on this
		 *	We have not even use gcd function to adjust the coefficients.
		 *
		 *	For example.
		 *	1.2345 x1 >= 2.4690    ==>		x1 >= 2
		 *	2 x1 >= 5.000001	   ==>		x1 >= 2.5
		 *
		 *	@param e Contains the polynomail that has already rounded off
		 *	@return int 0 if no error.
		 */
		int roundoff(Polynomial& e);
		bool already_roundoff();

		Polynomial* roundoff_in_place();

	private: 
		static bool roundoff_double(double x, double& roundx);
		bool roundoffable();
};

int test_polynomial();
#endif
