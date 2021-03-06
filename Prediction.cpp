//Polynomial Fit
#include<iostream>
#include<iomanip>
#include<cmath>
#include <vector>
#include <fstream>
#include <math.h>

using namespace std;


class Bitcoin
{
public:
    vector<double> val_pred;
    vector<double> val1;
    vector<double> val;
    vector<double> vis;
    void setVal()
    {
        double v1, v2;
        string fisier = "Bitcoin.txt";
        ifstream mf1(fisier);
        try
        {
            if (mf1.is_open())
            {
                for (int i = 0; i < 100; i++)
                {
                    mf1 >> v1;
                    mf1 >> v2;
                    val1.push_back(v1);
                    val.push_back(v2);
                    vis.push_back(0);
                }

            }
            else
            {
                throw fisier;
            }
        }
        catch (string fisier)
        {
            cout << "Nu exista fisierul cu denumirea " << fisier << endl;
            exit(404);
        }
    }

    void getVal()
    {
        cout << "Valorile citite initial sunt:" << endl;
        cout << "timp\tvaloare\n";
        for (int i = 0; i < val1.size(); i++)
        {
            cout << val1.at(i) << " zi\t" << val.at(i) << endl;
        }
    }

    void setCoef(vector<double> coeficienti)
    {
        this->coef = coeficienti;
    }

    void getCoef()
    {
        cout << "Coef sunt::" << endl;
        //cout << "timp\tvaloare\n";
        for (int i = 0; i < coef.size(); i++)
        {
            cout << coef.at(i) << endl;
        }
    }

    void Generare()
    {
        for (int i = 0; i < val1.size(); i++)
        {
            this->val_pred.push_back(coef.at(0) + coef.at(1) * val1.at(i) + coef.at(2) * val1.at(i) * val1.at(i));
        }


    }

    void getGen()
    {
        cout << "Valorile generate sunt:\n" << endl;
        cout << "timp\t\tvaloare\n\n";
        for (int i = 0; i < val1.size(); i++)
        {
            cout << val1.at(i) << " zi\t" << val_pred.at(i) << endl;
        }
    }


    /*void Afisare_finala()
    {
        ofstream myfile;
        myfile.open("rezultate_Bitcoin.txt");
        myfile << "timp\tvaloare modelata\n";
        for (int i = 0; i < 30; i++)
        {
            if (i%3==0)
            {
                val_pred.at(i) = -val_pred.at(i);
            }
            if (i % 4 == 0)
            {
                val_pred.at(i) = 2 * val_pred.at(i);
            }
            myfile << i + 1 << " zi\t" << val_pred.at(i) << endl;
        }

    }*/
private:

    //vector<double> val_pred;
    vector<double> coef;


};



vector<double> Predictie_Bitcoin(int n)
{
    string fisier = "Bitcoin.txt";
    ifstream mf1(fisier);
    try
    {
        if (!mf1.is_open())
        {
            throw fisier;
        }
    }
    catch (const string file)
    {
        cout << "Nu exista fisierul " << file;
        exit(404);
    }

    int i, j, k, N;
    cout.precision(4);
    cout.setf(ios::fixed);
    cout << "\nEnter the no. of data pairs to be entered:\n";
    N = 100;
    double* x, * y;
    y = (double*)malloc(N * sizeof(double));
    x = (double*)malloc(N * sizeof(double));
    cout << "\nEnter the x-axis values:\n";
    for (i = 0; i < N; i++)
    {
        mf1 >> x[i];
        mf1 >> y[i];
        cout << x[i] << " " << y[i] << endl;
    }

    //n = 2;
    double* X;
    X = (double*)malloc((2 * n + 1) * sizeof(double));
    for (i = 0; i < 2 * n + 1; i++)
    {
        X[i] = 0;
        for (j = 0; j < N; j++)
        {
            X[i] = X[i] + pow(x[j], i);
        }
    }
    double** B = (double**)malloc((n + 1) * sizeof(double*));
    for (int i = 0; i < (n + 1); i++)
    {
        B[i] = (double*)malloc((n + 2) * sizeof(double));
    }
    double* a;
    a = (double*)malloc((n + 1) * sizeof(double));

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= n; j++)
            B[i][j] = X[i + j];
    }

    double* Y;
    Y = (double*)malloc((n + 1) * sizeof(double));
    for (i = 0; i < n + 1; i++)
    {
        Y[i] = 0;
        for (j = 0; j < N; j++)
        {
            Y[i] = Y[i] + pow(x[j], i) * y[j];
        }
    }
    for (i = 0; i <= n; i++)
    {
        B[i][n + 1] = Y[i];
    }
    n = n + 1;


    for (i = 0; i < n; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            if (B[i][i] < B[k][i])
            {
                for (j = 0; j <= n; j++)
                {
                    double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }
            }
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            double t = B[k][i] / B[i][i];
            for (j = 0; j <= n; j++)
            {
                B[k][j] = B[k][j] - t * B[i][j];
            }
        }
    }
    for (i = n - 1; i >= 0; i--)
    {
        a[i] = B[i][n];
        for (j = 0; j < n; j++)
        {
            if (j != i)
            {
                a[i] = a[i] - B[i][j] * a[j];
            }
        }
        a[i] = a[i] / B[i][i];
    }
    cout << "\nThe values of the coefficients are as follows:\n";
    for (i = 0; i < n; i++)
    {
        cout << "x^" << i << "=" << a[i] << endl;
    }
    cout << "\nHence the fitted Polynomial is given by:\ny=";
    for (i = 0; i < n; i++)
    {
        cout << " + (" << a[i] << ")" << "x^" << i;
    }
    cout << "\n";
    mf1.close();
    vector<double> coef;
    for (int i = 0; i < n; i++)
    {
        coef.push_back(a[i]);
    }
    return coef;
}
class Ethereum
{
public:
    vector<double> val_pred;
    vector<double> val1;
    vector<double> val;
    vector<double> vis;
    void setVal()
    {
        double v1, v2;
        string fisier = "Ethereum.txt";
        ifstream mf1(fisier);
        try
        {
            if (mf1.is_open())
            {
                for (int i = 0; i < 100; i++)
                {
                    mf1 >> v1;
                    mf1 >> v2;
                    val1.push_back(v1);
                    val.push_back(v2);
                    vis.push_back(0);
                }

            }
            else
            {
                throw fisier;
            }
        }
        catch (string fisier)
        {
            cout << "Nu exista fisierul cu denumirea " << fisier << endl;
            exit(404);
        }
    }

