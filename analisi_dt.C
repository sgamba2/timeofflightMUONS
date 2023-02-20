#define analisi_dt_cxx
#include "analisi_dt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TF1.h"

bool reject;
double fline(double *x, double *par)
{
    if (reject && x[0] > 80 && x[0] < 100) {
      TF1::RejectPoint();
      return 0;
   }
   return par[0] + par[1]*0*x[0];
}
double background(double *x, double *par) {
   return par[0] + 0*x[0];
}

double gass(double * x, double *par){
    return par[0]*exp(-0.5*((x[0]-par[1])/par[2])*((x[0]-par[1])/par[2]));
}

double fitFunction(double *x, double *par) {
    return background(x,&par[0])+gass(x,&par[1]);
}


void func(TH1F* hist, double *par,double low, double up){

}

double *gettingpar(TH1F* hist, float low , float up, float peaklow , float peakup, float param){
    TF1 *fl = new TF1("fl",fline,low,up,2);
    fl->SetParameters(1.,0.);
    reject = true;
    hist->Fit(fl,"N","",low,up);
    reject = false;
    double par[6];
    TF1 *fright = new TF1("fright",fline,peakup,up,1);
    fright->SetParameters(fl->GetParameters());
    hist->GetListOfFunctions()->Add(fright);
    gROOT->GetListOfFunctions()->Remove(fright);
    TF1 *fleft = new TF1("fleft",fline,low,peaklow,1);
    fleft->SetParameters(fl->GetParameters());
    hist->GetListOfFunctions()->Add(fleft);
    gROOT->GetListOfFunctions()->Remove(fleft);
    TF1 *f1 = new TF1("f1","gaus",peaklow,peakup,3);
    f1->SetParameters(60,param,3);
    hist->Fit(f1,"N","",peaklow,peakup);
    fl->GetParameters(&par[0]);
    f1->GetParameters(&par[1]);
    return par;
}

void fittinghisto(TH1F* hist, double * par, double low,double up){
    
    TF1 *tot = new TF1("tot",fitFunction,low,up,4);
    tot->SetParameters(par);
    tot->SetParNames("bkg","norm","mean","stddev");
    hist->Fit(tot,"L","",low,up);
    gStyle->SetOptFit(1111);
    hist->DrawClone("E1");
    
}

void analisi_dt::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analisi_dt.C
//      root> analisi_dt t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout<<"n entries = "<<nentries<<std::endl;
   Long64_t nbytes = 0, nb = 0;
       
    int nbins = 50;
    TH1F *histogram1= new TH1F("#Delta t12","Istogramma #Delta t PM1-PM2 -- V1=1650/V2=1625",nbins, -10, 6);
    TH1F *histogram2= new TH1F("#Delta t23","Istogramma #Delta t PM2-PM3 -- V1=1650/V2=1625",nbins, 12, 28);
    TH1F *histogram3= new TH1F("#Delta t13","Istogramma #Delta t PM1-PM3 -- V1=1650/V2=1625",nbins, 10, 26);
    
    Double_t V_th = -0.2; //V
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
      // if (Cut(ientry) < 0) continue;

	//////// Save times

	Double_t t1_signal = -1.;
	Double_t t2_signal = -1.;
	Double_t t3_signal = -1.;
    
	
        for(int i=0; i<1064; i++){
            if(w0[i]<V_th){
                t1_signal = t0[i];
                break;
            }
        }

        for(int i=0; i<1064; i++){
            if(w1[i]<V_th){
                t2_signal = t1[i];
                break;
            }
        }
        
        for(int i=0; i<1064; i++){
            if(w2[i]<V_th){
                t3_signal = t2[i];
                break;
            }
        }

	if(t1_signal>0. and t2_signal>0. and t3_signal>0. ){
	  Double_t Delta_t12 = t1_signal-t2_signal;
	  Double_t Delta_t13 = t1_signal-t3_signal;
	  Double_t Delta_t23 = t2_signal-t3_signal;

        histogram1->Fill(Delta_t12);
	histogram2->Fill(Delta_t23);
	histogram3->Fill(Delta_t13);}

    }

    
    TCanvas *c_isto1 = new TCanvas("Istogramma Dt12", "Istogramma Dt12",700,500);
    c_isto1->cd();

    
    //histogram1->Draw();
    double* par1=gettingpar(histogram1,-10, 6, -4,-1,0);
    fittinghisto(histogram1,par1,-10, 6);
    histogram1->SetLineColor(4);
    
    histogram1->GetXaxis()->SetTitle("#Delta t [ns]");
    histogram1->GetYaxis()->SetTitle("Occorrenze");
    c_isto1->Print("./Grafici/tel2_Deltat_12.pdf");

    TCanvas *c_isto2 = new TCanvas("Istogramma Dt23", "Istogramma Dt23",700,500);
    c_isto2->cd();

    double* par2=gettingpar(histogram2,12,28,16,22,18);
    fittinghisto(histogram2,par2,12,28);
    histogram2->SetLineColor(4);
    histogram2->GetXaxis()->SetTitle("#Delta t [ns]");
    histogram2->GetYaxis()->SetTitle("Occorrenze");
    
    c_isto2->Print("./Grafici/tel2_Deltat_23.pdf");

    
    TCanvas *c_isto3 = new TCanvas("Istogramma Dt13", "Istogramma Dt13",700,500);
    c_isto3->cd();

    double* par3=gettingpar(histogram3,10, 26,14,20,17);
    fittinghisto(histogram3,par3,10, 26);
    histogram3->SetLineColor(4);
    histogram3->GetXaxis()->SetTitle("#Delta t [ns]");
    histogram3->GetYaxis()->SetTitle("Occorrenze");

    c_isto3->Print("./Grafici/tel2_Deltat_13.pdf");
      
    
    
}
