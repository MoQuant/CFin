#define USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>

double pi(){
    return M_PI;
}

// Normal Distribution Function
double NORM(double z)
{
    auto simps = [](int n){
        std::vector<double> result;
        for(int i = 0; i < n; ++i){
            if(i == 0 || i == n - 1){
                result.push_back(1.0);
            } else if(i % 2 == 0){
                result.push_back(2.0);
            } else {
                result.push_back(4.0);
            }
        }
        return result;
    };

    auto norm = [](double z){
        double factor = 1.0 / sqrt(2.0*pi());
        double e = exp(-pow(z, 2)/2);
        return factor * e;
    };

    int ii = 0;
    int N = 101;
    z = abs(z);
    double prob = 0;
    double z0 = 0;
    double dZ = (z - z0)/((double) N - 1);

    for(auto & c : simps(N)){
        prob += c*norm(z0 + ii*dZ);
        ii += 1;
    }

    prob *= dZ/3.0;

    return 1 - (prob + 0.5);
}

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

// Interest rate function
double Interest(double amount, double rate, double periods)
{
    rate /= periods;
    return amount * rate;
}

// Loan Amortization Table
void LoanAmortizationTable(double amount, double rate, double time, double periods){
    double dtime = time * periods;
    double pmt = LoanPmt(amount, rate, time, periods);
    double ipmt = 0;
    std::cout << amount << "\t" << "-" << "\t" << "-" << std::endl;
    for(int i = 0; i < dtime; ++i){
        ipmt = Interest(amount, rate, periods);
        amount = amount + ipmt - pmt;
        std::cout << amount << "\t" << ipmt << "\t" << pmt << std::endl;
        
    }
}

// Calculates the IRR
double IRR(std::vector<double> x)
{
    // NPV Function
    auto fx = [](std::vector<double> k, double r){
        double npv = 0;
        for(int i = 0; i < k.size(); ++i){
            npv += k[i]/pow(1 + r, i);
        }
        return npv;
    };

    // dNPV Function
    auto f1 = [](std::vector<double> k, double r){
        double npv_dr = 0;
        for(int i = 0; i < k.size(); ++i){
            npv_dr += -i*k[i]/pow(1 + r, i + 1);
        }
        return npv_dr;
    };

    double r0 = 0.1, r1 = 1.00;
    
    // Iterative algorithm solving for the IRR
    while(true){
        r1 = r0 - fx(x, r0)/f1(x, r0);
        if(abs(r1 - r0) < 0.0001){
            break;
        }
        r0 = r1;
    }

    return r1;
}

int main()
{
    LoanAmortizationTable(500000, 0.07, 30, 12);

    return 0;
}
