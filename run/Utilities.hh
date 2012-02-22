#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include "TString.h"
#include "TRegexp.h"
#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TRandom3.h"
#include "TMath.h"
#include "TArrow.h"
#include "TPad.h"
#include "TPaveStats.h"
#include "TSystem.h"
#include "TF1.h"
#include "TStyle.h"

// #include "AtlasStyle.h"
#include "TF1.h"


void printAll(const std::vector<std::vector<TH1*> >& _results,const std::vector<double>& _expected,const std::vector<double>& _expectedErrors, TStyle* _aStyle, const std::string& _file=""){


  TCanvas myResults(_file.c_str(),"",3000,2000);
  myResults.Clear();
  myResults.Draw();
  myResults.Divide(3,_results.size());
  int padSize = 3*_results.size();
  TLine anLine;
  anLine.SetLineColor(kBlue);
  anLine.SetLineWidth(2);
  int currentPad=0;
  int padStart=1;
  std::ostringstream expValueString;
  TPaveText expValue;
  expValue.SetTextColor(kBlue);
  expValue.SetBorderSize(0.1);
  expValue.SetFillColor(kWhite);

  TVirtualPad* currentPadPtr = 0;
  double ArrowXNDC = 0.;
  for (int i = 0; i < _results.size(); ++i,padStart+=3)
  {
    expValueString.str("");
    expValueString <</* "expected:\t"<<*/ (_expected[i]) << " #pm " << (_expectedErrors[i]);
    for (int pad = 0; pad < 3; ++pad)
    {
      currentPad= pad + padStart;
      currentPadPtr = myResults.cd(currentPad);
      expValue.Clear();
      _results[i][pad]->SetMaximum(1.4*_results[i][pad]->GetMaximum());
      _results[i][pad]->Draw("");
      if(pad<1){
        myResults.Update();
        ArrowXNDC = (gPad->XtoPad(_expected[i]) - gPad->GetUxmin())/(gPad->GetUxmax() - gPad->GetUxmin());
        if(ArrowXNDC<.5)
          expValue.SetX1NDC(.5);
        else
          expValue.SetX1NDC(.17);

        expValue.SetY1NDC(1-_aStyle->GetStatH()-.17);
        expValue.SetX2NDC(expValue.GetX1NDC()+.33);
        expValue.SetY2NDC(expValue.GetY1NDC()+.1);


        expValue.AddText(expValueString.str().c_str());
        expValue.DrawClone();
        
        anLine.DrawLine(gPad->XtoPad(_expected[i]),gPad->GetUymin(),
                        gPad->XtoPad(_expected[i]),gPad->GetUymax()/*,0.03,"<|"*/);
      }
    }
  }
  myResults.Update();
  myResults.Print(".eps");


}

void printMeans(const std::vector<std::vector<TH1*> >& _results, const std::vector<double>& _expected,const std::string& _file="", ConfPseudoExperiment* _conf=0){

  TCanvas MeanCanvas(_file.c_str(),"",3000,1000);
  MeanCanvas.Clear();
  MeanCanvas.Draw();
  int width = _results.size();
  TString templateNames = _conf->p_tempTitle.c_str();
  templateNames.ToLower();

  if(templateNames.Contains("background"))
    width-=1;

  if(templateNames.Contains("ttbar") || templateNames.Contains("top"))
    width-=1;

  if(templateNames.Contains("qcd"))
    width-=1;
  
  MeanCanvas.Divide(width,1);
  int pad=1;
  double ArrowXNDC = 0.;
  TLine anLine;
  anLine.SetLineColor(kBlue);
  anLine.SetLineWidth(2);
  TString title = "";
  for (int i = 0; i < _results.size(); ++i,pad++)
  {
    title = _results[i][0]->GetXaxis()->GetTitle();
    title.ToLower();
    if(title.Contains("ttbar") || title.Contains("top") 
       || title.Contains("qcd") || title.Contains("background")){
      continue;}

    MeanCanvas.cd(pad);

    _results[i][0]->SetTitleSize(_results[i][0]->GetTitleSize()*1.5);
    _results[i][0]->SetTitleOffset(_results[i][0]->GetTitleOffset()*.75);
    _results[i][0]->SetYTitle(TString::Format("N_{events} / %.1f",_results[i][0]->GetXaxis()->GetBinWidth(2) ));

    _results[i][0]->Draw();
    MeanCanvas.Update();
    ArrowXNDC = (gPad->XtoPad(_expected[i]) - gPad->GetUxmin())/(gPad->GetUxmax() - gPad->GetUxmin());
    anLine.DrawLine(gPad->XtoPad(_expected[i]),gPad->GetUymin(),
                    gPad->XtoPad(_expected[i]),gPad->GetUymax()/*,0.03,"<|"*/);
    // }

  }
  MeanCanvas.Update();
  MeanCanvas.Print(".eps");
  MeanCanvas.SaveAs(TString::Format("%s.C",MeanCanvas.GetName()));
}

