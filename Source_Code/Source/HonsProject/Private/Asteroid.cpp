// Fill out your copyright notice in the Description page of Project Settings.


#include "Asteroid.h"

// Sets default values
AAsteroid::AAsteroid()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshCompopnent"));
	StaticMeshComponent->SetupAttachment(SceneComponent);

	////choose a random mesh out of 4 for the ore
	//auto MeshAssetA = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/GreenwoodFantasyVillage/Meshes/SM_RockA.SM_RockA'"));
	//auto MeshAssetB = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/GreenwoodFantasyVillage/Meshes/SM_RockB.SM_RockB'"));
	//auto MeshAssetC = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/GreenwoodFantasyVillage/Meshes/SM_RockC.SM_RockC'"));
	//auto MeshAssetD = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/GreenwoodFantasyVillage/Meshes/SM_RockD.SM_RockD'"));
	//UStaticMesh* tempM = nullptr;
	//
	//
	//	int choiceNR = FMath::RandRange(0, 3);
	//
	//	switch (choiceNR) {
	//	case 1:
	//		if (MeshAssetB.Succeeded()) {
	//			tempM = MeshAssetB.Object;
	//
	//		}
	//		break;
	//	case 2:
	//		if (MeshAssetC.Succeeded()) {
	//			tempM = MeshAssetC.Object;
	//		}
	//		break;
	//	case 3:
	//		if (MeshAssetD.Succeeded()) {
	//			tempM = MeshAssetD.Object;
	//		}
	//		break;
	//	default:
	//		if (MeshAssetA.Succeeded()) {
	//			tempM = MeshAssetA.Object;
	//		}
	//		break;
	//	}


	auto MeshAssetD = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/ImportedContent/GreenwoodFantasyVillage/Meshes/SM_RockD.SM_RockD'"));
	UStaticMesh* tempM = MeshAssetD.Object;
	//tempM.scale
	StaticMeshComponent->SetStaticMesh(tempM);
	StaticMeshComponent->SetRelativeScale3D(FVector(0.3f,0.3f,0.3f));



	//create random colour on material
	auto Mat_o = StaticMeshComponent->GetMaterial(0);

	myMat = UMaterialInstanceDynamic::Create(Mat_o, NULL);
	StaticMeshComponent->SetMaterial(0, myMat);

	myRot = FRotator(0,0,0);
	myRot.Yaw = FMath::RandRange(-1.0f, 1.0f);
	myRot.Pitch = FMath::RandRange(-1.0f, 1.0f);
	myRot.Roll = FMath::RandRange(-1.0f, 1.0f);

	myRotateSpeed = FMath::RandRange(50.0f, 150.0f);


	FVector4 colour_;

	//option to set colour too
	colour_.X = FMath::RandRange(0.0f, 1.0f);
	colour_.Y = FMath::RandRange(0.0f, 1.0f);
	colour_.Z = FMath::RandRange(0.0f, 1.0f);
	//colour_.W = 1.0f;
	//GravComp->myCol = colour_;
	myMat->SetVectorParameterValue(TEXT("OreColour"), colour_);
}




// Called when the game starts or when spawned
void AAsteroid::BeginPlay()
{
	Super::BeginPlay();


	//FTransform tr;
	//tr.SetIdentity();

	//create Nbody handler
	//GravComp = Cast<UGravBodyComponent>(this->AddComponentByClass(UGravBodyComponent::StaticClass(), false, tr, true));
	//GravComp->RegisterComponent();

	
	
}

// Called every frame
void AAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GravComp) {
		AddActorWorldRotation(myRot * myRotateSpeed * GravComp->myLocalTimeEditor * DeltaTime);
	}

	//this->AddActorLocalRotation()
}

