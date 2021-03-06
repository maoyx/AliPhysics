AliAnalysisTask *AddTask_jbook_JPsiQA(TString prod="", Bool_t gridconf=kFALSE){
  //get the current analysis manager
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
  if (!mgr) {
    Error("AddTask_jbook_JPsiQA", "No analysis manager found.");
    return 0;
  }

  //Do we have an MC handler?
  Bool_t hasMC = kFALSE;
  TString list = gSystem->Getenv("LIST");
  if( list.IsNull()) list=prod;
  if( list.Contains("LHC10h")   || list.Contains("LHC11h")   ) hasMC=kFALSE;
  if( list.Contains("LHC11a10") || list.Contains("LHC12a17") ) hasMC=kTRUE;

  //Do we have an AOD handler?
  Bool_t isAOD=(mgr->GetInputEventHandler()->IsA()==AliAODInputHandler::Class() ? kTRUE : kFALSE);

  // set AOD debug levels
  if(isAOD) {
    mgr->AddClassDebug("AliAODTrack", AliLog::kFatal);
    mgr->AddClassDebug("AliAODpidUtil", AliLog::kInfo); 
  }
  
  //set config file name
  TString configFile("");
  printf("%s \n",gSystem->pwd());
  TString trainRoot=gSystem->Getenv("TRAIN_ROOT");
  if (!trainRoot.IsNull())
    configFile="$TRAIN_ROOT/jbook_jpsi/ConfigJpsiQA_jb_PbPb.C";   // gsi config
  else if(!gSystem->Exec("alien_cp alien:///alice/cern.ch/user/j/jbook/PWGDQ/dielectron/macrosJPSI/ConfigJpsiQA_jb_PbPb.C ."))
    configFile=Form("%s/ConfigJpsiQA_jb_PbPb.C",gSystem->pwd());                        // alien config
  else
    configFile="$ALICE_PHYSICS/PWGDQ/dielectron/macrosJPSI/ConfigJpsiQA_jb_PbPb.C"; // aliroot config

  if(!gridconf)
    configFile="$ALICE_PHYSICS/PWGDQ/dielectron/macrosJPSI/ConfigJpsiQA_jb_PbPb.C"; // aliroot config

  //create task and add it to the manager
  AliAnalysisTaskMultiDielectron *task=new AliAnalysisTaskMultiDielectron("MultiDieData");
  task->SetTriggerMask(AliVEvent::kMB+AliVEvent::kCentral+AliVEvent::kSemiCentral);
  if (!hasMC) task->UsePhysicsSelection();
  mgr->AddTask(task);
  
  //load dielectron configuration file
  TString checkconfig="ConfigJpsiQA_jb_PbPb";
  if (!gROOT->GetListOfGlobalFunctions()->FindObject(checkconfig.Data()))
    gROOT->LoadMacro(configFile.Data());

  //add dielectron analysis with different cuts to the task
  for (Int_t i=0; i<nDie; ++i){ //nDie defined in config file
    AliDielectron *jpsi=ConfigJpsiQA_jb_PbPb(i,list);
    if (jpsi ) task->AddDielectron(jpsi);
    if (jpsi ) printf("add: %s\n",jpsi->GetName());
  }
  
  //Add event filter
  AliDielectronEventCuts *eventCuts=new AliDielectronEventCuts("eventCuts","Vertex Track && |vtxZ|<10 && ncontrib>0");
  if (isAOD) eventCuts->SetVertexType(AliDielectronEventCuts::kVtxAny);
  eventCuts->SetRequireVertex();
  eventCuts->SetMinVtxContributors(1);
  eventCuts->SetVertexZ(-10.,10.);
  eventCuts->SetCentralityRange(0.0,80.0);
  task->SetEventFilter(eventCuts);

  
  //create output container
  AliAnalysisDataContainer *coutput1 =
    mgr->CreateContainer("jbookQA_tree",
                         TTree::Class(),
                         AliAnalysisManager::kExchangeContainer,
                         "jbook_default");
  
  AliAnalysisDataContainer *cOutputHist1 =
    mgr->CreateContainer("jbookQA",
                         TList::Class(),
                         AliAnalysisManager::kOutputContainer,
                         "jbookQA.root");

  
  AliAnalysisDataContainer *cOutputHist2 =
    mgr->CreateContainer("jbookQA_CF",
                         TList::Class(),
			 AliAnalysisManager::kOutputContainer,//AliAnalysisManager::kExchangeContainer,
                         "jbookQA.root");
    
  AliAnalysisDataContainer *cOutputHist3 =
    mgr->CreateContainer("jbookQA_EventStat",
                         TH1D::Class(),
                         AliAnalysisManager::kOutputContainer,
                         "jbookQA.root");
  
  mgr->ConnectInput(task,  0, mgr->GetCommonInputContainer());
  mgr->ConnectOutput(task, 0, coutput1 );
  mgr->ConnectOutput(task, 1, cOutputHist1);
  mgr->ConnectOutput(task, 2, cOutputHist2);
  mgr->ConnectOutput(task, 3, cOutputHist3);
  
  return task;
}