void printBias(const std::vector<std::vector<TH1*> >& _results, 
               const std::string& _file="", 
               ConfPseudoExperiment* _conf=0){

  TCanvas BiasCanvas(_file.c_str(),"",3000,1000);
  BiasCanvas.Clear();
  BiasCanvas.Draw();
  int width = _results.size();
  TString templateNames = _conf->p_tempTitle.c_str();
  templateNames.ToLower();

  if(templateNames.Contains("background"))
    width-=1;

  if(templateNames.Contains("ttbar") || templateNames.Contains("top"))
    width-=1;

  if(templateNames.Contains("qcd"))
    width-=1;
  
  BiasCanvas.Divide(width,1);
  int pad=1;
  double ArrowXNDC = 0.;
  TLine anLine;
  anLine.SetLineColor(kBlue);
  anLine.SetLineWidth(2);
  TString title = "";
  for (int i = 0; i < _results.size(); ++i,pad++)
  {
    title = _results[i][3]->GetXaxis()->GetTitle();
    title.ToLower();
    if(title.Contains("ttbar") || title.Contains("top") 
       || title.Contains("qcd") || title.Contains("background")){
      continue;}

    BiasCanvas.cd(pad);

    _results[i][3]->SetTitleSize(_results[i][3]->GetTitleSize()*1.5);
    _results[i][3]->SetTitleOffset(_results[i][3]->GetTitleOffset()*.75);
    _results[i][3]->SetYTitle(TString::Format("N_{events} / %.1f",_results[i][3]->GetXaxis()->GetBinWidth(2) ));

    _results[i][3]->Draw();
    BiasCanvas.Update();

  }
  BiasCanvas.Update();
  BiasCanvas.Print(".eps");
  BiasCanvas.SaveAs(TString::Format("%s.C",BiasCanvas.GetName()));
}

void printPulls(const std::vector<std::vector<TH1*> >& _results, const std::string& _file="", ConfPseudoExperiment* _conf=0){

  TCanvas PullCanvas(_file.c_str(),"",3000,1500);
  PullCanvas.Clear();
  PullCanvas.Draw();

  int width = _results.size();
  TString templateNames = _conf->p_tempTitle.c_str();
  templateNames.ToLower();

  if(templateNames.Contains("ttbar") || templateNames.Contains("top") || templateNames.Contains("background",TString::kIgnoreCase) || templateNames.Contains("qcd"))
    width-=1;

  PullCanvas.Divide(width,1);
  int pad=1;
  TF1* gaus = new TF1("MyGaus","gaus(0)",_results[0][2]->GetXaxis()->GetXmin(),_results[0][2]->GetXaxis()->GetXmax());
  gaus->SetParameter(0,_results[0][2]->GetEntries());
  gaus->SetParameter(1,0.);
  gaus->SetParameter(2,1.);
  TPaveText fitValues;
  fitValues.SetTextColor(kBlue);
  fitValues.SetBorderSize(0.1);
  fitValues.SetFillColor(kWhite);
  std::ostringstream stream;
  TString title = "";
  for (int i = 0; i < _results.size(); ++i,pad++)
  {
    stream.str("");
    fitValues.Clear();
    title = _results[i][2]->GetXaxis()->GetTitle();
    title.ToLower();
    if(title.Contains("ttbar") || title.Contains("top") || 
       title.Contains("qcd") || title.Contains("background"))
      continue;
    PullCanvas.cd(pad);

    TF1 gaus(TString::Format("Gaus_pull%i",i),"gaus(0)",_results[i][2]->GetXaxis()->GetXmin(),_results[i][2]->GetXaxis()->GetXmax());
    gaus.SetParameter(0,_results[i][2]->GetEntries());
    gaus.SetParameter(1,0.);
    gaus.SetParameter(2,1.);

    gPad->SetLogy();
    gPad->SetTopMargin(.2);
    _results[i][2]->SetStats(false);
    _results[i][2]->SetTitleSize(_results[i][2]->GetTitleSize()*1.5);
    _results[i][2]->SetTitleOffset(_results[i][2]->GetTitleOffset()*.75);
    _results[i][2]->SetYTitle(TString::Format("N_{events} / %.1f",_results[i][2]->GetXaxis()->GetBinWidth(2) ));
    _results[i][2]->Draw("e0");
    if(_results[i][2]->GetEntries()>0){
      _results[i][2]->Fit(&gaus,"VR+");
      stream << "#mu :  " << TString::Format("%.3f",gaus.GetParameter(1)) << " #pm " 
             << TString::Format("%.3f",gaus.GetParError(1)) 
             << ";  #sigma :  " << TString::Format("%.3f",gaus.GetParameter(2)) << " #pm "  
             << TString::Format("%.3f",gaus.GetParError(2));
      
      fitValues.AddText(stream.str().c_str());

      stream.str("");
      stream << "chi2/NDF :  " << gaus.GetChisquare() << " / " << gaus.GetNDF();
      fitValues.AddText(stream.str().c_str());
      stream.str("");
      stream << "Prob(chi2) :  " << TString::Format("%.3f",TMath::Prob(gaus.GetChisquare(),gaus.GetNDF()));
      fitValues.AddText(stream.str().c_str());
      fitValues.SetX1NDC(.15);
      fitValues.SetX2NDC(.85);
      fitValues.SetY1NDC(.82);
      fitValues.SetY2NDC(.98);
      fitValues.DrawClone();
      _results[i][2]->SetDrawOption("e0");
    }
    PullCanvas.Update();
  }
  PullCanvas.Update();
  PullCanvas.Print(".eps");
  PullCanvas.SaveAs(TString::Format("%s.C",PullCanvas.GetName()));

}

