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
#ifndef MICROBOONE_KDAR_NU_H_SEEN
#define MICROBOONE_KDAR_NU_H_SEEN

#include "Measurement1D.h"

class MicroBooNE_KDAR_nu : public Measurement1D {

public:

  // Basic Constructor.
  MicroBooNE_KDAR_nu(nuiskey samplekey);

  // Virtual Destructor
  ~MicroBooNE_KDAR_nu() {};

  // Apply signal definition
  bool isSignal(FitEvent* nvect);

  // Fill kinematic variables
  void FillEventVariables(FitEvent* customEvent);

  // Fill the true histogram fMCHist_true, not the reco one saved in fMCHist
  void FillHistograms();

  // Map from fMCHist_true to fMCHist
  void ApplySmearingMatrix(); 

  // Make sure the smearing matrix is applied
  void ConvertEventRates();

private:

  TH1D* fMCHist_true; // Truth space equivalent of fMCHist, filled and then smeared to fMCHist 
  TH1D* fMCStat_true; // Truth space equivalent of fMCStat, filled and then smeared to fMCStat 

  int GetBinTrueKvis(double Kp, double Kmu);
  int GetBinTrueCosP(double Kp, double CosP);

  enum Distribution { kKmu, kKp, kCosMu, kCosP, kKvis, kMult, ksqrtQ2, kq };
  Distribution fDist;

};

#endif

