// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Gun.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

    UE_LOG(LogTemp, Warning, TEXT("Gun BeginPlay Called"));
    InitializeBulletPool();
}

void AGun::InitializeBulletPool()
{
    UE_LOG(LogTemp, Warning, TEXT("Initializing Bullet Pool"));

    if (!BulletClass)
    {
        UE_LOG(LogTemp, Error, TEXT("BulletClass is not set in BP_Gun"));
        return;
    }

    if (!GetWorld())
    {
        UE_LOG(LogTemp, Error, TEXT("World is null"));
        return;
    }

	if (!BulletClass) return;

	BulletPool = NewObject<UNDObjectPoolManager>(GetWorld()->GetGameInstance());
	if (BulletPool)
	{
        UE_LOG(LogTemp, Warning, TEXT("BulletPool created successfully"));
        BulletPool->Initialize<ANDBullet>(GetWorld(), BulletClass, PoolSize);
        UE_LOG(LogTemp, Log, TEXT("Bullet pool initialized with size: %d"), PoolSize);
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("BulletPool already exists"));
    }
}

void AGun::PullTrigger()
{
    if (bAutomatic)
    {
        StartFiring();
    }
    else
    {
        Fire();
    }
}

void AGun::ReleaseTrigger()
{
    if (bAutomatic)
    {
        StopFiring();
    }
}

void AGun::StartFiring()
{
    GetWorld()->GetTimerManager().SetTimer(
        FireRateTimerHandle,
        this,
        &AGun::Fire,
        FireRate,
        true,
        0.0f
    );
}

void AGun::StopFiring()
{
    GetWorld()->GetTimerManager().ClearTimer(FireRateTimerHandle);
}

void AGun::Fire()
{
    if (!BulletPool || !bCanFire) return;

    // ī�޶� ��ġ�� ȸ���� ��������
    FVector CameraLocation;
    FRotator CameraRotation;
    GetCameraViewPoint(CameraLocation, CameraRotation);

    // �Ѿ� ���� ��ġ�� �ѱ� ��ġ ���
    FVector SpawnLocation = GetMuzzleLocation();

    // �߻� ������ ī�޶� ���� ���
    FRotator SpawnRotation = CameraRotation;

    if (ANDBullet* Bullet = BulletPool->GetPooledObject<ANDBullet>(SpawnLocation, SpawnRotation))
    {
        // ī�޶� �������� �߻�
        Bullet->FireInDirection(GetAdjustedAimDirection());
    }
}

void AGun::GetCameraViewPoint(FVector& Location, FRotator& Rotation) const
{
    AController* OwnerController = GetOwnerController();
    if (OwnerController)
    {
        // ī�޶� ��ġ�� ȸ���� ��������
        OwnerController->GetPlayerViewPoint(Location, Rotation);
    }
}

AController* AGun::GetOwnerController() const
{
    APawn* OwnerPawn = Cast<APawn>(GetOwner());
    if (OwnerPawn)
    {
        return OwnerPawn->GetController();
    }
    return nullptr;
}

FVector AGun::GetAdjustedAimDirection() const
{
    FVector Location;
    FRotator Rotation;
    GetCameraViewPoint(Location, Rotation);

    // ī�޶��� ���� ���͸� ����Ͽ� �߻� ���� ����
    return Rotation.Vector();
}

FVector AGun::GetMuzzleLocation() const
{
    if (Mesh && Mesh->DoesSocketExist(MuzzleSocketName))
    {
        return Mesh->GetSocketLocation(MuzzleSocketName);
    }
    return GetActorLocation() + GetActorForwardVector() * 100.0f;
}

FRotator AGun::GetMuzzleRotation() const
{
    if (Mesh && Mesh->DoesSocketExist(MuzzleSocketName))
    {
        return Mesh->GetSocketRotation(MuzzleSocketName);
    }
    return GetActorRotation();
}
