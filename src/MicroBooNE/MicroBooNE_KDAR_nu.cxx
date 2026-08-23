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
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Kmu_nu_MCHist_true",";K_{#mu} (MeV)",24,0,120);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Kmu_nu_MCStat_true",";K_{#mu} (MeV)",24,0,120);
  }
  else if (!name.compare("MicroBooNE_KDAR_ThetaMu_nu")) {
    fDist = kThetaMu;
    objSuffix = "ThetaMu";
    fSettings.SetXTitle("#theta_{#mu}^{reco}");
    fSettings.SetYTitle("1/#sigma d#sigma/d#theta_{#mu}^{reco}");
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
  else if (!name.compare("MicroBooNE_KDAR_ThetaP_nu")) {
    fDist = kThetaP;
    objSuffix = "ThetaP";
    fSettings.SetXTitle("1/#sigma #theta_{p}^{reco}");
    fSettings.SetYTitle("d#sigma/d#theta_{p}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_ThetaP_nu_MCHist_true",";K_{p} and cos_{p} bin",288,-0.5,287.5);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_ThetaP_nu_MCStat_true",";K_{p} and cos_{p} bin",288,-0.5,287.5);
  }
  else if (!name.compare("MicroBooNE_KDAR_Mult_nu")) {
    fDist = kMult;
    objSuffix = "Mult";
    fSettings.SetXTitle("Reconstructed Multiplicity");
    fSettings.SetYTitle("1/#sigma d#sigma/dN_{p}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Mult_nu_MCHist_true",";K_{p} (MeV)",26,0,130);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Mult_nu_MCStat_true",";K_{p} (MeV)",26,0,130);
  }
  else if (!name.compare("MicroBooNE_KDAR_TrackKvis_nu")) {
    fDist = kTrackKvis;
    objSuffix = "trackKvis";
    fSettings.SetXTitle("Track-only K_{vis}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dK_{vis,track}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_TrackKvis_nu_MCHist_true",";K_{p} and K_{#mu} bin",160,-0.5,159.5);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_TrackKvis_nu_MCStat_true",";K_{p} and K_{#mu} bin",160,-0.5,159.5);
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
  else if (!name.compare("MicroBooNE_KDAR_Kvis_nu")) {
    fDist = kKvis;
    objSuffix = "Kvis";
    fSettings.SetXTitle("K_{vis}^{reco} (MeV)");
    fSettings.SetYTitle("1/#sigma d#sigma/dK_{vis}^{reco}");
    fMCHist_true = new TH1D("MicroBooNE_KDAR_Kvis_nu_MCHist_true",";P. mult., K_{p} and K_{#mu} bin",1610,-0.5,1609.5);
    fMCStat_true = new TH1D("MicroBooNE_KDAR_Kvis_nu_MCStat_true",";P. mult., K_{p} and K_{#mu} bin",1610,-0.5,15609.5);
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
  fSettings.SetAllowedTypes("FULL,DIAG");
  fSettings.SetEnuRange(0.234, 0.237);
  fSettings.DefineAllowedTargets("Ar");
  fSettings.DefineAllowedSpecies("numu");
  FinaliseSampleSettings();

  // Load data ---------------------------------------------------------
  std::string inputFile = FitPar::GetDataBase() + "/MicroBooNE/KDAR/KDAR_dataRelease.root";
  SetDataFromRootFile(inputFile, "Data_" + objSuffix);

  // Unity since this is shape only
  fScaleFactor = 1; 

  SetCovarFromRootFile(inputFile, "Cov_" + objSuffix);
  (*fFullCovar) *= 1E76;
  covar = StatUtils::GetInvert(fFullCovar, true);
  fDecomp = StatUtils::GetDecomp(fFullCovar);

  TFile* inputRootFile = TFile::Open(inputFile.c_str());
  assert(inputRootFile && inputRootFile->IsOpen());
  fSmearingMatrix = (TH2D*) inputRootFile->Get(("R_" + objSuffix).c_str());
  fSmearingMatrix->SetDirectory(0);
  inputRootFile->Close();
  assert(fSmearingMatrix);

  // set the errors to the ones from covariance matrix to suppresses warnings
  for(int i = 0; i < fDataHist->GetNbinsX(); i++)
    fDataHist->SetBinError(i+1, sqrt((*fFullCovar)(i, i))*1E-38);

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
  double ThetaMu = event->GetHMFSParticle(13)->fP.Vect().Theta();
  double CosMu = event->GetHMFSParticle(13)->fP.Vect().CosTheta();
  double SinMu = TMath::Sin(ThetaMu);
  double pMu = event->GetHMFSParticle(13)->p();
  double pl = pMu*CosMu;
  double pt = pMu*SinMu; 
  double Kp = 0.00000001;
  double ThetaP = 0;
  double Pmult = event->NumFSParticle(2212);
  if (Pmult != 0){ 
    Kp = event->GetHMFSParticle(2212)->KE();
    ThetaP = event->GetHMFSParticle(2212)->fP.Vect().Theta();
  }
  double sprtQ2 = sqrt(event->GetQ2())*1000; // GeV->MeV
  double nu = event->Enu() - event->GetHMFSParticle(13)->E();
  double q = sqrt(sprtQ2*sprtQ2 + nu*nu);

  if (fDist == kKmu) {
    fXVar = Kmu; 
  }
  else if (fDist == kThetaMu) {
    fXVar = ThetaMu; 
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
  else if (fDist == kThetaP) {
    fXVar = GetBinTrueThetaP(Kp,ThetaP);
  }
  else if (fDist == kTrackKvis) {
    fXVar = GetBinTrueTrackKvis(Kp,Kmu);
  }
  else if (fDist == ksqrtQ2) {
    fXVar = sprtQ2;
  }
  else if (fDist == kq) {
    fXVar = q;
  }
  else if (fDist == kKvis) {
    fXVar = GetBinTrueKvis(Pmult,Kp,Kmu);
  }

  if(fDist != kKvis && fDist != kThetaP){ 
    double maxXVar = fMCHist_true->GetXaxis()->GetBinUpEdge(fMCHist_true->GetNbinsX());
    if (fXVar>maxXVar) fXVar=maxXVar-0.0001;
  }

}


int MicroBooNE_KDAR_nu::GetBinTrueThetaP(double Kp, double ThetaP){

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
    if(ThetaP<bin*bin_width+bin_width+min && ThetaP>=bin*bin_width+min){
      found_bin = bin;
      break;
    }
  }

  if(found_slice<0 || found_bin<0){
    NUIS_ERR(WRN,fName << ": WARNING, could not find {Kp,ThetaP} bin.");
    return -1;
  }
 
  return found_slice*nbins+found_bin;

};

int MicroBooNE_KDAR_nu::GetBinTrueKvis(double Pmult, double Kp, double Kmu){

  int found_Pmult = -1;
  int found_slice = -1;
  int found_bin = -1;
  int Pmult_width=1;
  int Pmult_min = 0;
  int Pmult_max = 4;
  int Pmult_nbins = int( (Pmult_max-Pmult_min)/Pmult_width);
  int slice_width=5;
  int slice_min = 0;
  int slice_max = 115;
  int slice_nbins = int( (slice_max-slice_min)/slice_width);
  int bin_width=5;
  int min = 0;
  int max = 115;
  int nbins = int( (max-min)/bin_width);

  // Check the multiplicity
  // First check overflow
  if(Pmult>=Pmult_max){
    found_Pmult = Pmult_nbins-1;
  }
  else{
    // Then check all the bins
    for(int Pmult_bin=0; Pmult_bin<Pmult_nbins; Pmult_bin++){
      if(Pmult<Pmult_bin*Pmult_width+Pmult_width+Pmult_min && Pmult>=Pmult_bin*Pmult_width+Pmult_min){
        found_Pmult = Pmult_bin;
        break;
      }
    }
  }

  // Check all slices if we have a proton
  // Do we have a proton?
  if (found_Pmult==0){
    found_slice = 0;
  }
  // Then check overflow
  else if(Kp>=slice_max){
    found_slice = slice_nbins-1;
  }
  // Now check all 
  else{
    for(int slice_bin=0; slice_bin<slice_nbins; slice_bin++){
      if(Kp<slice_bin*slice_width+slice_width+slice_min && Kp>=slice_bin*slice_width+slice_min){
        found_slice = slice_bin;
        break;
      }
    }
  }

  // First check overflow
  if(Kmu>=max){
    found_bin = nbins-1;
  }
  else{
    // Check all the bins
    for(int bin=0; bin<nbins; bin++){
      if(Kmu<bin*bin_width+bin_width+min && Kmu>=bin*bin_width+min){
        found_bin = bin;
        break;
      }
    }
  }


  if(found_Pmult<0 || found_slice<0 || found_bin<0){
    NUIS_ERR(WRN,fName << ": WARNING, could not find {Pmult,Kp,Kmu} bin.");
    return -1;
  }

  int bin = found_bin;
  if (found_Pmult>0){
    bin = nbins + (found_Pmult-1)*(slice_nbins*nbins) + (found_slice*nbins + found_bin);
  }
  return bin;


}

int MicroBooNE_KDAR_nu::GetBinTrueTrackKvis(double Kp, double Kmu){

  int found_slice = -1;
  int found_bin = -1;
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
    if(Kmu>max){
      found_bin = nbins-1;
      break;
    }
    if(Kmu<bin*bin_width+bin_width+min && Kmu>=bin*bin_width+min){
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

  if (!fSmearingMatrix) {
    NUIS_ERR(WRN,fName << ": attempted to apply smearing matrix, but none was set");
    return;
  }

  TH1D *unsmeared = (TH1D *)fMCHist_true->Clone();
  TH1D *smeared = (TH1D *)fMCHist->Clone();
  TH1D *unsmeared_stat = (TH1D *)fMCStat_true->Clone();
  TH1D *smeared_stat = (TH1D *)fMCStat->Clone();
  smeared->Reset();
  smeared_stat->Reset();

  // true = y; reco = x
  int n_rbins=fSmearingMatrix->GetNbinsX();
  int n_tbins=fSmearingMatrix->GetNbinsY();

  // Loop over reconstructed bins
  for (int rbin = 0; rbin < n_rbins; ++rbin) {
    // Sum up the constributions from all true bins
    double rBinVal = 0;
    double rBinStat = 0;
    // Loop over true bins
    for (int tbin = 0; tbin < n_tbins; ++tbin) {
      rBinVal +=
          fSmearingMatrix->GetBinContent(rbin+1, tbin+1) * unsmeared->GetBinContent(tbin+1);
      rBinStat +=
          fSmearingMatrix->GetBinContent(rbin+1, tbin+1) * unsmeared_stat->GetBinContent(tbin+1);
    }
    smeared->SetBinContent(rbin+1, rBinVal);
    smeared_stat->SetBinContent(rbin+1, rBinStat);
  }
  fMCHist = (TH1D *)smeared->Clone();
  fMCStat = (TH1D *)smeared_stat->Clone();

/*
  // Now normalize to unity
  double norm_factor=1;
  for (int rbin = 0; rbin < n_rbins; ++rbin) {
    norm_factor+=fMCHist->GetBinContent(rbin+1);
  }
  fMCHist->Scale(1/norm_factor);
  fMCStat->Scale(1/norm_factor);
*/

  return;

}


void MicroBooNE_KDAR_nu::ConvertEventRates() {

  MicroBooNE_KDAR_nu::ApplySmearingMatrix();
  Measurement1D::ConvertEventRates();

  int n_rbins=fMCHist->GetNbinsX();
  // Now normalize to unity
  double norm_factor=1;
  for (int rbin = 0; rbin < n_rbins; ++rbin) {
    norm_factor+=fMCHist->GetBinContent(rbin+1);
  }
  fMCHist->Scale(1/norm_factor);
  fMCStat->Scale(1/norm_factor);

  return;

}

