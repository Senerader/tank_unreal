// Copyright M.S2019

#include "SprungWheel.h"
#include "Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Engine/Classes/Components/SphereComponent.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;
	//setting up physics constraints
	PhysicsConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Main Constraint"));
	SetRootComponent(PhysicsConstraint);

	//setting wheel mesh and default values
	Axel = CreateDefaultSubobject<USphereComponent>(FName("Axel"));
	Axel->SetupAttachment(PhysicsConstraint);

	//setting up physics constraints
	AxelWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics AxelWheel Constraint"));
	AxelWheelConstraint->SetupAttachment(Axel);

	//setting wheel sphere and default values
	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axel);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Axel || !Wheel)
	{
		return;
	}

	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!(GetAttachParentActor()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Check"));
		return;
	}

	if (!(GetAttachParentActor()->GetRootComponent())) { return; }
	PhysicsConstraint->SetConstrainedComponents(
		Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()),
		NAME_None,
		Cast<UPrimitiveComponent>(Axel),
		NAME_None
	);

	AxelWheelConstraint->SetConstrainedComponents(
		Cast<UPrimitiveComponent>(Axel),
		NAME_None,
		Cast<UPrimitiveComponent>(Wheel),
		NAME_None
	);
}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	LocalForceMagnitude += ForceMagnitude;
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics) 
	{
		LocalForceMagnitude = 0;
	}
}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	return Wheel->AddForce(Axel->GetForwardVector()*LocalForceMagnitude);
}