void printCorrelations(const std::vector<std::vector<TH2*> >& _results, const std::string& _file=""){

  int ysize = 0;
  int xsize = 0;
  if(_results.size() && _results[0].size()){
    xsize = _results.size();
    ysize = _results[0].size();

    TString rfileName = _file.c_str();
    rfileName += ".root";
    TFile correlationRFile(rfileName.Data(),"RECREATE");
    TCanvas PseudoCorrelation(_file.c_str(),"",xsize*800,ysize*600);

    PseudoCorrelation.Clear();
    PseudoCorrelation.Draw();
    PseudoCorrelation.Divide(xsize,ysize);
    
    int padId = 0;
    std::ostringstream correlationText;
    for (int col = 0; col < _results.size(); ++col)
    {
      for (int row = 0; row < _results[0].size(); ++row)
      {
        padId = (_results.size()*row)+1+col;
        PseudoCorrelation.cd(padId);
        _results[col][row]->SetStats(false);
        _results[col][row]->Draw("colz");
        _results[col][row]->SetDirectory(correlationRFile.GetDirectory("/"));

        correlationText.str("");
        correlationText<< "correlation: " << _results[col][row]->GetCorrelationFactor();
        TPaveText aPave;
        aPave.SetFillColor(kWhite);
        aPave.SetBorderSize(0.1);
        aPave.AddText(correlationText.str().c_str());
        aPave.SetX1NDC(.1);
        aPave.SetX2NDC(.9);
        aPave.SetY1NDC(.85);
        aPave.SetY2NDC(1.);
        
        aPave.DrawClone();
        PseudoCorrelation.Update();
      }
    }
    
    PseudoCorrelation.Print(".eps");
    correlationRFile.Write();

    ///////////////////////////////////////////////////////////////////////
    //stupid root, Close calls delete of all contained objects!
    for (int col = 0; col < _results.size(); ++col)
    {
      for (int row = 0; row < _results[0].size(); ++row)
      {
        _results[col][row]->SetDirectory(0);
      }
    }

    correlationRFile.Close();
    
  }


}

void printMaxLLH(TH1* _maxLLH, const std::string& _file=""){

 TCanvas PseudoMaxLLH(_file.c_str(),"",800,600);
  PseudoMaxLLH.Clear();
  PseudoMaxLLH.Draw();
  PseudoMaxLLH.cd(0);
  Double_t lowBound = _maxLLH->GetXaxis()->GetXmin();
  Double_t upBound = _maxLLH->GetXaxis()->GetXmax();
  Double_t lowMeanMinusSigma = _maxLLH->GetMean()-(4*_maxLLH->GetRMS());
  Double_t upMeanPlusSigma = _maxLLH->GetMean()+(4*_maxLLH->GetRMS());

  _maxLLH->GetXaxis()->SetRangeUser((lowMeanMinusSigma>lowBound) ? lowMeanMinusSigma : lowBound,
                                    (upMeanPlusSigma<upBound) ? upMeanPlusSigma : upBound);
  _maxLLH->SetXTitle("-1 log(#it{L})|_{max}");
  _maxLLH->SetYTitle(TString::Format("N_{events} / %.1f",_maxLLH->GetXaxis()->GetBinWidth(2)));
  _maxLLH->Draw();
  PseudoMaxLLH.Update();
  PseudoMaxLLH.Print(".eps");
  PseudoMaxLLH.SaveAs(TString::Format("%s.C",PseudoMaxLLH.GetName()));

}


#endif /* _UTILITIES_H_ */
