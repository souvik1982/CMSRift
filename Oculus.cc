#include <iostream>

#include "OVR.h"
#include "Kernel/OVR_Math.h"

using namespace OVR;

int main()
{
  System::Init(Log::ConfigureDefaultLog(LogMask_All));
  
  Ptr<DeviceManager> pManager = *DeviceManager::Create();
  Ptr<HMDDevice> pHMD = *pManager->EnumerateDevices<HMDDevice>().CreateDevice();
  if (pHMD)
  {
    std::cout<<"HMD attached. Good to go."<<std::endl;
    Ptr<SensorDevice> pSensor  = *pHMD->GetSensor();
    if (pSensor)
    {
      SensorFusion fusionResult;
      fusionResult.AttachToSensor(pSensor);
      
      // Get the orientation quaternion to control view
      Quatf q = fusionResult.GetOrientation();
      std::cout<<"Orientation quaternion: axis = "<<q.x<<"i + "<<q.y<<"j + "<<q.z<<"k. rotation = "<<q.w<<std::endl;
    }
    else
    {
      std::cout<<"Couldn't attached to HMD sensor."<<std::endl;
      return 0;
    }
  }
  else
  {
    std::cout<<"No HMD attached!"<<std::endl;
    return 0;
  }
  
  return 1;
}
