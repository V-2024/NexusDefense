#include "NDSoundManager.h"
#include "NDObjectPoolManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

UNDSoundManager::UNDSoundManager()
{

}

void UNDSoundManager::Initialize(UNDObjectPoolManager* PoolManager)
{
    ObjectPoolManager = PoolManager;
}

void UNDSoundManager::PlaySound(USoundBase* Sound, const FVector& Location, float VolumeMultiplier, float PitchMultiplier)
{
    //if (Sound && ObjectPoolManager)
    //{
    //    UAudioComponent* AudioComponent = Cast<UAudioComponent>(ObjectPoolManager->GetPooledObject(UAudioComponent::StaticClass()));
    //    if (AudioComponent)
    //    {
    //        AudioComponent->SetSound(Sound);
    //        AudioComponent->SetWorldLocation(Location);
    //        AudioComponent->SetVolumeMultiplier(VolumeMultiplier);
    //        AudioComponent->SetPitchMultiplier(PitchMultiplier);
    //        AudioComponent->Play();
    //        ActiveSounds.Add(AudioComponent);
    //    }
    //}
}

void UNDSoundManager::StopSound(UAudioComponent* AudioComponent)
{
    if (AudioComponent)
    {
        AudioComponent->Stop();
        ActiveSounds.Remove(AudioComponent);
        //ObjectPoolManager->ReturnSoundToPool(AudioComponent);
    }
}

void UNDSoundManager::PlayBackgroundMusic(USoundBase* Music)
{
    if (!BackgroundMusicComponent)
    {
        BackgroundMusicComponent = UGameplayStatics::CreateSound2D(this, Music);
    }

    if (BackgroundMusicComponent)
    {
        BackgroundMusicComponent->SetSound(Music);
        BackgroundMusicComponent->Play();
    }
}

void UNDSoundManager::StopBackgroundMusic()
{
    if (BackgroundMusicComponent)
    {
        BackgroundMusicComponent->Stop();
    }
}

void UNDSoundManager::UpdateActiveSounds(float DeltaTime)
{
    for (int32 i = ActiveSounds.Num() - 1; i >= 0; --i)
    {
        if (ActiveSounds[i] && !ActiveSounds[i]->IsPlaying())
        {
            StopSound(ActiveSounds[i]);
        }
    }
}