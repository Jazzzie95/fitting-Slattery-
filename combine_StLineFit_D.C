#include "TCanvas.h"
#include "TROOT.h"
#include "TMath.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"
#include "TMatrixD.h"
#include "TMinuit.h"


// input file at 20, output file at 27, set title at 38, set y axis at 47, set limits on x and y at 52, fit function at 61, parameter names  at 65
using namespace std;
void combine_StLineFit_D()
{
   gStyle->SetOptFit(1);
//    const char *file1[1] = {"AVNVSWSQ"};
//    const char *file1[1] = {"DATA_D_vs_n_ch_1"}; //input file
    const char *file1[1] = {"nP_n"}; //input file
    const double file2[1] = {0.34}; //Min for the TF1 for fit
    const double file3[1] = {3.4};//max for the TF1 for fit
    const double file4[1]= {0.1};// Given fit parameter first
    const double file5[1] = {0.2};// Giveen fit parameter second
    const double file6[1] = {0.3};
//  const char *file7[1] = {"AVNVSWSQ"};f
    const char *file7[1] = {"P(n_ch)_vs_n_ch_fit_QE"};//output 
    // const char *file7[1] = {"D(n_ch)_vs_n_ch"}; 
  char name1[200]; char name2[200]; char name3[200];
  char name_graphG[200];  char name_fitG[200];

  for(int i=0;i<1;i++){

     sprintf(name1, "%s.txt", file1[i]);//     What is %s.txt?
    TGraphErrors graph(name1);//               Is this saving the errors in name1 array?
    
    //graph.SetTitle("D(N_ch) Vs. N_ch for OPERAdata on Neutrino_R ");
    graph.SetTitle("P(N_ch) Vs. N_ch for OPERAdata on Neutrino_R with fit_QE ");
//      graph.SetTitle( "<Nch> Vs. ln(W^2) Fit");
      graph.SetMarkerStyle(20);
 //     graph.SetMarkerStyle(kDot);
    graph.SetMarkerColor(kBlue);
    graph.SetLineColor(kBlue);
//      graph.GetXaxis()->SetTitle(" ln<W^2>");
//      graph.GetYaxis()->SetTitle(" <Nch>");
      graph.GetXaxis()->SetTitle(" n_ch");
     // graph.GetYaxis()->SetTitle(" D(n_ch) ");
      graph.GetYaxis()->SetTitle(" P(n_ch) ");

    //graph.GetYaxis()->SetMaximum(0.15);
     //Pv/s N
      graph.GetXaxis()->SetLimits(-0.5,12);
      graph.GetYaxis()->SetRangeUser(-0.05,0.35);
     //D vs n
     // graph.GetXaxis()->SetLimits(-0.5,4.5);
     // graph.GetYaxis()->SetRangeUser(-0.05,3.5);
     
    // St. Line fit 
   // TF1 n("n","([0]*x + [1])",file2[i], file3[i]);
    // Negative Binomial fit ritu ma'am function
   TF1 n("n","((TMath::Gamma(x+[0])*TMath::Power(([1]/[0]),x))/(TMath::Gamma(x+1)*TMath::Gamma([0])*TMath::Power((1+([1]/[0])),x+[0])))",0,12);
      
  
     //  n.SetParNames("Slope","intercept");
    n.SetParNames("k","mean n");
   n.SetParameter(0, file4[i]); // c (normalization constant)
   n.SetParameter(1, file5[i]); // a
   
    graph.Fit(&n, "ME0");
 
      TCanvas* c1 = new TCanvas();
//    sprintf(name2, "PNG/%s.png", file7[i]);
    sprintf(name3, "PDF/%s.pdf", file7[i]);
    graph.DrawClone("AP");
    n.DrawClone("Same");
    
    TLegend *l = new TLegend(0.65,0.55,0.8,0.7);
    l->SetBorderSize(0);
    l->AddEntry(&graph,"data");
    l->SetTextSize(0.035);
    l->AddEntry(&n,"fit"); 
    l->DrawClone("Same");
      
 //     c1->SaveAs(name2);
      c1->SaveAs(name3);
      
//     sprintf(name_graphG, "%s_graphG", file1[i]);
 //     sprintf(name_fitG, "%s_fitG", file1[i]);
 //     graph.Write(name_graphG);
 //     f.Write(name_fitG);
      
  //  cout<<""<<endl;
   // cout<<""<<endl;
      
// Find the covariance matrix
      
 /*     TMatrixD matrix0(2,2);
      gMinuit->mnemat(matrix0.GetMatrixArray(),2); // store covariance matrix
      
//      cout << matrix0(0,0) <<"   "<<  matrix0(0,1) << "    " << matrix0(0,2) <<endl;
      cout << matrix0(0,0) <<"   "<<  matrix0(0,1)     <<endl;
      cout << matrix0(1,0) <<"   "<<  matrix0(1,1)    <<endl;
 
//  Find correltaion matrix from the covariance matrix

      gMinuit->mnmatu(1); // print correlation and covariance matrix
      
      Double_t det1;
      TMatrixD H1 =matrix0;
      H1.InvertFast(&det1); // H1 is inverse of matrix0

      cout << " determinant is = "  << det1 << endl;
      //   gMinuit->mnmatu(1);

      */
      //double * elements=matrix0.GetElements();
        //  matrix0.GetElements(elements);

  }
}
