#include "Constants.h"

float Environment::s_Gravity = 0.0f;
float Environment::s_Elasticity = 1.0f;
int Environment::s_Cores = 8;
int Environment::s_Iterations = 8; // Total physics iterations 
									// Thread iterations = s_Iterations / s_Cores