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

#ifndef MEASUREMENT_2D_HXX_SEEN
#define MEASUREMENT_2D_HXX_SEEN

/*!
 *  \addtogroup FitBase
 *  @{
 */

#include <math.h>
#include <stdlib.h>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

// ROOT includes
#include <TArrayF.h>
#include <TDecompSVD.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TMatrixDSym.h>
#include <TROOT.h>
#include <TSystem.h>

// External data fit includes
#include "FitEvent.h"
#include "FitParameters.h"
#include "FitUtils.h"
#include "MeasurementBase.h"
#include "PlotUtils.h"
#include "SignalDef.h"
#include "StatUtils.h"

//********************************************************************
//! 2D Measurement base class. Histogram handling is done in this base layer.
class Measurement2D : public MeasurementBase {
  //********************************************************************

 public:
  /*
    Constructor/Deconstuctor
  */

  //! Default Constructor
  Measurement2D();

  //! Default Destructor
  virtual ~Measurement2D();

  /*
    Setup Functions
  */

  //! Intial setup of common measurement variables. Parse input files, types,
  //! etc.
  virtual void SetupMeasurement(std::string input, std::string type,
                                FitWeight* rw, std::string fkdt);

  //! Setup the default mc Hist given a data histogram
  virtual void SetupDefaultHist();

  //! Parse the fit type to get fit options
  virtual void SetFitOptions(std::string opt);

  //! Set the data values and errors from two files
  virtual void SetDataValues(std::string dataFile, double dataNorm,
                             std::string errorFile, double errorNorm);
  virtual void SetDataValues(std::string dataFile, std::string TH2Dname);

  //! Set the data values only from a text file
  virtual void SetDataValuesFromText(std::string dataFile, double norm);

  //! Read a covariance matrix from a file (Default name "covar" in file)
  virtual void SetCovarMatrix(std::string covarFile);

  //! Set the covariance matrix from a text file
  virtual void SetCovarMatrixFromText(std::string covarFile, int dim);

  //! Set the covariance matrix from a text file containing the cholesky
  //! fDecomposition
  virtual void SetCovarMatrixFromChol(std::string covarFile, int dim);

  // virtual void SetMaskValuesFromText(std::string dataFile);

  //! Read in a histogram 2Dto1D map from a text file
  virtual void SetMapValuesFromText(std::string dataFile);

  //! Set the bin mask for a 2D histogram (list: bini, binj, MaskFlag)
  virtual void SetBinMask(std::string maskFile);

  // virtual void ReadHistogramFile();

  /*
    XSec Functions
  */
  // // ! Set the flux from a text file
  // virtual void SetFluxHistogram(std::string fluxFile, int minE, int maxE,
  // double fluxNorm);

  // //! Get the integrated flux between this measurements energy ranges
  // virtual double TotalIntegratedFlux(std::string intOpt="width",double
  // low=-9999.9, double high=-9999.9);

  /*
    Reconfigure LOOP
  */

  //! Reset the MC Histograms to zero
  virtual void ResetAll();

  //! Fill the histograms given fXVar, fYVar, and Weight for this event
  virtual void FillHistograms();

  //! Apply event scaling to XSec values after reconfigure has been called
  virtual void ScaleEvents();

  //! Apply a normalisation scale in free normalisation fits after reconfigure
  //! has been called
  virtual void ApplyNormScale(double norm);

  /*
    Statistic Functions - Outsources to StatUtils
   */

  //! Get the Number of degrees of freedom accounting for bin masking
  virtual int GetNDOF();

  //! Get the likelihood at current state
  virtual double GetLikelihood();

  /*
    Fake Data Functions
  */

  //! Set fake data values from MC. Use external file, or current MC prediction
  //! using option "MC"
  virtual void SetFakeDataValues(std::string fakeOption);
  // virtual void ResetFakeData();
  // virtual void ResetData();

  //! Use the covariance to throw fake data from the current fDataHist
  virtual void ThrowCovariance();

  virtual THStack GetModeStack();

  /*
    Access Functions
  */

  TH2D* GetMCHistogram() { return fMCHist; };
  TH2D* GetDataHistogram() { return fDataHist; };

