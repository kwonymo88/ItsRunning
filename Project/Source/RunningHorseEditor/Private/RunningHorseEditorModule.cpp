#include "RunningHorseEditorModule.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_GAME_MODULE(FRunningHorseEditorModule, RunningHorseEditor);

#define LOCTEXT_NAMESPACE "RunningHorseEditor"

void FRunningHorseEditorModule::StartupModule()
{
   // UE_LOG(RunningHorseEditorModule, Warning, TEXT("RunningHorseEditorModule: Log Started"));
}

void FRunningHorseEditorModule::ShutdownModule()
{
    //UE_LOG(RunningHorseEditorModule, Warning, TEXT("RunningHorseEditorModule: Log Ended"));
}

#undef LOCTEXT_NAMESPACE