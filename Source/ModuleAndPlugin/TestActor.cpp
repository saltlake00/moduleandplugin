// TestActor.cpp


#include "TestActor.h"
#include "MySpartaLog/MySpartaLog.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogMySpartaModule, Display, TEXT("Actor call MySpartaLog Module!"));
}