  virtual std::vector<TH1*> GetMCList();
  virtual std::vector<TH1*> GetDataList();
  virtual std::vector<TH1*> GetMaskList() {
    return std::vector<TH1*>(1, fMaskHist);
  };
  virtual std::vector<TH1*> GetFineList() {
    return std::vector<TH1*>(1, fMCFine);
  };

  //! Get bin contents and errors from fMCHist and fill a vector with them
  virtual void GetBinContents(std::vector<double>& cont,
                              std::vector<double>& err);

  //! Get covariance matrix as a pretty plot
  virtual TH2D GetCovarMatrix() { return TH2D(*covar); };

  //! Get Integrated XSec (option flags whether to get data or MC)
  virtual std::vector<double> GetXSec(std::string option);

  /*
    Write Functions
  */

  //! Save Histograms to the current directory
  virtual void Write(std::string drawOpt);

 protected:
  // The data histograms
  TH2D* fDataHist;    //!< default data histogram (use in chi2 calculations)
  TH2D* fDataOrig;    //!< histogram to store original data before throws.
  TH2D* fDataTrue;    //!< histogram to store true dataset
  TH1D* fDataHist_X;  //!< Projections onto X of the fDataHist
  TH1D* fDataHist_Y;  //!< Projections onto Y of the fDataHist

  // The MC histograms
  TH2D* fMCHist;          //!< MC Histogram (used in chi2 calculations)
  TH2D* fMCFine;          //!< Finely binned MC Histogram
  TH2D* fMCHist_PDG[61];  //!< MC Histograms for each interaction mode
  TH1D* fMCHist_X;        //!< Projections onto X of the fMCHist
  TH1D* fMCHist_Y;        //!< Projections onto Y of the fMCHist
  TH2D* fMCWeighted;      //!< Raw Event Weights

  TH2I* fMaskHist;  //!< mask histogram for the data
  TH2I* fMapHist;   //!< map histogram used to convert 2D to 1D distributions

  bool fIsFakeData;          //!< is current data actually fake
  std::string fakeDataFile;  //!< MC fake data input file

  std::string fPlotTitles;  //!< X and Y plot titles.
  std::string fFitType;
  std::string fDefaultTypes;  //!< Default Fit Options
  std::string fAllowedTypes;  //!< Any allowed Fit Options

  TMatrixDSym* covar;       //!< inverted covariance matrix
  TMatrixDSym* fFullCovar;  //!< covariance matrix
  TMatrixDSym* fDecomp;     //!< fDecomposed covariance matrix
  TMatrixDSym* fCorrel;     //!< correlation matrix
  double fCovDet;           //!< covariance deteriminant
  double fNormError;        //!< Normalisation on the error on the data

  Double_t* fXBins;     //!< X Bin Edges
  Double_t* fYBins;     //!< Y Bin Edges
  Int_t fNDataPointsX;  //!< Number of X data points
  Int_t fNDataPointsY;  //!< NUmber of Y data points

  // Fit specific flags
  bool fIsShape;      //!< Flag: Perform shape-only fit
  bool fIsFree;       //!< Flag: Perform normalisation free fit
  bool fIsDiag;       //!< Flag: Only use diagonal bin errors in stats
  bool fIsMask;       //!< Flag: Apply bin masking
  bool fIsRawEvents;  //!< Flag: Only event rates in histograms
  bool fIsEnu;        //!< Needs Enu Unfolding
  bool fIsChi2SVD;    //!< Flag: Chi2 SVD Method (DO NOT USE)
  bool fAddNormPen;   //!< Flag: Add normalisation penalty to fi
  bool fIsProjFitX;  //!< Flag: Use 1D projections onto X and Y to calculate the
                     //!Chi2 Method. If flagged X will be used to set the rate.
  bool fIsProjFitY;  //!< Flag: Use 1D projections onto X and Y to calculate the
                     //!Chi2 Method. If flagged Y will be used to set the rate.
  bool fIsFix;       //!< Flag: Fixed Histogram Norm
  bool fIsFull;      //!< Flag; Use Full Covar
  bool fIsDifXSec;   //!< Flag: Differential XSec
  bool fIsEnu1D;     //!< Flag: Flux Unfolded XSec
  bool fIsChi2;      //!< Flag; Use Chi2 over LL
};

/*! @} */
#endif
