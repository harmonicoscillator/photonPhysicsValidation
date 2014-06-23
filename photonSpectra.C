#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLatex.h>
#include <TGraph.h>
#include <TString.h>
#include <stdio.h>
#include <TLegendEntry.h>
#include <TGraphAsymmErrors.h>


void photonSpectra()
{
  const TString forest_input = "/mnt/hadoop/cms/store/user/richard/2014-photon-forests/PbPb_Data_unmerged/*.root";
  TChain *photons = new TChain("multiPhotonAnalyzer/photon","photons");
  TChain *hlt = new TChain("hltanalysis/HltTree","hlt");

  photons->Add(forest_input);
  hlt->Add(forest_input);
  photons->AddFriend(hlt);

  TFile *outfile = TFile::Open("goodpt.root","RECREATE");
  TH1D *goodpt = new TH1D("goodpt",
			  ";pt[0], abs(eta[0])<2.4 && hadronicOverEm[0]<0.1 && HLT_HISinglePhoton20_v2",
			  1000,0,1000);

  photons->Project("goodpt","pt[0]","abs(eta[0])<2.4 && hadronicOverEm[0]<0.1 && HLT_HISinglePhoton20_v2");

  outfile->cd();
  goodpt->Write();
  outfile->Close();
  delete goodpt;
  delete outfile;
}

int main()
{
  photonSpectra();
  return 0;
}
