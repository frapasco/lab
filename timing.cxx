#include "timing.h"


//--------------------------------------------------------------
//TAC calibration-----------------------------------------------
//--------------------------------------------------------------
void TACcalibration(){
  const char* Data1=TACcal[1];
  const char* Data2=TACcal[2];
  const char* Data3=TACcal[3];
  const char* Data4=TACcal[4];
  const char* Data5=TACcal[5];
  const char* Data6=TACcal[6];
  const char* Data7=TACcal[7];
  //  const char *Data8=TACcal[0]; //rejecting the 2ns data
  const int numBins=10000;
  const int minX=0;
  const int maxX=100000;
    
  int n;
  cout<<"Se vuoi solo osservare lo spettro digita 1, se vuoi calibrare digita 2"<<endl;
  cin>>n;
  
  slimport_data_t data1;
  TFile *infile1 = new TFile (Data1);
  TTree *intree1 = (TTree*)infile1->Get("acq_tree_0");
  TBranch *inbranch1 = intree1->GetBranch("acq_ch2");
  inbranch1->SetAddress(&data1.timetag);
  
  slimport_data_t data2;
  TFile *infile2 = new TFile (Data2);
  TTree *intree2 = (TTree*)infile2->Get("acq_tree_0");
  TBranch *inbranch2 = intree2->GetBranch("acq_ch2");
  inbranch2->SetAddress(&data2.timetag);
  
  slimport_data_t data3;
  TFile *infile3 = new TFile (Data3);
  TTree *intree3 = (TTree*)infile3->Get("acq_tree_0");
  TBranch *inbranch3 = intree3->GetBranch("acq_ch2");
  inbranch3->SetAddress(&data3.timetag);
  
  slimport_data_t data4;
  TFile *infile4 = new TFile (Data4);
  TTree *intree4 = (TTree*)infile4->Get("acq_tree_0");
  TBranch *inbranch4 = intree4->GetBranch("acq_ch2");
  inbranch4->SetAddress(&data4.timetag);
  
  slimport_data_t data5;
  TFile *infile5 = new TFile (Data5);
  TTree *intree5 = (TTree*)infile5->Get("acq_tree_0");
  TBranch *inbranch5 = intree5->GetBranch("acq_ch2");
  inbranch5->SetAddress(&data5.timetag);
  
  slimport_data_t data6;
  TFile *infile6 = new TFile (Data6);
  TTree *intree6 = (TTree*)infile6->Get("acq_tree_0");
  TBranch *inbranch6 = intree6->GetBranch("acq_ch2");
  inbranch6->SetAddress(&data6.timetag);
  
  slimport_data_t data7;
  TFile *infile7 = new TFile (Data7);
  TTree *intree7 = (TTree*)infile7->Get("acq_tree_0");
  TBranch *inbranch7 = intree7->GetBranch("acq_ch2");
  inbranch7->SetAddress(&data7.timetag);
  /*
    slimport_data_t data8;
    TFile *infile8 = new TFile (Data8);
    TTree *intree8 = (TTree*)infile8->Get("acq_tree_0");
    TBranch *inbranch8 = intree8->GetBranch("acq_ch2");
    inbranch8->SetAddress(&data8.timetag); 
  */
  
  TH1F *h = new TH1F("","", numBins,minX,maxX);
	
  if(n==1){
	
    for(int i=0; i<inbranch1->GetEntries();i++){
      inbranch1->GetEntry(i);
      h->Fill(data1.qlong);
    }
    
    for(int i=0; i<inbranch2->GetEntries();i++){
      inbranch2->GetEntry(i);
      h->Fill(data2.qlong);
    }
    
    for(int i=0; i<inbranch3->GetEntries();i++){
      inbranch3->GetEntry(i);
      h->Fill(data3.qlong);
    }
    
    for(int i=0; i<inbranch4->GetEntries();i++){
      inbranch4->GetEntry(i);
      h->Fill(data4.qlong);
    }
    
    for(int i=0; i<inbranch5->GetEntries();i++){
      inbranch5->GetEntry(i);
      h->Fill(data5.qlong);
    }
        	
    for(int i=0; i<inbranch6->GetEntries();i++){
      inbranch6->GetEntry(i);
      h->Fill(data6.qlong);
    }
    
    for(int i=0; i<inbranch7->GetEntries();i++){
      inbranch7->GetEntry(i);
      h->Fill(data7.qlong);
    }
    /*
      for(int i=0; i<inbranch8->GetEntries();i++){
      inbranch8->GetEntry(i);
      h->Fill(data8.qlong);
      }  
    */
	
    h->Draw();
  }
  
  if(n==2){
    int peaks=7;
		
    /*
      double max[peaks] , min [peaks];
      cout<<"Inserisci i range in cui sono contenuti i picchi (min;max) in ordine crescente"<<endl;
      for(int i=0;i<peaks;i++){
      cin>>min[i]>>max[i]; }
    */
    double max=25000;
    double min=800;
		
    TH1F *h2[peaks];
    for(int i=0;i<peaks;i++){
      h2[i] = new TH1F("","", numBins,minX,maxX); }
    
    
    unsigned short dat;
    
    
    for(int i=0; i<inbranch1->GetEntries();i++){
      inbranch1->GetEntry(i);
      dat=data1.qlong;
      h->Fill(data1.qlong);
      if(dat>min && dat<max){
	h2[0]->Fill(data1.qlong);
      }	
    }
    
    
    for(int i=0; i<inbranch2->GetEntries();i++){
      inbranch2->GetEntry(i);
      dat=data2.qlong;
      h->Fill(data2.qlong);
      if(dat>min && dat<max){
	h2[1]->Fill(data2.qlong);
      }	
    }
    
    
    for(int i=0; i<inbranch3->GetEntries();i++){
      inbranch3->GetEntry(i);
      dat=data3.qlong;
      h->Fill(data3.qlong);
      if(dat>min && dat<max){
	h2[2]->Fill(data3.qlong);
      }	
    }
    
    for(int i=0; i<inbranch4->GetEntries();i++){
      inbranch4->GetEntry(i);
      dat=data4.qlong;
      h->Fill(data4.qlong);
      if(dat>min && dat<max){
	h2[3]->Fill(data4.qlong);
      }	
    }
    
    
    for(int i=0; i<inbranch5->GetEntries();i++){
      inbranch5->GetEntry(i);
      dat=data5.qlong;
      h->Fill(data5.qlong);
      if(dat>min && dat<max){
	h2[4]->Fill(data5.qlong);
      }	
    }
    
    
    for(int i=0; i<inbranch6->GetEntries();i++){
      inbranch6->GetEntry(i);
      dat=data6.qlong;
      h->Fill(data6.qlong);
      if(dat>min && dat<max){
	h2[5]->Fill(data6.qlong);
      }	
    }
    
    
    for(int i=0; i<inbranch7->GetEntries();i++){
      inbranch7->GetEntry(i);
      dat=data7.qlong;
      h->Fill(data7.qlong);
      if(dat>min && dat<max){
	h2[6]->Fill(data7.qlong);
      }	
    }        
    
    /*
      for(int i=0; i<inbranch8->GetEntries();i++){
      inbranch8->GetEntry(i);
      dat=data8.qlong;
      h->Fill(data8.qlong);
      if(dat>min && dat<max){
      h2[7]->Fill(data8.qlong);  
      }
      }	
    */
        	 
        	 
    double Max[peaks];
    for(int i=0;i<peaks;i++){
      Max[i]=h2[i]->GetMaximumBin();
    }
        
    TGraph *gr  = new TGraph(peaks,delay,Max);
    TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,600,400);
    gr->SetTitle("TAC calibration");
    gr->GetXaxis()->SetTitle("Delay [ns]");
    gr->GetYaxis()->SetTitle("[Channels]");
    gr->Draw("AP*");
    TF1* fitfunc=new TF1("fitfunc","pol1",0,30);
    gr->Fit("fitfunc");
    constTAC=fitfunc->GetParameter(1);
  }
}


