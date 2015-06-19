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

void CMSRift()
{
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
  
  // Double_t boxClip[6]={500, 0, 0, 1000, 1000, 2000};
  // v_stereo->GetGLViewer()->GetClipSet()->SetClipState(TGLClip::kClipBox, boxClip);
  v_stereo->GetGLViewer()->GetClipSet()->SetClipType(TGLClip::kClipBox);
  v_stereo->GetGLViewer()->SetGuideState(TGLUtil::kAxesEdge, kTRUE, kFALSE, 0);
  v_stereo->GetGLViewer()->RefreshPadEditor(v_stereo);
  v_stereo->GetGLViewer()->CurrentCamera().RotateRad(-0.2, 4.0);
  v_stereo->GetGLViewer()->DoDraw();
  
  v_stereo->UndockWindowDestroySlot();
  
  
}
  
