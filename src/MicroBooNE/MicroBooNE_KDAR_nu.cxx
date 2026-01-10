// Copyright 2016 L. Pickering, P Stowell, R. Terri, C. Wilkinson, C. Wret

/*******************************************************************************
*    This file is part of NUISANCE.
*
*    NUISANCE is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    NUISANCE is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with NUISANCE.  If not, see <http://www.gnu.org/licenses/>.
*******************************************************************************/

#include "MicroBooNE_KDAR_nu.h"
#include "MicroBooNE_SignalDef.h"

//********************************************************************
MicroBooNE_KDAR_nu::MicroBooNE_KDAR_nu(nuiskey samplekey) {
//********************************************************************
  fSettings = LoadSampleSettings(samplekey);
  std::string name = fSettings.GetS("name");
  std::string objSuffix;

  if (!name.compare("MicroBooNE_KDAR_Kmu_nu")) {
    fDist = kKmu;
    objSuffix = "Kmu";
    fSettings.SetXTitle("K_{#mu}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dK_{#mu}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Kmu_nu_MCHist_true",";K_{#mu} (MeV)",26,0,130);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Kmu_nu_MCStat_true",";K_{#mu} (MeV)",26,0,130);
  }
  else if (!name.compare("MicroBooNE_KDAR_CosMu_nu")) {
    fDist = kCosMu;
    objSuffix = "CosMu";
    fSettings.SetXTitle("cos#theta_{#mu}^{reco}");
    fSettings.SetYTitle("1/#sigma d#sigma/dcos#theta_{#mu}^{reco}");
    // nothing implemented for now
  }
  else if (!name.compare("MicroBooNE_KDAR_pl_nu")) {
    fDist = kpl;
    objSuffix = "pl";
    fSettings.SetXTitle("p_{l}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dp_{l}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_pl_nu_MCHist_true",";p_{l} (MeV)",40,-200,200);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_pl_nu_MCStat_true",";p_{l} (MeV)",40,-200,200);
  }
  else if (!name.compare("MicroBooNE_KDAR_pt_nu")) {
    fDist = kpt;
    objSuffix = "pt";
    fSettings.SetXTitle("p_{t}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dp_{t}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_pt_nu_MCHist_true",";p_{t} (MeV)",25,0,200);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_pt_nu_MCStat_true",";p_{t} (MeV)",25,0,200);
  }
  else if (!name.compare("MicroBooNE_KDAR_Kp_nu")) {
    fDist = kKp;
    objSuffix = "Kp";
    fSettings.SetXTitle("K_{p}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dK_{p}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Kp_nu_MCHist_true",";K_{p} (MeV)",26,0,130);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Kp_nu_MCStat_true",";K_{p} (MeV)",26,0,130);
  }
  else if (!name.compare("MicroBooNE_KDAR_CosP_nu")) {
    fDist = kCosP;
    objSuffix = "CosP";
    fSettings.SetXTitle("1/#sigma cos#theta_{p}^{reco}");
    fSettings.SetYTitle("d#sigma/dcos#theta_{p}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_CosP_nu_MCHist_true",";K_{p} and cos_{p} bin",288,-0.5,287.5);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_CosP_nu_MCStat_true",";K_{p} and cos_{p} bin",288,-0.5,287.5);
  }
  else if (!name.compare("MicroBooNE_KDAR_Mult_nu")) {
    fDist = kMult;
    objSuffix = "Mult";
    fSettings.SetXTitle("Reconstructed Multiplicity");
    fSettings.SetYTitle("1/#sigma d#sigma/dN_{p}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Mult_nu_MCHist_true",";K_{p} (MeV)",26,0,130);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Mult_nu_MCStat_true",";K_{p} (MeV)",26,0,130);
  }
  else if (!name.compare("MicroBooNE_KDAR_Kvis_nu")) {
    fDist = kKvis;
    objSuffix = "Kvis";
    fSettings.SetXTitle("K_{vis}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dK_{vis}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Kvis_nu_MCHist_true",";K_{p} and K_{#mu} bin",160,-0.5,159.5);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Kvis_nu_MCStat_true",";K_{p} and K_{#mu} bin",160,-0.5,159.5);
  }
  else if (!name.compare("MicroBooNE_KDAR_sqrtQ2_nu")) {
    fDist = ksqrtQ2;
    objSuffix = "sqrtQ2";
    fSettings.SetXTitle("Q^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dQ^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_sqrtQ2_nu_MCHist_true",";Q",35,0,420);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_sqrtQ2_nu_MCStat_true",";Q",35,0,420);
  }
  else if (!name.compare("MicroBooNE_KDAR_q_nu")) {
    fDist = kq;
    objSuffix = "q";
    fSettings.SetXTitle("q^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dq^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_q_nu_MCHist_true",";q",40,0,480);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_q_nu_MCStat_true",";q",40,0,480);
  }
  else {
    assert(false);
  }

  // Sample overview ---------------------------------------------------
  std::string descrip = name + " sample.\n" \
                        "Target: Ar\n" \
                        "Flux: KDAR" \
                        "Signal: CC\n";

  fSettings.SetDescription(descrip);
  fSettings.SetTitle(name);
  fSettings.SetAllowedTypes("DIAG/FREE,SHAPE");
  fSettings.SetEnuRange(0.235, 0.236);
  fSettings.DefineAllowedTargets("Ar");
  fSettings.DefineAllowedSpecies("numu");
  FinaliseSampleSettings();

  // Load data ---------------------------------------------------------
  std::string inputFile = FitPar::GetDataBase() + "/MicroBooNE/KDAR/KDAR_dataRelease.root";
  SetDataFromRootFile(inputFile, "Data_" + objSuffix);

  // Unity since this is shape only
  fScaleFactor = 1; 

  SetCovarFromRootFile(inputFile, "Cov_" + objSuffix);
  covar = StatUtils::GetInvert(fFullCovar, true);
  fDecomp = StatUtils::GetDecomp(fFullCovar);

  TFile* inputRootFile = TFile::Open(inputFile.c_str());
  assert(inputRootFile && inputRootFile->IsOpen());
  fSmearingMatrix = (TH2D*) inputRootFile->Get(("R_" + objSuffix).c_str());
  fSmearingMatrix->SetDirectory(0);
  inputRootFile->Close();
  assert(fSmearingMatrix);

  // Final setup ------------------------------------------------------
  FinaliseMeasurement();
};


bool MicroBooNE_KDAR_nu::isSignal(FitEvent* event) {
  return SignalDef::MicroBooNE::isKDAR(event);
};


void MicroBooNE_KDAR_nu::FillEventVariables(FitEvent* event) {

  if (!isSignal(event)) { // double the work, but it lets us use the below functions without error checking
    fXVar = -999;
    return;
  }

  double Kmu = event->GetHMFSParticle(13)->KE();
  double CosMu = event->GetHMFSParticle(13)->fP.Vect().CosTheta();
  double SinMu = TMath::Sin(event->GetHMFSParticle(13)->fP.Vect().Theta());
  double pMu = event->GetHMFSParticle(13)->p();
  double pl = pMu*CosMu;
  double pt = pMu*SinMu; 
  double Kp = 0.00000001;
  double CosP = -2;
  if (event->NumFSParticle(2212) != 0){ 
    Kp = event->GetHMFSParticle(2212)->KE();
    CosP = event->GetHMFSParticle(2212)->fP.Vect().CosTheta();
  }
  double sprtQ2 = sqrt(event->GetQ2());
  double nu = event->Enu() - event->GetHMFSParticle(13)->E();
  double q = sprtQ2*sprtQ2 - nu*nu;

  if (fDist == kKmu) {
    fXVar = Kmu; 
  }
  else if (fDist == kCosMu) {
    fXVar = CosMu; 
  }
  else if (fDist == kpl) {
    fXVar = pl;
  }
  else if (fDist == kpt) {
    fXVar = pt;
  }
  else if (fDist == kKp || fDist == kMult) {
    fXVar = Kp;
  }
  else if (fDist == kCosP) {
    fXVar = GetBinTrueCosP(Kp,CosP);
  }
  else if (fDist == kKvis) {
    fXVar = GetBinTrueKvis(Kp,Kmu);
  }
  else if (fDist == ksqrtQ2) {
    fXVar = sprtQ2;
  }
  else if (fDist == kq) {
    fXVar = q;
  }

  if(fDist != kKvis && fDist != kCosP){ 
    double maxXVar = fMCHist_true->GetXaxis()->GetBinUpEdge(fMCHist_true->GetNbinsX());
    if (fXVar>maxXVar) fXVar=maxXVar-0.0001;
  }

}


int MicroBooNE_KDAR_nu::GetBinTrueCosP(double Kp, double CosP){

  int found_slice = -1;
  int found_bin = -1;
  int slice_width=8;
  int slice_min = 0;
  int slice_max = 128;
  int slice_nbins = int( (slice_max-slice_min)/slice_width);
  int bin_width=10;
  int min = 0;
  int max = 180;
  int nbins = int( (max-min)/bin_width);

  // Check all slices
  for(int slice_bin=0; slice_bin<slice_nbins; slice_bin++){
    // First check overflow
    if(Kp>slice_max){
      found_slice = slice_nbins-1;
      break;
    }
    // Now check all the slices
    if(Kp<slice_bin*slice_width+slice_width+slice_min && Kp>=slice_bin*slice_width+slice_min){
      found_slice = slice_bin;
      break;
    }
  }
  // Check all the bins
  for(int bin=0; bin<nbins; bin++){
    if(CosP<bin*bin_width+bin_width+min && CosP>bin*bin_width+min){
      found_bin = bin;
      break;
    }
  }

  if(found_slice<0 || found_bin<0){
    NUIS_ERR(WRN,fName << ": WARNING, could not find {Kp,CosP} bin.");
    return -1;
  }
 
  return found_slice*nbins+found_bin;

};


int MicroBooNE_KDAR_nu::GetBinTrueKvis(double Kp, double Kmu){

  bool found_slice = -1;
  bool found_bin = -1;
  int slice_width=12;
  int slice_min = 0;
  int slice_max = 120;
  int slice_nbins = int( (slice_max-slice_min)/slice_width);
  int bin_width=8;
  int min = 0;
  int max = 128;
  int nbins = int( (max-min)/bin_width);

  // Check all slices
  for(int slice_bin=0; slice_bin<slice_nbins; slice_bin++){
    // First check overflow
    if(Kp>slice_max){
      found_slice = slice_nbins-1;
      break;
    }
    // Now check all the slices
    if(Kp<slice_bin*slice_width+slice_width+slice_min && Kp>=slice_bin*slice_width+slice_min){
      found_slice = slice_bin;
      break;
    }
  }
  // Check all the bins
  for(int bin=0; bin<nbins; bin++){
    // First check overflow
    if(Kp>max){
      found_bin = nbins-1;
      break;
    }
    if(Kmu<bin*bin_width+bin_width+min && Kmu>bin*bin_width+min){
      found_bin = bin;
      break;
    } 
  } 

  if(found_slice<0 || found_bin<0){
    NUIS_ERR(WRN,fName << ": WARNING, could not find {Kp,Kmu} bin.");
    return -1;
  }
 
  return found_slice*nbins+found_bin;

};


void MicroBooNE_KDAR_nu::FillHistograms() {

  if (Signal) {

    NUIS_LOG(DEB, "Fill MCHist_true: " << fXVar << ", " << Weight);

    // If it's single bin, whatever the limits on the plot are don't apply
    if (fIsSingleBin){
      fMCHist->Fill(fMCHist->GetBinCenter(1), Weight);
      fMCStat->Fill(fMCStat->GetBinCenter(1), 1.0);
      if (fMCHist_Modes)
	fMCHist_Modes->Fill(Mode, fMCHist->GetBinCenter(1), Weight);
    } else {
      fMCHist_true->Fill(fXVar, Weight);
      fMCStat_true->Fill(fXVar, 1.0);
      //if (fMCHist_Modes)
	//fMCHist_Modes->Fill(Mode, fXVar, Weight);
    }

    //fMCFine->Fill(fXVar, Weight);
    //if (fMCFine_Modes)
    //  fMCFine_Modes->Fill(Mode, fXVar, Weight);
  }

  return;
}


void MicroBooNE_KDAR_nu::ApplySmearingMatrix() {

  if (!fSmearMatrix) {
    NUIS_ERR(WRN,
             fName << ": attempted to apply smearing matrix, but none was set");
    return;
  }

  TH1D *unsmeared = (TH1D *)fMCHist_true->Clone();
  TH1D *smeared = (TH1D *)fMCHist->Clone();
  TH1D *unsmeared_stat = (TH1D *)fMCStat_true->Clone();
  TH1D *smeared_stat = (TH1D *)fMCStat->Clone();
  smeared->Reset();
  smeared_stat->Reset();

  // Loop over reconstructed bins
  // true = row; reco = column
  for (int rbin = 0; rbin < fSmearMatrix->GetNcols(); ++rbin) {
    // Sum up the constributions from all true bins
    double rBinVal = 0;
    double rBinStat = 0;
    // Loop over true bins
    for (int tbin = 0; tbin < fSmearMatrix->GetNrows(); ++tbin) {
      rBinVal +=
          (*fSmearMatrix)(tbin, rbin) * unsmeared->GetBinContent(tbin + 1);
      rBinStat +=
          (*fSmearMatrix)(tbin, rbin) * unsmeared_stat->GetBinContent(tbin + 1);
    }
    smeared->SetBinContent(rbin + 1, rBinVal);
    smeared_stat->SetBinContent(rbin + 1, rBinStat);
  }
  fMCHist = (TH1D *)smeared->Clone();
  fMCStat = (TH1D *)smeared_stat->Clone();

  return;
}


void MicroBooNE_KDAR_nu::ConvertEventRates() {
  MicroBooNE_KDAR_nu::ApplySmearingMatrix();
  Measurement1D::ConvertEventRates();
}