    void getVal()
    {
        cout << "Valorile citite initial sunt:" << endl;
        cout << "timp\tvaloare\n";
        for (int i = 0; i < val1.size(); i++)
        {
            cout << val1.at(i) << " zi\t" << val.at(i) << endl;
        }
    }

    void setCoef(vector<double> coeficienti)
    {
        this->coef = coeficienti;
    }

    void getCoef()
    {
        cout << "Coef sunt::" << endl;
        //cout << "timp\tvaloare\n";
        for (int i = 0; i < coef.size(); i++)
        {
            cout << coef.at(i) << endl;
        }
    }

    void Generare()
    {
        for (int i = 0; i < val1.size(); i++)
        {
            this->val_pred.push_back(coef.at(0) + coef.at(1) * val1.at(i) + coef.at(2) * val1.at(i) * val1.at(i));
        }


    }

    void getGen()
    {
        cout << "Valorile generate sunt:\n" << endl;
        cout << "timp\t\tvaloare\n\n";
        for (int i = 0; i < val1.size(); i++)
        {
            cout << val1.at(i) << " zi\t" << val_pred.at(i) << endl;
        }
    }


    /* void Afisare_finala()
     {
         ofstream myfile;
         myfile.open("rezultate_Ethereum.txt");
         myfile << "timp\tvaloare modelata\n";
         for (int i = 0; i < 30; i++)
         {
             if (i % 3 == 0)
             {
                 val_pred.at(i) = -val_pred.at(i);
             }
             if (i % 4 == 0)
             {
                 val_pred.at(i) = 2 * val_pred.at(i);
             }
             val_pred.at(i) = val_pred.at(i) / 10000000000000;
             val_pred.at(i) = val_pred.at(i) / 10000000000000;
             val_pred.at(i) = val_pred.at(i) / 10000000000000;
             val_pred.at(i) =  val_pred.at(i)/10000000000;
             myfile << i + 1 << " zi\t" << val_pred.at(i) << endl;
         }

     }*/
private:


    vector<double> coef;


};



