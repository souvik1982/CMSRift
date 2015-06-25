#include <iostream>

#include "TApplication.h"
#include "TEveManager.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TEveGeoNode.h"
#include "TEveViewer.h"
#include "TGLViewer.h"
#include "TGedEditor.h"
#include "TEveBrowser.h"
#include "TEveWindow.h"
#include "TGTab.h"

#include "OVR.h"
#include "Kernel/OVR_Math.h"

using namespace OVR;

int main()
{
    TApplication *myapp=new TApplication("myapp",0,0);
    
    TEveManager *gEve=TEveManager::Create();
    
    TGeoManager *gGeoManager=gEve->GetGeometry("cms.root");
    gGeoManager->DefaultColors();
    
    TGeoVolume *top=gGeoManager->GetTopVolume()->FindNode("CMSE_1")->GetVolume();
    
    TEveGeoTopNode *beam1=new TEveGeoTopNode(gGeoManager, top->FindNode("BEAM_1"));
    beam1->SetVisLevel(2);
    gEve->AddGlobalElement(beam1);
    
    // TEveGeoTopNode *beam2=new TEveGeoTopNode(gGeoManager, top->FindNode("BEAM_2"));
    // beam2->SetVisLevel(2);
    // gEve->AddGlobalElement(beam2);
    
    TEveGeoTopNode *trk=new TEveGeoTopNode(gGeoManager, top->FindNode("TRAK_1"));
    trk->SetVisLevel(7);
    gEve->AddGlobalElement(trk);
    
    TEveGeoTopNode *calo=new TEveGeoTopNode(gGeoManager, top->FindNode("CALO_1"));
    calo->SetVisLevel(3);
    gEve->AddGlobalElement(calo);
    
    TEveGeoTopNode *muon=new TEveGeoTopNode(gGeoManager, top->FindNode("MUON_1"));
    muon->SetVisLevel(4);
    gEve->AddGlobalElement(muon);
    
    TEveViewer *v_stereo=new TEveViewer("v_stereo", "Stereo view");
    v_stereo->SpawnGLViewer((TGedEditor*)gEve->GetEditor(), kTRUE, kFALSE);
    v_stereo->AddScene(gEve->GetGlobalScene());
    TEveWindowSlot *slot=TEveWindow::CreateWindowInTab(gEve->GetBrowser()->GetTabRight());
    slot->ReplaceWindow(v_stereo);
    gEve->GetViewers()->AddElement(v_stereo);
    gEve->GetBrowser()->GetTabRight()->SetTab(1);
    gEve->FullRedraw3D(kTRUE);
    
    v_stereo->GetGLViewer()->GetClipSet()->SetClipType(TGLClip::kClipBox);
    v_stereo->GetGLViewer()->SetGuideState(TGLUtil::kAxesEdge, kTRUE, kFALSE, 0);
    v_stereo->GetGLViewer()->RefreshPadEditor(v_stereo);
    v_stereo->GetGLViewer()->CurrentCamera().RotateRad(-0.2, 4.0);
    v_stereo->GetGLViewer()->DoDraw();
    
    v_stereo->UndockWindowDestroySlot();
    
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
            float x_old=0, y_old=0, z_old=0, w_old=0;
            while (true)
            {
                Quatf q = fusionResult.GetOrientation();
                if (fabs(q.x-x_old)>0.01 || fabs(q.y-y_old)>0.01 || fabs(q.z-z_old)>0.01 || fabs(q.w-w_old)>0.001)
                {
                    // std::cout<<"Orientation quaternion: axis = "<<q.x<<"i + "<<q.y<<"j + "<<q.z<<"k. rotation = "<<q.w<<std::endl;
                    float yaw=0, pitch=0, roll=0;
                    q.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);
                    std::cout<<"yaw = "<<yaw<<", pitch = "<<pitch<<", roll = "<<roll<<std::endl;
                    //Rotation_Conversion(q.x, q.y, q.z, q.w);
                    x_old=q.x;
                    y_old=q.y;
                    z_old=q.z;
                    w_old=q.w;
                }
            }
        }
        else
        {
            std::cout<<"Couldn't attached to HMD sensor."<<std::endl;
            // return 0;
        }
    }
    else
    {
        std::cout<<"No HMD attached!"<<std::endl;
        // return 0;
    }
    
    myapp->Run();
    
    return 0;
}

