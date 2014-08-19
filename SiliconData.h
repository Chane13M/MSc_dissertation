#ifndef __SiliconData__
#define __SiliconData__ 1

/*
 * 
 * This is a header file defining the data structure for silicon events for K600 analysis.
 * It should be used as a basis for another analysis file, an example of which should be found in the same directory.
 * 
 * Author: Philip Adsley, June 2014
 * E-mail: padsley@gmail.com
 * 
 * Please contact me if you find errors or have useful suggestions
 * 
 */
#include <vector>
#include <stdio.h>
#include <TCutG.h>


//define the silicon calibration parameters
double silicon_offset[128] = {-167.805,-214.406,-187.454,-181.633,-160.386,-149.132,-202.629,-160.261,-203.654,-173.817,-187.64,-157.683,-148.687,-92.1872,-161.218,-70.8537,-180.455,-180.758,-227.364,-152.841,-184.163,-138.119,-178.638,-167.513,-235.224,-225.14,-196.467,-234.196,-171.881,-185.131,-151.409,-145.787,258.692,-88.8767,-140.271,-101.703,-140.5,-88.484,-245.035,-77.4569,-94.7413,-146.396,-136.314,-117.08,-215.074,-105.078,-144.869,-161.288,-295.513,-297.778,-193.066,-238.863,-246.341,-266.892,-275.673,-259.938,-264.263,-320.586,-240.4,-273.869,-234.21,-175.276,-229.119,-100.009,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-153.9,-141.116,-66.7166,-103.2,-130.332,-95.8439,-112.015,-162.337,-85.2311,-104.158,-133.836,-104.588,-176.148,-125.141,-90.5022,-124.296,-29.529,-61.7865,-88.3409,-114.406,-92.1489,-5.52266,-50.7833,-84.6803,-97.1285,-49.1359,-65.4897,-101.801,-92.5068,-116.007,-49.3386,-73.9171,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

double silicon_gain[128] = {2.7211,2.71494,2.73297,2.73106,2.73573,2.68548,2.76225,2.80152,2.79172,2.75188,2.80635,2.66006,2.75826,2.96099,2.78068,2.73402,2.79736,2.86712,2.84351,2.74067,2.83164,2.86948,2.87157,2.79478,2.83121,2.88493,2.84582,2.77553,2.88338,2.88706,2.93624,2.89496,2.74762,2.8514,2.89757,2.89894,2.88723,2.87429,2.90762,2.93522,2.94179,2.87595,2.90036,2.93048,2.95111,2.95414,2.97117,2.99479,3.17541,3.19887,3.14558,3.18869,3.12393,3.14539,3.17036,3.12102,3.07041,3.17293,3.2341,3.23097,3.25645,3.16729,3.24288,3.06999,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3.01396,2.90243,3.03025,2.99131,2.99434,3.03356,3.01627,2.97887,2.93761,2.98534,3.02228,3.01619,3.02228,3.0249,3.06732,2.95583,2.87665,2.86676,2.94053,2.91049,2.99978,2.91588,2.82934,2.94514,2.96318,2.88167,2.87429,3.01928,2.89797,2.81918,2.94514,2.75654,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

class SiliconData
{
public :
  SiliconData();
  virtual ~SiliconData();
  
  private :
  //The actual members of the class
  int SiliconHits;
  
  //Physical values which are generated
  std::vector<double> SiliconEnergy;
  std::vector<double> SiliconTheta;
  std::vector<double> SiliconPhi;
  std::vector<double> SiliconTime;
  
  //Diagnostic values - these are things which might be useful to finding problems in the experiment or the sort code.
  std::vector<int> DetectorHit;
  std::vector<int> ADCChannelFront;
  std::vector<int> ADCChannelBack;
  std::vector<int> TDCChannelFront;
  std::vector<int> TDCChannelBack;
  std::vector<int> ADCValueFront;
  std::vector<int> ADCValueBack;
  std::vector<int> TDCValueFront;
  std::vector<int> TDCValueBack;
  std::vector<double> EnergyFront;
  std::vector<double> EnergyBack;
  
  std::vector<int> TDCChannelMultiplicity;
//   TCutG *mFrontBackEnergyCut;
  
public :
  //Setters - set the physical values for each physical event
  void SetHits(int hits)		{SiliconHits = hits;}
  
  void SetEnergy(double ener)		{SiliconEnergy.push_back(ener);}
  void SetTheta(double thet)		{SiliconTheta.push_back(thet);}
  void SetPhi(double ph)		{SiliconPhi.push_back(ph);}
  void SetTime(double tim)		{SiliconTime.push_back(tim);}
  
  void SetDetectorHit(int det)		{DetectorHit.push_back(det);}
  void SetADCChannelFront(int chan)	{ADCChannelFront.push_back(chan);}
  void SetADCChannelBack(int chan)	{ADCChannelBack.push_back(chan);}
  void SetTDCChannelFront(int chan)	{TDCChannelFront.push_back(chan);}
  void SetTDCChannelBack(int chan)	{TDCChannelBack.push_back(chan);}
  void SetADCValueFront(int chan)	{ADCValueFront.push_back(chan);}
  void SetADCValueBack(int chan)	{ADCValueBack.push_back(chan);}
  void SetTDCValueFront(int chan)	{TDCValueFront.push_back(chan);}
  void SetTDCValueBack(int chan)	{TDCValueBack.push_back(chan);}
  void SetEnergyFront(double ener)	{EnergyFront.push_back(ener);}
  void SetEnergyBack(double ener)	{EnergyBack.push_back(ener);}
//   void SetFrontBackEnergyCut(TCutG *cut) {printf("Set cut\n");mFrontBackEnergyCut = cut;}
  
  //Getters - return the value of the private member - shouldn't have them visible to the user
  double GetEnergy(int i)		{return SiliconEnergy.at(i);}
  double GetTheta(int i)		{return SiliconTheta.at(i);}
  double GetPhi(int i)			{return SiliconPhi.at(i);}
  double GetTime(int i)			{return SiliconTime.at(i);}  
  
//   TCutG *GetFrontBackEnergyCut() 	{return mFrontBackEnergyCut;}
  
  void PrintEvent();
  bool TestEvent();
  void ClearEvent();
  
  unsigned int SizeOfEvent();
};

#endif