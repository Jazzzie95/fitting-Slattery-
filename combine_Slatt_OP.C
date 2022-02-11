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

using namespace std;
void combine_Slatt_OP()
{

  gStyle->SetOptFit(1);

    //Input
    const char *fileW1[1]  = {"W_1 (copy)"};// "W_1_quad" file with quad errors
    const char *fileW2[1] = {"W_2 (copy)"};
    const char *fileW3[1] = {"W_3 (copy)"};
    const char *file1[1] = {"W_all (copy)"};
    const double file2[1] = {0.1};
    const double file3[1] = {4};
//    const double file4[1]= {0.001};
    const double file5[1] = {30.0};
    const double file6[1] = {-9.0};
    const double file7[1] = {3.2};
    
  const char *file8[1] = {"Slattery_FIT_3Set_1_R_QE(copy)"};

  char name1[200]; char name2[200]; char name3[200]; char nameW1[200]; char nameW2[200]; char nameW3[200];
  char name_graphG[200];  char name_fitG[200];

  for(int i=0;i<1;i++){

     sprintf(name1, "%s.txt", file1[i]);
     sprintf(nameW1, "%s.txt", fileW1[i]);
     sprintf(nameW2, "%s.txt", fileW2[i]);
     sprintf(nameW3, "%s.txt", fileW3[i]);
    TGraphErrors graph(name1);
    TGraphErrors graphW1(nameW1);
    TGraphErrors graphW2(nameW2);
    TGraphErrors graphW3(nameW3);
    graph.SetTitle("Slattery Fit to KNO-Dist. for OPERA for_3Sets_R_QE(copy)");

    graph.SetMarkerStyle(kOpenCircle);
    graphW1.SetMarkerStyle(24);
    graphW2.SetMarkerStyle(20);
    graphW3.SetMarkerStyle(22);
    graph.SetMarkerColor(kWhite);
    graphW1.SetMarkerColor(kGreen);
    graphW2.SetMarkerColor(kViolet);
    graphW3.SetMarkerColor(kBlue);
    graph.SetLineColor(kWhite);
    graphW1.SetLineColor(kGreen);
    graphW2.SetLineColor(kViolet);
    graphW3.SetLineColor(kBlue);
    
    //graph.GetYaxis()->SetMaximum(0.15);
      graph.GetXaxis()->SetTitle(" z'= (nch-alpha)/<nch-alpha>");
      graph.GetYaxis()->SetTitle(" <nch-alpha>*P(nch) ");

      graph.GetXaxis()->SetLimits(0,4.5);
      graph.GetYaxis()->SetRangeUser(-0.1,1.5);

      
// Slattery function
      TF1
        f("f","(([0]*TMath::Power(x,3)+ [1]*TMath::Power(x,4))*TMath::Exp(-[2]*x))",file2[i], file3[i]);

      
//    f.SetParNames("N","A","B","C");
   f.SetParNames("A", "B", "C");
//    f.SetParameter(0, file4[i]); // N (normalization constant)
    f.SetParameter(0, file5[i]); // A
    f.SetParameter(1, file6[i]); // B
    f.SetParameter(2, file7[i]); // C
     
      
    graph.Fit(&f, "ME0");

      TCanvas* c1 = new TCanvas();
//    sprintf(name2, "PNG/%s.png", file8[i]);
    sprintf(name3, "PDF-SLATT/%s.pdf", file8[i]);
    graph.DrawClone("APE");
    graphW1.DrawClone("pe Same");
    graphW2.DrawClone("pe Same");
    graphW3.DrawClone("pe Same");
    f.DrawClone("Same");
      
    auto legend = new TLegend(0.89,0.6,0.58,0.48);
    legend->SetBorderSize(0);
    legend->AddEntry(&graphW1,"for 1 < W^2 < 9 GeV^2/c^4");
    legend->AddEntry(&graphW2,"for 9 < W^2 < 19 GeV^2/c^4");
    legend->AddEntry(&graphW3,"for W^2 > 19 GeV^2/c^4");

    legend->DrawClone("Same");  
      
 //     c1->SaveAs(name2);
      c1->SaveAs(name3);
      
//     sprintf(name_graphG, "%s_graphG", file1[i]);
 //     sprintf(name_fitG, "%s_fitG", file1[i]);
 //     graph.Write(name_graphG);
 //     f.Write(name_fitG);
      
    cout<<""<<endl;
    cout<<""<<endl;


    TMatrixD matrix0(3,3);
    gMinuit->mnemat(matrix0.GetMatrixArray(),3); // store covariance matrix
    
    cout << matrix0(1,1) <<"   "<<  matrix0(1,2) << "    " << matrix0(1,3) <<endl;
    cout << matrix0(2,1) <<"   "<<  matrix0(2,2) << "    " << matrix0(2,3) <<endl;
  cout << matrix0(3,1) <<"   "<<  matrix0(3,2) << "    " << matrix0(3,3) <<endl;
      
  
    
    gMinuit->mnmatu(1); // prit correlation and covariance matrix


    Double_t det1;
    TMatrixD H1 =matrix0;
    H1.InvertFast(&det1); // H1 is inverse of matrix0

    cout << " determinant is = "  << det1 << endl; 
    //   gMinuit->mnmatu(1);

    
    //double * elements=matrix0.GetElements();
      //  matrix0.GetElements(elements);


  }
}
