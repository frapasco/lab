//--------------------------------------------------------------
//data locations------------------------------------------------
//--------------------------------------------------------------
vector<const char*> NaCal={"../timing1stDayDATA/energyCalibrationD1OR.root","../timing1stDayDATA/energyCalibrationD2OR.root"};

const char* cobalt="../timing3rdDayDATA/cobalt12hours.root";

vector<const char*> timeReso={"../timing2ndDayDATA/timeReso-1.root","../timing2ndDayDATA/timeReso0.root","../timing2ndDayDATA/timeReso+1.root","../timing2ndDayDATA/timeReso+2.root"};

vector<const char*> TACcal={"../timing1stDayDATA/TACCalibration2ms.root","../timing1stDayDATA/TACCalibration4ms.root","../timing1stDayDATA/TACCalibration8ms.root","../timing1stDayDATA/TACCalibration10ms.root","../timing1stDayDATA/TACCalibration15ms.root","../timing1stDayDATA/TACCalibration20ms.root","../timing1stDayDATA/TACCalibration23ms.root","../timing1stDayDATA/TACCalibration30ms.root",};
double delay[]={4,8,10,15,20,23,30};

vector<const char*> LEMOcal={"../timing2ndDayDATA/TAClenght30ns-10.root","../timing2ndDayDATA/TAClenght30ns-20.root","../timing2ndDayDATA/TAClenght30ns-30.root","../timing2ndDayDATA/TAClenght30ns-50.root"};
double length[]={0,10,20,30,50};
//--------------------------------------------------------------
//global variables----------------------------------------------
//--------------------------------------------------------------
double constTAC;

struct slimport_data_t{
  unsigned long     timetag;
  unsigned int      baseline;
  unsigned short    qshort;
  unsigned short    qlong;
  unsigned short    pur;
  unsigned short    samples[4096];
};
  
//-------------------------------------------------------------
//calibrate histo----------------------------------------------
//-------------------------------------------------------------
TH1F* CalibrateHisto(TH1F* h, float m, float q) { 
  TH1F* h_cal=(TH1F*)h->Clone();
  float max_kev=h_cal->GetXaxis()->GetXmax()*m+q;
  float min_kev=h_cal->GetXaxis()->GetXmin()*m+q;
  h_cal->GetXaxis()->SetLimits(min_kev,max_kev);
  if (m!=1 && q!=0) 
    h_cal->SetXTitle("keV");
    
  //calibration check
  //  TF1 *f1=new TF1("f1","gaus",450,650);
  //  h_cal->Fit(f1,"R");
  //  cout<<endl<<endl;
  //  cout<<"+++check gaussian fit: "<<f1->GetParameter(1)<<"+++"<<endl;
  //  cout<<endl<<endl;

  return h_cal;
}

//returns the fit parameters for calibration--------------
float* calibrate(TH1F* h_1){
  TH1F* h_na=(TH1F*)h_1->Clone();
  int minbin=h_na->GetMaximumBin();
  h_na->GetXaxis()->SetRange(minbin+5,h_na->GetNbinsX());
  
  //search the peaks
  TSpectrum* s = new TSpectrum(30);
  int nPeaks;
  double* na_bin;
  nPeaks = s->Search(h_na,2,"",0.05);
  na_bin = s->GetPositionX();
  //  plot(h_na);

  //extra fits for better precision
  float range=25e6;
  TF1* f1=new TF1("f1","gaus",na_bin[0]+range,na_bin[0]-range);
  h_na->Fit(f1, "R");
  na_bin[0]=f1->GetParameter(1);
  
  TF1* f2=new TF1("f2","gaus",na_bin[1]+range,na_bin[1]-range);
  h_na->Fit(f2, "R+");
  na_bin[1]=f2->GetParameter(1);
        
  //fit the peaks with the Na energies
  double na_kev[2]; 
  na_kev[0] = 340.; 
  na_kev[1] = 1062.;
  TGraphErrors* graphErr = new TGraphErrors(nPeaks,na_bin,na_kev);
  TF1* fitfun = new TF1("calfitfun1","pol1",na_bin[0],na_bin[1]);
  graphErr->Fit(fitfun);
  
  //get the fit parameters
  float m = fitfun->GetParameter(1);
  float q = fitfun->GetParameter(0);

  h_na->GetXaxis()->SetRange(0,200);

  float* par;
  par=new float[2];
  par[0]=m; par[1]=q;
  return par;
}

//--------------------------------------------------------------
//energy calibration parameters---------------------------------
//--------------------------------------------------------------
float* energyCalPar(const char* filename, const char* treename, const char* channel){
  const int numBins=10000;
  const int minX=0;
  const int maxX=100000;

  slimport_data_t data1;
  TFile *infile1 = new TFile (filename);
  TTree *intree1 = (TTree*)infile1->Get(treename);
  TBranch *inbranch1 = intree1->GetBranch(channel);
  inbranch1->SetAddress(&data1.timetag);

  TH1F *h = new TH1F("","", numBins,minX,maxX);
  
  for(int i=0; i<inbranch1->GetEntries();i++){
    inbranch1->GetEntry(i);
    h->Fill(data1.qlong);
  }
  
  float* par;
  par=calibrate(h);
  TH1F* h1=CalibrateHisto(h,par[0],par[1]);
  h1->SetTitle(channel);
  return par;
}

//--------------------------------------------------------------
//plot template
//--------------------------------------------------------------
template <class Obj>
void plot(Obj* h){
  TCanvas* c=new TCanvas;
  h->Draw();
}

template <class Obj>
void plotSave(Obj* h,const char* name){
  TCanvas* c=new TCanvas;
  h->Draw();
  c->SaveAs(name);
}
