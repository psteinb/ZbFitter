{
//========= Macro generated from object: fitResult/
//========= by ROOT version5.28/00b
   
   TH1D *fitResult = new TH1D("fitResult","",11,-5,5);
   fitResult->SetBinContent(1,nan);
   fitResult->SetBinContent(2,nan);
   fitResult->SetBinContent(3,nan);
   fitResult->SetBinContent(4,-354.411);
   fitResult->SetBinContent(5,-374.377);
   fitResult->SetBinContent(6,-380.683);
   fitResult->SetBinContent(7,-379.761);
   fitResult->SetBinContent(8,-374.227);
   fitResult->SetBinContent(9,-365.463);
   fitResult->SetBinContent(10,-354.299);
   fitResult->SetBinContent(12,-341.277);
   fitResult->SetEntries(11);
   fitResult->SetStats(0);
   fitResult->SetLineWidth(2);
   fitResult->SetMarkerStyle(20);
   fitResult->SetMarkerSize(1.2);
   fitResult->GetXaxis()->SetTitle("parameter");
   fitResult->GetXaxis()->SetLabelFont(42);
   fitResult->GetXaxis()->SetLabelSize(0.05);
   fitResult->GetXaxis()->SetTitleSize(0.05);
   fitResult->GetXaxis()->SetTitleOffset(1.4);
   fitResult->GetXaxis()->SetTitleFont(42);
   fitResult->GetYaxis()->SetTitle("log(L) / a.u.");
   fitResult->GetYaxis()->SetLabelFont(42);
   fitResult->GetYaxis()->SetLabelSize(0.05);
   fitResult->GetYaxis()->SetTitleSize(0.05);
   fitResult->GetYaxis()->SetTitleOffset(1.4);
   fitResult->GetYaxis()->SetTitleFont(42);
   fitResult->GetZaxis()->SetLabelFont(42);
   fitResult->GetZaxis()->SetLabelSize(0.05);
   fitResult->GetZaxis()->SetTitleSize(0.05);
   fitResult->GetZaxis()->SetTitleFont(42);
   fitResult->Draw("");
}