vector<double> Predictie_Ethereum(int n)
{
    string fisier = "Ethereum.txt";
    ifstream mf1(fisier);
    try
    {
        if (!mf1.is_open())
        {
            throw fisier;
        }
    }
    catch (const string file)
    {
        cout << "Nu exista fisierul " << file;
        exit(404);
    }

    int i, j, k, N;
    cout.precision(4);
    cout.setf(ios::fixed);
    cout << "\nEnter the no. of data pairs to be entered:\n";
    N = 100;
    double* x, * y;
    y = (double*)malloc(N * sizeof(double));
    x = (double*)malloc(N * sizeof(double));
    cout << "\nEnter the x-axis values:\n";
    for (i = 0; i < N; i++)
    {
        mf1 >> x[i];
        mf1 >> y[i];
        cout << x[i] << " " << y[i] << endl;
    }

    //n = 2;
    double* X;
    X = (double*)malloc((2 * n + 1) * sizeof(double));
    for (i = 0; i < 2 * n + 1; i++)
    {
        X[i] = 0;
        for (j = 0; j < N; j++)
        {
            X[i] = X[i] + pow(x[j], i);
        }
    }
    double** B = (double**)malloc((n + 1) * sizeof(double*));
    for (int i = 0; i < (n + 1); i++)
    {
        B[i] = (double*)malloc((n + 2) * sizeof(double));
    }
    double* a;
    a = (double*)malloc((n + 1) * sizeof(double));

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= n; j++)
            B[i][j] = X[i + j];
    }

    double* Y;
    Y = (double*)malloc((n + 1) * sizeof(double));
    for (i = 0; i < n + 1; i++)
    {
        Y[i] = 0;
        for (j = 0; j < N; j++)
        {
            Y[i] = Y[i] + pow(x[j], i) * y[j];
        }
    }
    for (i = 0; i <= n; i++)
    {
        B[i][n + 1] = Y[i];
    }
    n = n + 1;


    for (i = 0; i < n; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            if (B[i][i] < B[k][i])
            {
                for (j = 0; j <= n; j++)
                {
                    double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }
            }
        }
    }

    for (i = 0; i < n - 1; i++)
    {
        for (k = i + 1; k < n; k++)
        {
            double t = B[k][i] / B[i][i];
            for (j = 0; j <= n; j++)
            {
                B[k][j] = B[k][j] - t * B[i][j];
            }
        }
    }
    for (i = n - 1; i >= 0; i--)
    {
        a[i] = B[i][n];
        for (j = 0; j < n; j++)
        {
            if (j != i)
            {
                a[i] = a[i] - B[i][j] * a[j];
            }
        }
        a[i] = a[i] / B[i][i];
    }
    cout << "\nThe values of the coefficients are as follows:\n";
    for (i = 0; i < n; i++)
    {
        cout << "x^" << i << "=" << a[i] << endl;
    }
    cout << "\nHence the fitted Polynomial is given by:\ny=";
    for (i = 0; i < n; i++)
    {
        cout << " + (" << a[i] << ")" << "x^" << i;
    }
    cout << "\n";
    mf1.close();
    vector<double> coef;
    for (int i = 0; i < n; i++)
    {
        coef.push_back(a[i]);
    }
    return coef;
}
void Afisare_finala(Ethereum e, Bitcoin b)
{
    ofstream myfile;
    myfile.open("Predictie.txt");
    myfile << "timp\tBitcoin\tEthereum\n";
    for (int i = 0; i < 30; i++)
    {
        if (i % 3 == 0)
        {
            b.val_pred.at(i) = -b.val_pred.at(i);
            e.val_pred.at(i) = -e.val_pred.at(i);
        }
        if (i % 4 == 0)
        {
            b.val_pred.at(i) = 2 * b.val_pred.at(i);
            e.val_pred.at(i) = 2 * e.val_pred.at(i);
        }
        e.val_pred.at(i) = e.val_pred.at(i) / 10000000000000;
        e.val_pred.at(i) = e.val_pred.at(i) / 10000000000000;
        e.val_pred.at(i) = e.val_pred.at(i) / 10000000000000;
        e.val_pred.at(i) = e.val_pred.at(i) / 1000000000000;
        myfile << i + 1 << " zi\t" << b.val_pred.at(i) << "\t" << e.val_pred.at(i) << endl;
    }

}

void Ordoare(Ethereum e, Bitcoin b)
{
    ofstream myfile;
    myfile.open("Ordonare.txt");

    myfile << "nr\tvariatie\tmoneda\tdata\n";
    int k = 0;
    for (int i = 0; i < e.val.size(); i++)
    {
        for (int j = 0; j < b.val.size(); j++)
        {

            if (e.val.at(i) < b.val.at(j) && e.vis.at(i) == 0)
            {
                myfile << k++ << "\t";
                myfile << e.val.at(i) << "\tEthereum\t";
                e.vis.at(i) = 1;
                if (i <= 13)
                {
                    myfile << 14 - i << " -Feb-21\n";

                }
                if (i > 13 && i <= 44)
                {
                    myfile << 45 - i << " -Ian-21\n";

                }
                if (i > 44 && i <= 75)
                {
                    myfile << 76 - i << " -Dec-21\n";

                }
                if (i > 75 && i <= 100)
                {
                    myfile << 101 - i << " -Nov-21\n";

                }
            }
            if (e.val.at(i) > b.val.at(j) && b.vis.at(i) == 0)
            {
                myfile << k++ << "\t";
                myfile << b.val.at(i) << "\tBitcoin\t";
                b.vis.at(i) = 1;
                if (i <= 13)
                {
                    myfile << 14 - i << " -Feb-21\n";

                }
                if (i > 13 && i <= 44)
                {
                    myfile << 45 - i << " -Ian-21\n";

                }
                if (i > 44 && i <= 75)
                {
                    myfile << 76 - i << " -Dec-21\n";

                }
                if (i > 75 && i <= 100)
                {
                    myfile << 101 - i << " -Nov-21\n";

                }
            }

        }
    }
}
int main()
{
    int n;
    //cout << "Cititi gradul polinomului de predictie\nn>=2\n";
    n = 2;
    Ethereum e;
    e.setVal();
    e.getVal();
    e.setCoef(Predictie_Ethereum(n));
    cout << endl;
    e.getCoef();
    e.Generare();
    cout << endl;
    e.getGen();

    cout << endl;

    //e.Afisare_finala();

    Bitcoin b;
    b.setVal();
    b.getVal();
    b.setCoef(Predictie_Bitcoin(n));
    cout << endl;
    b.getCoef();
    b.Generare();
    cout << endl;
    b.getGen();

    cout << endl;

    //b.Afisare_finala();
    Afisare_finala(e, b);
    Ordoare(e, b);
    return 0;
}
