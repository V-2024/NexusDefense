// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Gun.h"
#include "Ammo/NDBullet.h"
#include "Kismet/GameplayStatics.h"

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
    FTimerHandle InitTimerHandle;
    GetWorld()->GetTimerManager().SetTimer(
        InitTimerHandle,
        [this]()
        {
            InitializeBulletPool();
        },
        0.1f,
        false
    );
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		BulletPool->CreatePool(GetWorld(), BulletClass, PoolSize);
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to create BulletPool"));
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

void AGun::StartFiring()
{
	GetWorldTimerManager().SetTimer(
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
	GetWorldTimerManager().ClearTimer(FireRateTimerHandle);
}

void AGun::Fire()
{
    UE_LOG(LogTemp, Warning, TEXT("Fire Called")); // 발사 함수 호출 확인

    if (!BulletPool)
    {
        UE_LOG(LogTemp, Error, TEXT("BulletPool is null")); // 풀이 null인지 확인
        return;
    }

    if (!BulletClass)
    {
        UE_LOG(LogTemp, Error, TEXT("BulletClass is not set")); // 총알 클래스가 설정되었는지 확인
        return;
    }

    FVector MuzzleLocation = GetMuzzleLocation();
    FRotator MuzzleRotation = GetMuzzleRotation();

    UE_LOG(LogTemp, Warning, TEXT("Attempting to spawn bullet at location: %s"), *MuzzleLocation.ToString());


    // 총알 발사
    if (AActor* Bullet = BulletPool->GetPooledObject(GetMuzzleLocation(), GetMuzzleRotation()))
    {
        if (ANDBullet* BulletActor = Cast<ANDBullet>(Bullet))
        {
            BulletActor->FireInDirection(GetMuzzleRotation().Vector());
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to get bullet from pool"));
    }

    // 이펙트 재생
    if (MuzzleFlash)
    {
        UGameplayStatics::SpawnEmitterAttached(
            MuzzleFlash,
            Mesh,
            MuzzleSocketName
        );
    }

    // 사운드 재생
    if (FireSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            this,
            FireSound,
            GetMuzzleLocation()
        );
    }

    // 발사 딜레이 설정 (반자동의 경우)
    if (!bAutomatic)
    {
        bCanFire = false;
        GetWorldTimerManager().SetTimer(
            FireRateTimerHandle,
            [this]() { bCanFire = true; },
            FireRate,
            false
        );
    }
}

FVector AGun::GetMuzzleLocation() const
{
    if (Mesh && Mesh->DoesSocketExist(MuzzleSocketName))
    {
        return Mesh->GetSocketLocation(MuzzleSocketName);
    }
    return GetActorLocation();
}

FRotator AGun::GetMuzzleRotation() const
{
    if (Mesh && Mesh->DoesSocketExist(MuzzleSocketName))
    {
        return Mesh->GetSocketRotation(MuzzleSocketName);
    }
    return GetActorRotation();
}
