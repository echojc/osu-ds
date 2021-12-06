#include "DifficultyManager.h"

u32 DifficultyManager::preemptTime[] = {1800, 1680, 1560, 1440, 1320, 1200, 1050, 900, 750, 600, 450};
//u32 DifficultyManager::circleSize[] = {100, 92, 84, 76, 68, 60, 52, 44, 36, 28, 20};
u32 DifficultyManager::circleSize[] = {100, 92, 84, 76, 68, 60, 52, 52, 52, 52, 52};
//u32 DifficultyManager::circleSize[] = {120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20};
u32 DifficultyManager::hitWindow300[] = {80, 74, 68, 62, 56, 50, 44, 38, 32, 26, 20};
u32 DifficultyManager::hitWindow100[] = {140, 132, 124, 116, 108, 100, 92, 84, 76, 68, 60};
u32 DifficultyManager::hitWindow50[] = {200, 190, 180, 170, 160, 150, 140, 130, 120, 110, 100};
u32 DifficultyManager::spinnerTime[] = {525, 480, 435, 390, 345, 300, 270, 240, 210, 180, 150};
s32 DifficultyManager::missHpDrain[] = {-10, -18, -26, -34, -42, -50, -56, -62, -68, -74, -80};

u8 DifficultyManager::DifficultyHpDrain = 5;
u8 DifficultyManager::DifficultyCircleSize = 5;
u8 DifficultyManager::DifficultyOverall = 5;
float DifficultyManager::SliderMultiplier = 1.0;
float DifficultyManager::SliderTickRate = 1.0;
float DifficultyManager::DifficultyHpDrainRate = 1.0;
u8 DifficultyManager::DifficultyPeppyStars = 3;
float DifficultyManager::DifficultyEyupStars = 3.0;

