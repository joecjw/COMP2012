#ifndef ISSUER_H
#define ISSUER_H
#include <string>

enum BondType {T1, T2, T3};

class CertificateBase;
template<enum BondType bondType>
class Certificate;

class IssuerBase {
    protected:
        int numOfBond_;
        std::string name_;

    public:
        IssuerBase(std::string name): name_(name), numOfBond_(0){};

        void IssueBond(int amount) {
            numOfBond_ = amount;
        }

        virtual CertificateBase* SellBond(int amount) = 0;
        virtual void SetRateAndPeriod(double rate, int period) const = 0;
        virtual void Log() const = 0;
};

template<enum BondType bondType>
class Issuer : public IssuerBase {
    public:
        Issuer(std::string name): IssuerBase(name){};

        virtual CertificateBase* SellBond(int amount) {
        //TODO:
            //1. Decrease numOfBond_
            numOfBond_ -= amount;

            //2. Calculate the face value of certificate (face value = (1 + interest rate) * amount)
            double face_value = (1 + Certificate<bondType>::interestRate_) * amount;
            
            //3. Create and return a certificate to user
            Certificate<bondType>* temp = new Certificate<bondType>(face_value, this);
            dynamic_cast<CertificateBase*>(temp);
            return temp;

        //* You can always assume numOfBond_ is greater than amount 
        }

        void SetRateAndPeriod(double rate, int year) const {
        //TODO:
            //1. Wrapper of SetRateAndPeriod in Certificate class
            Certificate<bondType>::SetRateAndPeriod(rate, year);
        }

        virtual void Settlement(Certificate<bondType>* Certificate) const {
            delete Certificate;
        }

        //CORRECTNESS CHECK - DO NOT MODIFY
        void Log() const{
            using namespace std;
            cout << "----------------------" << endl;
            cout << " Issuer: " << name_ << endl;
            cout << "----------------------" << endl;
            cout << "Num of ongoing transaction: " << Certificate<bondType>::transactionsNum_ << endl;
            cout << "Num of bond pending sold : " << numOfBond_ << endl;
        }
};

#endif