// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Not required ot add pointer protection in constructor
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	ProjectileMovementComponent->bAutoActivate = false;

	//setting up projectile collision mesh and default values
	ProjectileCollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(ProjectileCollisionMesh);
	ProjectileCollisionMesh->SetNotifyRigidBodyCollision(true);
	ProjectileCollisionMesh->SetVisibility(true);
	
	//setting up projectile launch blast and default values
	ProjectileLaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	ProjectileLaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	//setting up projectile impact landscape blast and default values
	ProjectileImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ProjectileImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ProjectileImpactBlast->bAutoActivate = false;

	//setting up explosion force upon projectile impact and default values
	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileCollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
}

void AProjectile::LaunchProjectile(float Speed)
{
	//setting up the velocity vector for output projectile which has same direction as barrel
	ProjectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	//activates the velocity of a projectile
	ProjectileMovementComponent->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//deactivate launch blast
	ProjectileLaunchBlast->Deactivate();
	//activate impact collision blast
	ProjectileImpactBlast->Activate();
	//providing impulse to proximity object
	ExplosionForce->FireImpulse();
}
