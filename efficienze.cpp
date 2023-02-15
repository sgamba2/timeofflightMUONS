#include <TROOT.h>
#include <vector>
#include <string>
#include <TGraph.h>
#include <TCanvas.h>
#include <cctype>
#include <iostream>
#include <time.h>

void pmtEff(std::vector<float> PMT_voltage, std::vector<float> eff, std::string cst){
    /***********************************************************
    \brief Graph of pmt efficiencies in function of pmt voltage
    \par pmt voltage
    \par pmt efficiencies
    \par name of canvas
    \return None
    ***********************************************************/
    TCanvas* c = new TCanvas(cst.c_str(),"",1100,900);
    TGraph* PMT = new TGraph(size(PMT_voltage),&PMT_voltage[0],&eff[0]);
    std::string title = "Efficiency vs Voltage-PMT"+cst;
    PMT->SetTitle(title.c_str());
    PMT->SetMarkerStyle(8);
    PMT->GetXaxis()->SetTitle("Voltage");
    PMT->GetYaxis()->SetTitle("Efficiency");
    PMT->SetLineStyle(2);
    PMT->Draw();
    title=title+".pdf";
    c->SaveAs(title.c_str());

}

void pmtCounts(std::vector<float> PMT_voltage, std::vector<float> PMT_counts, std::string cst){
    /***********************************************************
    \brief Graph of pmt efficiencies in function of pmt voltage
    \par pmt voltage
    \par pmt efficiencies
    \par name of canvas
    \return None
    ***********************************************************/
    TCanvas* c = new TCanvas(("c"+cst).c_str(),"",1100,900);
    TGraph* PMT = new TGraph(size(PMT_voltage),&PMT_voltage[0],&PMT_counts[0]);
    std::string title = "Counts vs Voltage-PMT"+cst;
    PMT->SetTitle(title.c_str());
    PMT->SetMarkerStyle(8);
    PMT->GetXaxis()->SetTitle("Voltage");
    PMT->GetYaxis()->SetTitle("Efficiency");
    PMT->SetLineStyle(2);
    PMT->Draw();
    title=title+".pdf";
    c->SaveAs(title.c_str());

}

void efficienze(){
    /***********************************************************
    \brief measurements of COUNTS vs VOLTAGE of PMT1, PMT2, PMT3
    coincidence 1-2
    Threshold for all PMTs -40mV
    first measurements all done in 100s
    \par None
    \return None
    ***********************************************************/
    std::vector<float> PMT1_counts {8963,11948,16274,18654,21159,27257,29929,33988,36693,40508,48386};
    std::vector<float> PMT1_voltage {1450,1500,1550,1575,1600,1650,1675,1700,1725,1750,1800};

    std::vector<float> PMT2_counts {9130,11923,15773,17533,19720,24964,28100,29772,33471,51764,61708};
    std::vector<float> PMT2_voltage {1450,1500,1550,1575,1600,1650,1675,1700,1725,1750,1800};

    std::vector<float> PMT3_counts {648,812,1001,1043,1199,1334,1518,1594,1738,1762,1995};
    std::vector<float> PMT3_voltage {1450,1500,1550,1575,1600,1650,1675,1700,1725,1750,1800};

    std::vector<float> coincidence_12 {3375,4902,7345,8682,10147,13779,15141,17024,18931,20934,25255};

    std::vector<float> eff1 {};
    std::vector<float> eff2 {};

    for(int i=0; i<size(PMT1_voltage); i++){
        eff1.push_back(coincidence_12.at(i)/PMT1_counts.at(i));
        eff2.push_back(coincidence_12.at(i)/PMT2_counts.at(i));
    }

    pmtEff(PMT1_voltage, eff1,"1");
    pmtEff(PMT2_voltage, eff2,"2");
    pmtCounts(PMT2_voltage, PMT1_counts,"1");
    pmtCounts(PMT2_voltage, PMT2_counts,"2");
    pmtCounts(PMT2_voltage, PMT3_counts,"3");
    
}
   
   
   