//--------------------------------------------------------------
//LEMO length calibration---------------------------------------
//--------------------------------------------------------------
void lengthCali(){
  const char* Data1=TACcal[7]; //30ns di delay base
  const char* Data2=LEMOcal[0];
  const char* Data3=LEMOcal[1];
  const char* Data4=LEMOcal[2];
  const char* Data5=LEMOcal[3];
  const int numBins=10000;
  const int minX=0;
  const int maxX=100000;
    
  int n;
  cout<<"Se vuoi solo osservare lo spettro digita 1, se vuoi calibrare digita 2"<<endl;
  cin>>n;
  
  slimport_data_t data1;
  TFile *infile1 = new TFile (Data1);
  TTree *intree1 = (TTree*)infile1->Get("acq_tree_0");
  TBranch *inbranch1 = intree1->GetBranch("acq_ch2");
  inbranch1->SetAddress(&data1.timetag);
  
  slimport_data_t data2;
  TFile *infile2 = new TFile (Data2);
  TTree *intree2 = (TTree*)infile2->Get("acq_tree_0");
  TBranch *inbranch2 = intree2->GetBranch("acq_ch2");
  inbranch2->SetAddress(&data2.timetag);
  
  slimport_data_t data3;
  TFile *infile3 = new TFile (Data3);
  TTree *intree3 = (TTree*)infile3->Get("acq_tree_0");
  TBranch *inbranch3 = intree3->GetBranch("acq_ch2");
  inbranch3->SetAddress(&data3.timetag);
  
  slimport_data_t data4;
  TFile *infile4 = new TFile (Data4);
  TTree *intree4 = (TTree*)infile4->Get("acq_tree_0");
  TBranch *inbranch4 = intree4->GetBranch("acq_ch2");
  inbranch4->SetAddress(&data4.timetag);
  
  slimport_data_t data5;
  TFile *infile5 = new TFile (Data5);
  TTree *intree5 = (TTree*)infile5->Get("acq_tree_0");
  TBranch *inbranch5 = intree5->GetBranch("acq_ch2");
  inbranch5->SetAddress(&data5.timetag);
  
  TH1F *h = new TH1F("","", numBins,minX,maxX);
	
  if(n==1){
	
    for(int i=0; i<inbranch1->GetEntries();i++){
      inbranch1->GetEntry(i);
      h->Fill(data1.qlong);
    }
    
    for(int i=0; i<inbranch2->GetEntries();i++){
      inbranch2->GetEntry(i);
      h->Fill(data2.qlong);
    }
    
    for(int i=0; i<inbranch3->GetEntries();i++){
      inbranch3->GetEntry(i);
      h->Fill(data3.qlong);
    }
    
    for(int i=0; i<inbranch4->GetEntries();i++){
      inbranch4->GetEntry(i);
      h->Fill(data4.qlong);
    }
    
    for(int i=0; i<inbranch5->GetEntries();i++){
      inbranch5->GetEntry(i);
      h->Fill(data5.qlong);
    }
    
    h->Draw();
  }
  
  if(n==2){
    int peaks=5;
		
    /*
      double max[peaks] , min [peaks];
      cout<<"Inserisci i range in cui sono contenuti i picchi (min;max) in ordine crescente"<<endl;
      for(int i=0;i<peaks;i++){
      cin>>min[i]>>max[i]; }
    */
    double max=25000;
    double min=800;
    		
    TH1F *h2[peaks];
    for(int i=0;i<peaks;i++){
      h2[i] = new TH1F("","", numBins,minX,maxX); }
    
    
    unsigned short dat;
    
    double resolution[peaks];
    TH1F* hRESO[peaks];
    TF1* gaus[peaks];
    int range=400;
    
    for(int i=0; i<inbranch1->GetEntries();i++){
      inbranch1->GetEntry(i);
      dat=data1.qlong;
      h->Fill(data1.qlong);
      if(dat>min && dat<max){
	h2[0]->Fill(data1.qlong);
      }	
    }
    gaus[0]=new TF1("gaus","gaus",h2[0]->GetMaximumBin()-range,h2[0]->GetMaximumBin()-range);
    hRESO[0]=h2[0];
    hRESO[0]->Fit(gaus[0],"R");
    resolution[0]=gaus[0]->GetParameter(2);
        

    for(int i=0; i<inbranch2->GetEntries();i++){
      inbranch2->GetEntry(i);
      dat=data2.qlong;
      h->Fill(data2.qlong);
      if(dat>min && dat<max){
	h2[1]->Fill(data2.qlong);
      }	
    }
    gaus[1]=new TF1("gaus","gaus",h2[1]->GetMaximumBin()-range,h2[1]->GetMaximumBin()-range);
    hRESO[1]=h2[1];
    hRESO[1]->Fit(gaus[1],"R");
    resolution[1]=gaus[1]->GetParameter(2);
    
    
    for(int i=0; i<inbranch3->GetEntries();i++){
      inbranch3->GetEntry(i);
      dat=data3.qlong;
      h->Fill(data3.qlong);
      if(dat>min && dat<max){
	h2[2]->Fill(data3.qlong);
      }	
    }
    gaus[2]=new TF1("gaus","gaus",h2[2]->GetMaximumBin()-range,h2[2]->GetMaximumBin()-range);
    hRESO[2]=h2[2];
    hRESO[2]->Fit(gaus[2],"R");
    resolution[2]=gaus[2]->GetParameter(2);
    
    for(int i=0; i<inbranch4->GetEntries();i++){
      inbranch4->GetEntry(i);
      dat=data4.qlong;
      h->Fill(data4.qlong);
      if(dat>min && dat<max){
	h2[3]->Fill(data4.qlong);
      }	
    }
    gaus[3]=new TF1("gaus","gaus",h2[3]->GetMaximumBin()-range,h2[3]->GetMaximumBin()-range);
    hRESO[3]=h2[3];
    hRESO[3]->Fit(gaus[3],"R");
    resolution[3]=gaus[3]->GetParameter(2);

    
    for(int i=0; i<inbranch5->GetEntries();i++){
      inbranch5->GetEntry(i);
      dat=data5.qlong;
      h->Fill(data5.qlong);
      if(dat>min && dat<max){
	h2[4]->Fill(data5.qlong);
      }	
    }
    gaus[4]=new TF1("gaus","gaus",h2[4]->GetMaximumBin()-range,h2[4]->GetMaximumBin()-range);
    hRESO[4]=h2[4];
    hRESO[4]->Fit(gaus[4],"R");
    resolution[4]=gaus[4]->GetParameter(2);
    
    double Max[peaks];
    double delays[peaks];
    for(int i=0;i<peaks;i++){
      Max[i]=(h2[i]->GetMaximumBin())*TMath::Power(constTAC,-1);
      delays[i]=Max[i]-Max[0];
      resolution[i]=(2.35*resolution[i])/hRESO[i]->GetEntries();
    }
        
    TGraph *grlen  = new TGraph(peaks,length,delays);
    TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,600,400);
    TGraph *grreso  = new TGraph(peaks,length,resolution);
    TCanvas *c2 = new TCanvas("c2","Graph Draw Options",200,10,600,400);
    
    c1->cd();
    grlen->SetTitle("Delay in function of the cable length");
    grlen->GetXaxis()->SetTitle("Cable length [cm]");
    grlen->GetYaxis()->SetTitle("Delay [ns]");
    grlen->Draw("AP*");
    TF1* fitfunc=new TF1("fitfunc","pol1",0,30);
    grlen->Fit("fitfunc");

    
    c2->cd();
    grreso->SetTitle("Resolution in function of the cable length");
    grreso->GetXaxis()->SetTitle("Cable length [cm]");
    grreso->GetYaxis()->SetTitle("Resolution [ns]");
    grreso->Draw("AL*");
  }
}

