// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera/EveCameraComponent.h"

void UEveCameraComponent::StartCameraShake(float Intensity, float Duration)
{
	// // Create a camera shake instance
	// UCameraShake* CameraShake = NewObject<UCameraShake>();
	// if (CameraShake)
	// {
	// 	// Set camera shake parameters
	// 	CameraShake->OscillationDuration = Duration;
	// 	CameraShake->OscillationBlendInTime = 0.1f; // Blend in time
	// 	CameraShake->OscillationBlendOutTime = Duration - 0.1f; // Blend out time
	// 	CameraShake->RotOscillation.Pitch.Amplitude = Intensity;
	// 	CameraShake->RotOscillation.Yaw.Amplitude = Intensity;
	//
	// 	// Apply camera shake to the camera component
	// 	this->AddCameraShake(CameraShake);
	// }
}

void UEveCameraComponent::StopCameraShake()
{
	// CameraComponent->SetWorldRotation(OriginalCameraRotation);
}
