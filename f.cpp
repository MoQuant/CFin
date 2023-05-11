#include <iostream>
#include <math.h>
#include <vector>

// Calculates future value of cash today
double FutureValue(double x, double r, double t)
{
    return x*pow(1 + r, t);
}

// Calculates present value of cash today
double PresentValue(double x, double r, double t)
{
    return x / pow(1 + r, t);
}

// Net present value
double NetPresentValue(std::vector<double> x, double r)
{
    double total = 0;
    for(int i = 0; i < x.size(); ++i){
        total = total + x[i]/pow(1 + r, i);
    }

    return total;
}

// Loan payment formula
double LoanPmt(double amount, double rate, double time, double periods)
{
    rate /= periods;
    time *= periods;

    double top = amount * rate;
    double bottom = 1.0 - 1.0 / pow(1 + rate, time);

    return top/bottom;
}

int main()
{
    // Calculate the future value of $50 growing for 15 days at a rate of 3.4%; Place
    // results into present value function and calculate back

    double cash = 50;
    double r = 0.034;
    double t = 15;

    r /= t;
    
    std::cout << "Future Value: " << FutureValue(cash, r, t) << std::endl;
    std::cout << "Present Value: " << PresentValue(FutureValue(cash, r, t), r, t) << std::endl;

    std::cout << std::endl;

    // Calculate the net present value of the following vector and interest rate
    std::vector<double> cashflows = {-1000, 500, 60, -30, 200, 100, 800};
    double cost_of_capital = 0.07;

    std::cout << "Net Present Value: " << NetPresentValue(cashflows, cost_of_capital) << std::endl;

    std::cout << std::endl;

    double loan_amount = 4500;
    double rate = 0.0429;
    double maturity = 1.0;
    double periods = 12;

    std::cout << "Loan Payment: " << LoanPmt(loan_amount, rate, maturity, periods) << std::endl;

    return 0;
}
