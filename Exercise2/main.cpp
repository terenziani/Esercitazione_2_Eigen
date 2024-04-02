/* Andrea Terenziani s284817
 *
 * Questo programma risolve i sistemi lineari Ax=b con A matrice 2x2 e b vettore dei termini noti di
 * dimensione 2, utilizzando prima il metodo PA=LU e poi il metodo QR.
 * Per entrambi i metodi viene inoltre valutato il rispettivo errore relativo, data la soluzione esatta x=[-1,-1].
 * Ci sono 3 input distinti per tale esercizio:
 * 1. A = [5.547001962252291e-01, -3.770900990025203e-02; 8.320502943378437e-01,-9.992887623566787e-01], b = [-5.169911863249772e-01; 1.672384680188350e-01]
 * 2. A = [5.547001962252291e-01, -5.540607316466765e-01; 8.320502943378437e-01,-8.324762492991313e-01], b = [-6.394645785530173e-04; 4.259549612877223e-04]
 * 3. A = [5.547001962252291e-01, -5.547001955851905e-01; 8.320502943378437e-01,-8.320502947645361e-01], b = [-6.400391328043042e-10; 4.266924591433963e-10]
*/










#include <iostream>
#include <fstream>
#include "Eigen/Eigen"


using namespace std;
using namespace Eigen;


//funzione che calcola i risultati con il metodo PA=LU

VectorXd risPALU( MatrixXd matrice, VectorXd vettore)
{
    VectorXd x=matrice.fullPivLu().solve(vettore);
    return x;
}


//funzione che calcola i risultati con il metodo QR

Vector2d risQR ( MatrixXd matrice, VectorXd vettore )
{
    VectorXd x=matrice.colPivHouseholderQr().solve(vettore);
    return x;
}


//funzione che calcola gli errori relativi

double errRel ( VectorXd vettorereale, VectorXd vettoremetodo)
{
    if (vettorereale.norm()!= 0)
    {
        double errorerelativo= (vettorereale - vettoremetodo ).norm()/(vettorereale).norm();

        return errorerelativo;

    }

    else
    {

        double errorerelativo=-1;
        return errorerelativo;

    }

}







int main()
{
    //apro i file di input e output

    string filename2("result.csv");

    ofstream ofs(filename2);


    //controllo che si siano correttamente aperti

    if (! ofs.is_open())
    {
        cout<<"il file di output non è stato aperto correttamnete"<<"\n";
    }

    else
    {
        //creo il vettore x delle soluzioni esatte

        Vector2d soluzione= VectorXd::Ones(2)* -1;

        //definisco le matrici

        Matrix2d A1,A2,A3;

        A1 << 5.547001962252291e-01, -3.770900990025203e-02, 8.320502943378437e-01,-9.992887623566787e-01;

        A2 << 5.547001962252291e-01, -5.540607316466765e-01, 8.320502943378437e-01,-8.324762492991313e-01;

        A3 << 5.547001962252291e-01, -5.547001955851905e-01, 8.320502943378437e-01,-8.320502947645361e-01;

        //definisco i vettori

        Vector2d b1,b2,b3;

        b1<<-5.169911863249772e-01, 1.672384680188350e-01;

        b2<<-6.394645785530173e-04, 4.259549612877223e-04;

        b3<<-6.400391328043042e-10, 4.266924591433963e-10;



        //calcolo i vettori x mediante il metodo PA=LU

        Vector2d x1PALU= risPALU( A1, b1);

        Vector2d x2PALU= risPALU( A2, b2);

        Vector2d x3PALU= risPALU( A3, b3);


        //calcolo i vettori x mediante il metodo QR

        Vector2d x1QR= risQR( A1, b1);

        Vector2d x2QR= risQR( A2, b2);

        Vector2d x3QR= risQR( A3, b3);


        //calcolo gli errori relativi ottenuti con il metodo PA=LU

        double err1PALU= errRel( soluzione, x1PALU );

        double err2PALU= errRel( soluzione, x2PALU );

        double err3PALU= errRel( soluzione, x3PALU );



        //calcolo gli errori relativi ottenuti con il metodo QR

        double err1QR= errRel( soluzione, x1QR );

        double err2QR= errRel( soluzione, x2QR );

        double err3QR= errRel( soluzione, x3QR );



        //stampo sul file output le soluzioni


        ofs<<"la soluzione del caso 1 utilizzando PA=LU e \n"<<x1PALU<<"\n";
        ofs<<"la soluzione del caso 1 utilizzando QR e \n"<<x1QR<<"\n";
        ofs<<"l'errore relativo del caso 1 usando il metodo PA=LU e "<<err1PALU<<"\n";
        ofs<<"l'errore relativo del caso 1 usando il metodo QR e "<<err1QR<<"\n";

        ofs<<"--------------------------------------------- \n";

        ofs<<"la soluzione del caso 2 utilizzando PA=LU e \n"<<x2PALU<<"\n";
        ofs<<"la soluzione del caso 2 utilizzando QR e \n"<<x2QR<<"\n";
        ofs<<"l'errore relativo del caso 2 usando il metodo PA=LU e "<<err2PALU<<"\n";
        ofs<<"l'errore relativo del caso 2 usando il metodo QR e "<<err2QR<<"\n";


        ofs<<"--------------------------------------------- \n";

        ofs<<"la soluzione del caso 3 utilizzando PA=LU e \n"<<x3PALU<<"\n";
        ofs<<"la soluzione del caso 3 utilizzando QR e \n"<<x3QR<<"\n";
        ofs<<"l'errore relativo del caso 3 usando il metodo PA=LU e "<<err3PALU<<"\n";
        ofs<<"l'errore relativo del caso 3 usando il metodo QR e "<<err3QR<<"\n";






    }


    ofs.close();

    return 0;
}
