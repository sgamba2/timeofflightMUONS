#define analisi_dt_cxx
#include "analisi_dt.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TF1.h"

bool reject;
double fline(double *x, double *par)
{
    if (reject && x[0] > par[2] && x[0] < par[3]) {
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


/*std::vector<double> gettingpar(TH1F* hist, double low , double up, double peaklow , double peakup, double param1, double param2, double param3){
    TF1 *fl = new TF1("fl",fline,low,up,4);
    fl->SetParameters(1.,0.,peaklow,peakup);
    reject = true;
    hist->Fit(fl,"N","",low,up);
    reject = false;
    std::vector<double> par;
    TF1 *fright = new TF1("fright",fline,peakup,up,1);
    fright->SetParameters(fl->GetParameters());
    hist->GetListOfFunctions()->Add(fright);
    gROOT->GetListOfFunctions()->Remove(fright);
    TF1 *fleft = new TF1("fleft",fline,low,peaklow,1);
    fleft->SetParameters(fl->GetParameters());
    hist->GetListOfFunctions()->Add(fleft);
    gROOT->GetListOfFunctions()->Remove(fleft);
    TF1 *f1 = new TF1("f1","gaus",peaklow,peakup,3);
    f1->SetParameters(param1,param2,param3);
    hist->Fit(f1,"N","",peaklow,peakup);
    double parameters[4];
    fl->GetParameters(&parameters[0]);
    f1->GetParameters(&parameters[1]);
    par.push_back(parameters[0]);
    par.push_back(parameters[1]);
    par.push_back(parameters[2]);
    par.push_back(parameters[3]);
    for (int i=0; i<size(par);i++){
        std::cout<<par.at(i)<<std::endl;
    }
    return par;
}

void fittinghisto(TH1F* hist,  std::vector<double> par, double low,double up){
    
    TF1 *tot = new TF1("tot",fitFunction,low,up,4);
    tot->SetParameters(&par[0]);
    tot->SetParNames("bkg","norm","mean","stddev");
    hist->Fit(tot,"L","",low,up);
    gStyle->SetOptFit(1111);
    //hist->DrawClone("E1");
    
}*/

void fittingHist(TH1F* hist, double low , double up, double peaklow , double peakup, double param1, double param2, double param3,std::string title){
    TCanvas *c_isto1 = new TCanvas(title.c_str(),title.c_str(),700,500);
    TF1 *fl = new TF1("fl",fline,low,up,4);
    fl->SetParameters(1.,0.,peaklow,peakup);
    reject = true;
    hist->Fit(fl,"N","",low,up);
    reject = false;
    std::vector<double> par;
    TF1 *fright = new TF1("fright",fline,peakup,up,1);
    fright->SetParameters(fl->GetParameters());
    hist->GetListOfFunctions()->Add(fright);
    gROOT->GetListOfFunctions()->Remove(fright);
    TF1 *fleft = new TF1("fleft",fline,low,peaklow,1);
    fleft->SetParameters(fl->GetParameters());
    hist->GetListOfFunctions()->Add(fleft);
    gROOT->GetListOfFunctions()->Remove(fleft);
    TF1 *f1 = new TF1("f1","gaus",peaklow,peakup,3);
    f1->SetParameters(param1,param2,param3);
    hist->Fit(f1,"N","",peaklow,peakup);
    double parameters[4];
    fl->GetParameters(&parameters[0]);
    f1->GetParameters(&parameters[1]);
    par.push_back(parameters[0]);
    par.push_back(parameters[1]);
    par.push_back(parameters[2]);
    par.push_back(parameters[3]);
    TF1 *tot = new TF1("tot",fitFunction,low,up,4);
    tot->SetParameters(&par[0]);
    tot->SetParNames("bkg","norm","mean","stddev");
    hist->Fit(tot,"L","",low,up);
    gStyle->SetOptFit(1111);
    hist->SetLineColor(4);
    hist->GetXaxis()->SetTitle("#Delta t [ns]");
    hist->GetYaxis()->SetTitle("Occorrenze");
    hist->Draw("E1");
    c_isto1->SaveAs(("./Grafici/"+title+".pdf").c_str());
    //hist->DrawClone("E1");

    
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
       
    constexpr int nbins = 100;
    TH1F *histogram1= new TH1F("#Delta t12","Istogramma #Delta t PM1-PM2 -- V1=1800/V2=1800",nbins, -22,-14);
    TH1F *histogram2= new TH1F("#Delta t23","Istogramma #Delta t PM2-PM3 -- V1=1800/V2=1800",nbins,  20 ,35);
    TH1F *histogram3= new TH1F("#Delta t13","Istogramma #Delta t PM1-PM3 -- V1=1800/V2=1800",nbins,2,14);
    
       Double_t V_th = -0.02; //V
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);
        nbytes += nb;
      // if (Cut(ientry) < 0) continue;


 /////// Graph event #4

	if(jentry == 344){
	  TCanvas* c_PMT_4 = new TCanvas("c_PMT_4", "c_PMT_4", 700, 500);

	  TMultiGraph* mg = new TMultiGraph("mg", "mg");
	  mg->SetTitle("Waveform signals PMT1-PMT2-PMT3 for event 344; Time [ns]; Voltage [V]");
	  //PMT1
	  TGraph * wave_PMT1 = new TGraph(800, t0, w0);
	  wave_PMT1->SetTitle("PMT1");
	 
	  wave_PMT1->SetMarkerStyle(7);
	  wave_PMT1->SetMarkerColor(4);
	  wave_PMT1->SetLineColor(4);


		  
	  //PMT2
	  TGraph * wave_PMT2 = new TGraph(800, t1, w1);
	  wave_PMT2->SetTitle("PMT2");
	  wave_PMT2->GetXaxis()->SetTitle("Time [ns]");
	  wave_PMT2->GetYaxis()->SetTitle("Voltage [V]");
	  wave_PMT2->SetMarkerStyle(7);
	  wave_PMT2->SetMarkerColor(2);
	  wave_PMT2->SetLineColor(2);


	  //PMT3
	  TGraph * wave_PMT3 = new TGraph(800, t2, w2);
	  wave_PMT3->SetTitle("PMT3");
	  wave_PMT3->GetXaxis()->SetTitle("Time [ns]");
	  wave_PMT3->GetYaxis()->SetTitle("Voltage [V]");
	  wave_PMT3->SetMarkerStyle(7);
	  wave_PMT3->SetMarkerColor(8);
	  wave_PMT3->SetLineColor(8);

	  // Line Vth

	  TLine* l = new TLine(0.,V_th,160.,V_th);
	  l->SetLineColor(1);
	  l->SetLineStyle(2);

	  //l->SetTitle("Threshold");
	    
	  mg->Add(wave_PMT1);
	  mg->Add(wave_PMT2);
	  mg->Add(wave_PMT3);
	  c_PMT_4->cd();
	  mg->Draw("al");
	  l->Draw("same");
	  
	  TLegend* leg = new TLegend(0.2, 0.2, 0.4, 0.4);
	  leg->AddEntry(wave_PMT1);
	  leg->AddEntry(wave_PMT2);
	  leg->AddEntry(wave_PMT3);
	  leg->AddEntry(l, "V threshold");

	  leg->Draw();
	  c_PMT_4->Print("./Grafici/waveforms_ev4.pdf");
	}



 
	//////// Save times

	Double_t t1_signal = 0.;
	Double_t t2_signal = 0.;
	Double_t t3_signal = 0.;
	Int_t accept_event = 0;


	
       
        for(int i=10; i<1060; i++){
	  if(w0[i]<V_th and w0[i-1]>V_th ){
                t1_signal = t0[i];
            }
	  if(w0[i]<-0.3){
	    accept_event +=1;
	    break;}
	  
        }

        for(int i=10; i<1060; i++){
             if(w1[i]<V_th and w1[i-1]>V_th ){
                t2_signal = t1[i];
            }
	  if(w1[i]<-0.3){
	    accept_event +=1;
	    break;}
        }

	 for(int i=10; i<1060; i++){
         if(w2[i]<V_th and w2[i-1]>V_th ){
                t3_signal = t2[i];
            }
	  if(w2[i]<-0.3){
	    accept_event +=1;
	    break;}
    }

	if(accept_event==3){
	  Double_t Delta_t12 = t1_signal-t2_signal;
	  Double_t Delta_t13 =  t1_signal-t3_signal;
	  Double_t Delta_t23 = t2_signal-t3_signal;

	
	  histogram1->Fill(Delta_t12);
    histogram2->Fill(Delta_t13);
    histogram3->Fill(Delta_t23);
	  // histogram23->Fill(Delta_t23);
	  //histogram13->Fill(Delta_t13);
	}
    
    else{
      std::cout<<"i scartato = "<<jentry<<std::endl;
    }
    }
    

    fittingHist(histogram1,-22,-14, -25,-18,30 ,-20 ,0.9759,"Istogramma_Dt12");
    fittingHist(histogram2,  20,35,24,30,16.33 ,26 ,1.393,"Istogramma_Dt23");
    fittingHist(histogram3,2,14,4,8,27.97,6,1.255,"Istogramma_Dt13");
    
    
    
}