//--------------------------------------------------------------
//resolution for cobalt60---------------------------------------
//--------------------------------------------------------------
void cobaltRESO(){
  const char* Data1=cobalt;
  const char* DataNa1=NaCal[0];
  const char* DataNa2=NaCal[1];
  
  const int numBins=10000;
  const int minX=0;
  const int maxX=100000;
    
  int n;
  cout<<"Se vuoi solo osservare lo spettro digita 1, se vuoi calibrare digita 2"<<endl;
  cin>>n;

  slimport_data_t data1;
  TFile *infile1 = new TFile (Data1);
  TTree *intree1 = (TTree*)infile1->Get("acq_tree_0");
  TBranch *inbranch1 = intree1->GetBranch("acq_ch2");
  inbranch1->SetAddress(&data1.timetag);

  float* par1=energyCalPar(DataNa1,"acq_tree_0","acq_ch0");
  float* par2=energyCalPar(DataNa2,"acq_tree_0","acq_ch1");

  TH1F *h = new TH1F("","", numBins,minX,maxX);
	
  if(n==1){
	
    for(int i=0; i<inbranch1->GetEntries();i++){
      inbranch1->GetEntry(i);
      h->Fill(data1.qlong);
    }
    
    h->Draw();
  }
  
  if(n==2){
    int peaks=6;
		
    double max=25000;
    double min=800;
    
    double length[peaks];
    cout<<"Inserire i valori delle lunghezze dei cavi (in caso di assenza scrivere 0) in ordine crescente"<<endl;
    for(int i=0;i<peaks;i++){
      cin>>length[i];	}
    
		
    TH1F *h2[peaks];
    for(int i=0;i<peaks;i++){
      h2[i] = new TH1F("","", numBins,minX,maxX); }
    
    
    unsigned short dat;
    
    double resolution[peaks];
    TH1F* hRESO[peaks];
    TF1* gaus[peaks];
    int range=400;
    
    for(int i=0; i<inbranch1->GetEntries();i++){
      inbranch1->GetEntry(i);
      dat=data1.qlong;
      h->Fill(data1.qlong);
      if(dat>min && dat<max){
	h2[0]->Fill(data1.qlong);
      }	
    }
    gaus[0]=new TF1("gaus","gaus",h2[0]->GetMaximumBin()-range,h2[0]->GetMaximumBin()-range);
    hRESO[0]=h2[0];
    hRESO[0]->Fit(gaus[0],"R");
    resolution[0]=gaus[0]->GetParameter(2);
    plot(hRESO[0]);

    
    for(int i=0; i<inbranch2->GetEntries();i++){
      inbranch2->GetEntry(i);
      dat=data2.qlong;
      h->Fill(data2.qlong);
      if(dat>min && dat<max){
	h2[1]->Fill(data2.qlong);
      }	
    }
    gaus[1]=new TF1("gaus","gaus",h2[1]->GetMaximumBin()-range,h2[1]->GetMaximumBin()-range);
    hRESO[1]=h2[1];
    hRESO[1]->Fit(gaus[1],"R");
    resolution[1]=gaus[1]->GetParameter(2);
    
    
    for(int i=0; i<inbranch3->GetEntries();i++){
      inbranch3->GetEntry(i);
      dat=data3.qlong;
      h->Fill(data3.qlong);
      if(dat>min && dat<max){
	h2[2]->Fill(data3.qlong);
      }	
    }
    gaus[2]=new TF1("gaus","gaus",h2[2]->GetMaximumBin()-range,h2[2]->GetMaximumBin()-range);
    hRESO[2]=h2[2];
    hRESO[2]->Fit(gaus[2],"R");
    resolution[2]=gaus[2]->GetParameter(2);
    
    for(int i=0; i<inbranch4->GetEntries();i++){
      inbranch4->GetEntry(i);
      dat=data4.qlong;
      h->Fill(data4.qlong);
      if(dat>min && dat<max){
	h2[3]->Fill(data4.qlong);
      }	
    }
    gaus[3]=new TF1("gaus","gaus",h2[3]->GetMaximumBin()-range,h2[3]->GetMaximumBin()-range);
    hRESO[3]=h2[3];
    hRESO[3]->Fit(gaus[3],"R");
    resolution[3]=gaus[3]->GetParameter(2);

    
    for(int i=0; i<inbranch5->GetEntries();i++){
      inbranch5->GetEntry(i);
      dat=data5.qlong;
      h->Fill(data5.qlong);
      if(dat>min && dat<max){
	h2[4]->Fill(data5.qlong);
      }	
    }
    gaus[4]=new TF1("gaus","gaus",h2[4]->GetMaximumBin()-range,h2[4]->GetMaximumBin()-range);
    hRESO[4]=h2[4];
    hRESO[4]->Fit(gaus[4],"R");
    resolution[4]=gaus[4]->GetParameter(2);
    
    double Max[peaks];
    double delays[peaks];
    for(int i=0;i<peaks;i++){
      Max[i]=(h2[i]->GetMaximumBin())*TMath::Power(constTAC,-1);
      delays[i]=Max[i]-Max[0];
      resolution[i]=(2.35*resolution[i])/hRESO[i]->GetEntries();
    }
        
    TGraph *grlen  = new TGraph(peaks,length,delays);
    TCanvas *c1 = new TCanvas("c1","Graph Draw Options",200,10,600,400);
    TGraph *grreso  = new TGraph(peaks,length,resolution);
    TCanvas *c2 = new TCanvas("c2","Graph Draw Options",200,10,600,400);
    
    c2->cd();
    grreso->SetTitle("Resolution in function of the cable length");
    grreso->GetXaxis()->SetTitle("Cable length [cm]");
    grreso->GetYaxis()->SetTitle("Resolution [ns]");
    grreso->Draw("AL*");
  }
}
