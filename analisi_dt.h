//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Feb 16 12:41:40 2023 by ROOT version 6.26/06
// from TTree rec/rec
// found on file: PMT123_15_02.root
//////////////////////////////////////////////////////////

#ifndef analisi_dt_h
#define analisi_dt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class analisi_dt {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        t0[1024];
   Double_t        t1[1024];
   Double_t        t2[1024];
   Double_t        t3[1024];
   Double_t        t4[1024];
   Double_t        t5[1024];
   Double_t        t6[1024];
   Double_t        t7[1024];
   Double_t        w0[1024];
   Double_t        w1[1024];
   Double_t        w2[1024];
   Double_t        w3[1024];
   Double_t        w4[1024];
   Double_t        w5[1024];
   Double_t        w6[1024];
   Double_t        w7[1024];

   // List of branches
   TBranch        *b_t0;   //!
   TBranch        *b_t1;   //!
   TBranch        *b_t2;   //!
   TBranch        *b_t3;   //!
   TBranch        *b_t4;   //!
   TBranch        *b_t5;   //!
   TBranch        *b_t6;   //!
   TBranch        *b_t7;   //!
   TBranch        *b_w0;   //!
   TBranch        *b_w1;   //!
   TBranch        *b_w2;   //!
   TBranch        *b_w3;   //!
   TBranch        *b_w4;   //!
   TBranch        *b_w5;   //!
   TBranch        *b_w6;   //!
   TBranch        *b_w7;   //!

   analisi_dt(TTree *tree=0);
   virtual ~analisi_dt();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analisi_dt_cxx
analisi_dt::analisi_dt(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("PMT123_16_02_V2_1625_V1_1650.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("PMT123_16_02_V2_1625_V1_1650.root");
      }
      f->GetObject("rec",tree);

   }
   Init(tree);
}

analisi_dt::~analisi_dt()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analisi_dt::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analisi_dt::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analisi_dt::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("t0", t0, &b_t0);
   fChain->SetBranchAddress("t1", t1, &b_t1);
   fChain->SetBranchAddress("t2", t2, &b_t2);
   fChain->SetBranchAddress("t3", t3, &b_t3);
   fChain->SetBranchAddress("t4", t4, &b_t4);
   fChain->SetBranchAddress("t5", t5, &b_t5);
   fChain->SetBranchAddress("t6", t6, &b_t6);
   fChain->SetBranchAddress("t7", t7, &b_t7);
   fChain->SetBranchAddress("w0", w0, &b_w0);
   fChain->SetBranchAddress("w1", w1, &b_w1);
   fChain->SetBranchAddress("w2", w2, &b_w2);
   fChain->SetBranchAddress("w3", w3, &b_w3);
   fChain->SetBranchAddress("w4", w4, &b_w4);
   fChain->SetBranchAddress("w5", w5, &b_w5);
   fChain->SetBranchAddress("w6", w6, &b_w6);
   fChain->SetBranchAddress("w7", w7, &b_w7);
   Notify();
}

Bool_t analisi_dt::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analisi_dt::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analisi_dt::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analisi_dt_cxx
