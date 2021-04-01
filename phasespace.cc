#include "ModelImport.hh"
#include <iostream>
#include <string>
#include <array>

#include "G4RunManagerFactory.hh"
#include "detectorconstruction.hh"
#include "actioninitialization.hh"
#include "runaction.hh"
#include "FTFP_BERT.hh"
#include "G4PhysListFactory.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4ParallelWorldPhysics.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4Timer.hh"
using namespace std;
int main ( int argc, char** argv)
{
    auto* runManager =
            G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);
    G4UIExecutive* ui = 0;
    if(argc==2)  runManager->SetNumberOfThreads(atoi(argv[1]));
    else         ui = new G4UIExecutive(argc, argv);

    G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    //generate socket for each source
    DetectorConstruction* det = new DetectorConstruction(new ModelImport());
    runManager->SetUserInitialization(det);
    G4VModularPhysicsList* physicsList = new FTFP_BERT;
    //    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new ActionInitialization());

    if(ui){
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        UImanager->ApplyCommand("/control/execute gui.mac");
        ui->SessionStart();
    }else{
        //runManager->Initialize();
        UImanager->ApplyCommand("/run/numberOfThreads 12");
        UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/beam/spec 80kVp.txt");
        UImanager->ApplyCommand("/run/beamOn 1");
        G4Timer timer; timer.Start();
        UImanager->ApplyCommand("/run/beamOn 1000000000");
        timer.Stop(); G4cout<<timer.GetRealElapsed()<<G4endl;

//        UImanager->ApplyCommand("/control/execute "+G4String(argv[1]));
    }
    delete runManager;
    delete visManager;
    return 0;
}

