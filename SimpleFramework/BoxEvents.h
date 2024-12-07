#pragma once

struct CollisionInfo;

class Box;
class Poly;

bool BoxToBox(Box& boxA, Box& boxB, CollisionInfo& info);
bool BoxToPoly(Box& box, Poly& poly, CollisionInfo& info);
