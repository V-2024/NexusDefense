
#include "Weapon/NDBaseWeapon.h"

ANDBaseWeapon::ANDBaseWeapon()
{
    SkeletalMesh =
        CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
    SkeletalMesh->SetupAttachment(GetRootComponent());
}
