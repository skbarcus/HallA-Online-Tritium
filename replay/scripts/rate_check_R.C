//Check rate: xbj , Q2, and tg_y after cuts
//Shujie Li,Dec 2017
void rate_check_R(Int_t flag, TString drawoption=""){

  gStyle->SetOptStat(0);
  
  
  TTree *tree = (TTree*)gDirectory->Get("T");
 //Set the cut for data 
   const double dp_cut = 0.035;
  const double th_cut = 0.035;
  const double ph_cut = 0.02; 
  //const double y_cut = 10;//0.02;
  

  TCut track = "R.tr.n ==1";
  TCut trigger = "((DR.evtypebits>>4)&1)";
  TCut pid = Form("R.cer.asum_c>1000 && ((R.ps.e+R.sh.e)>800)");
  TCut acc = Form("abs(R.tr.tg_dp)<%f && abs(R.tr.tg_ph)<%f && abs(R.tr.tg_th)<%f", dp_cut,ph_cut, th_cut);
  TCut data_cut =  track + acc+ trigger+pid ;
  TCut y_cut = "abs(R.tr.tg_y)<0.2"; // +-7cm ztarget at 17 degree
  if(flag==1){
    
    TH1F *ht1 = new TH1F("ht1","xbj w/ acc and tgy cuts",1000,0,3);
    ht1->GetXaxis()->SetTitle("xbj");ht1->GetXaxis()->CenterTitle();
    ht1->GetYaxis()->SetTitle("good events counts");ht1->GetYaxis()->CenterTitle();
    
    
    tree->Draw("EKR.x_bj>>ht1",data_cut+y_cut,drawoption);
  }
 if(flag==2){
    
    TH1F *ht2 = new TH1F("ht2","Q2 w/ acc and tgy cuts",1000,0,3);
    ht2->GetXaxis()->SetTitle("Q2");ht2->GetXaxis()->CenterTitle();
    ht2->GetYaxis()->SetTitle("good events counts");ht2->GetYaxis()->CenterTitle();
    
    
    tree->Draw("EKR.Q2>>ht2",data_cut+y_cut,drawoption);
  }
 if(flag==3){
    
   TH1F *ht3 = new TH1F("ht3","ytar w/ acc cuts",1000,-0.1,0.1);
    ht3->GetXaxis()->SetTitle("y_target (m)");ht3->GetXaxis()->CenterTitle();
    ht3->GetYaxis()->SetTitle("good events counts");ht3->GetYaxis()->CenterTitle();
    
    
    tree->Draw("R.tr.tg_y>>ht3",data_cut,drawoption);
  }

  if(flag==4){
    
    TH2F *ht4 = new TH2F("ht4","Q2 v.s. xbj (w/ acc, tgy cuts)",1000,0,3,1000,0,3);
    ht4->GetXaxis()->SetTitle("Time [TDC Channel]");ht4->GetXaxis()->CenterTitle();
    ht4->GetYaxis()->SetTitle("Amplitude [ADC Channel]");ht4->GetYaxis()->CenterTitle();
    //ht3->SetMarkerStyle(3);ht3->SetMarkerSize(0.75);

    tree->Draw("EKR.Q2:EKR.x_bj>>ht4",data_cut+y_cut,drawoption);
    
  }
}
