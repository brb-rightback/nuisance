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

#include "MINERvA_SignalDef.h"

#include "MINERvA_CCinc_XSec_1Dx_nu.h"

//********************************************************************
MINERvA_CCinc_XSec_1Dx_nu::MINERvA_CCinc_XSec_1Dx_nu(std::string name, std::string inputfile, FitWeight *rw, std::string type,
						     std::string fakeDataFile){
//********************************************************************

  // Measurement Details
  fName = name;
  fPlotTitles = "; Reconstructed Bjorken x; d#sigma/dx (cm^{2}/nucleon)";
  EnuMin = 2.;
  EnuMax = 20.;
  target = "";
  Measurement1D::SetupMeasurement(inputfile, type, rw, fakeDataFile);

  if      (name.find("C12")   != std::string::npos) target =   "C12";
  else if (name.find("Fe56")  != std::string::npos) target =  "Fe56";
  else if (name.find("Pb208") != std::string::npos) target = "Pb208";
  if      (name.find("DEN")   != std::string::npos) target =   "CH";
  if (target == "") ERR(WRN) << "target " << target << " was not found!" << std::endl;

  // Setup the Data Plots
  std::string basedir = FitPar::GetDataBase()+"/MINERvA/CCinc/";
  std::string smearfilename  = "CCinc_"+target+"_x_smear.csv";
  int nbins = 6;
  double bins[7] = {0, 0.1, 0.3, 0.7, 0.9, 1.1, 1.5};

  // Note that only the ratio is given, so I can't do this->SetDataValues or this->SetCovarMatrix
  this->fDataHist = new TH1D(name.c_str(),(name+fPlotTitles).c_str(),nbins,bins);

  // Setup Default MC Histograms
  this->SetupDefaultHist();

  // The smearing matrix is rectangular
  this->SetSmearingMatrix(basedir + smearfilename, nbins, nbins+1);

  // Set Scale Factor (EventHist/nucleons) so I don't need to know what the target is here
  this->fScaleFactor = (GetEventHistogram()->Integral("width")*1E-38/(fNEvents+0.))/this->TotalIntegratedFlux(); // NEUT

};

//********************************************************************
void MINERvA_CCinc_XSec_1Dx_nu::FillEventVariables(FitEvent *event){
//********************************************************************

  if (event->NumFSParticle(13) == 0)
    return;

  TLorentzVector Pnu  = event->GetNeutrinoIn()->fP;
  TLorentzVector Pmu  = event->GetHMFSParticle(13)->fP;

  ThetaMu     = Pnu.Vect().Angle(Pmu.Vect());
  TLorentzVector q = Pnu - Pmu;
  double q0   = q.E()/1000.0;
  double Emu  = (Pmu.E())/1000.0;
  Enu_rec     = Emu + q0;
  double Q2   = 4*Enu_rec*Emu*sin(ThetaMu/2)*sin(ThetaMu/2);
  bjork_x     = Q2/2./q0/((PhysConst::mass_proton+PhysConst::mass_neutron)/2.); // Average nucleon masses

  fXVar   = bjork_x;
  return;
}



//********************************************************************
bool MINERvA_CCinc_XSec_1Dx_nu::isSignal(FitEvent *event){
//*******************************************************************

  // Only look at numu events
  if (!SignalDef::isCCINC(event, 14, EnuMin, EnuMax)) return false;

  // Restrict the phase space to theta < 17 degrees
  if (ThetaMu > 0.296706) return false;

  // restrict energy range
  if (Enu_rec < this->EnuMin || Enu_rec > this->EnuMax) return false;

  return true;
};

//********************************************************************
void MINERvA_CCinc_XSec_1Dx_nu::ScaleEvents(){
//********************************************************************

  this->fDataHist = (TH1D*)this->GetMCList().at(0)->Clone();
  this->fDataHist->SetNameTitle((this->fName+"_unsmear").c_str(), (this->fName+"_unsmear"+this->fPlotTitles).c_str());
  this->ApplySmearingMatrix();

  // Get rid of this because it causes odd behaviour
  //Measurement1D::ScaleEvents();

  this->fMCHist->Scale(this->fScaleFactor, "width");

  // Proper error scaling - ROOT Freaks out with xsec weights sometimes
  for(int i=0; i<this->fMCStat->GetNbinsX();i++) {

    if (this->fMCStat->GetBinContent(i+1) != 0)
      this->fMCHist->SetBinError(i+1, this->fMCHist->GetBinContent(i+1) * this->fMCStat->GetBinError(i+1) / this->fMCStat->GetBinContent(i+1) );
    else this->fMCHist->SetBinError(i+1, this->fMCHist->Integral());
  }

}
