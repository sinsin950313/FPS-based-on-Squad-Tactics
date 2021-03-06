// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "Components/SphereComponent.h" 
#include "FPSPawn.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//UE_LOG(LogTemp, Log, TEXT("Projectile Created"));

	USphereComponent* sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Shpere Component"));
	sphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	//sphereComponent->SetNotifyRigidBodyCollision(true);
	sphereComponent->SetSphereRadius(0.1f);
	RootComponent = sphereComponent;

	_projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement Component"));
	//_projectileMovementComponent->InitialSpeed = 10000;
	_projectileMovementComponent->InitialSpeed = 1000;
	_projectileMovementComponent->UpdatedComponent = RootComponent;
	AddOwnedComponent(_projectileMovementComponent);

	UStaticMeshComponent* meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComponent->SetupAttachment(RootComponent);
	AddOwnedComponent(meshComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShpereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ShpereMesh.Succeeded())
	{
		meshComponent->SetStaticMesh(ShpereMesh.Object);
	}
	meshComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

	bGenerateOverlapEventsDuringLevelStreaming = true;
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(_countDownTimerHandler, this, &AProjectileActor::EndTime, 3.0f, true);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileActor::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Log, TEXT("Hit %s, %s"), *Hit.Actor->StaticClass()->GetName(), *Hit.Actor->GetActorLocation().ToString());
	if (Hit.Actor.IsValid())
	{
		Hit.Actor->TakeDamage(10.0f, FDamageEvent(), GetInstigator()->GetController(), this);
	}
	Destroy();
}

void AProjectileActor::EndTime()
{
	//UE_LOG(LogTemp, Log, TEXT("ProjectTile Time Over"));
	Destroy();
}

void AProjectileActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	AFPSPawn* pawn = Cast<AFPSPawn>(OtherActor);
	if (pawn != nullptr)
	{
		pawn->MoraleAttack(GetInstigator(), _moraleDamage);
	}
}
