#pragma once  
#include <raylib.h>
#include <raymath.h>  


struct aabb
{ 
   aabb(const Vector2& center, const Vector2& size) :
       center(center),  
       size(size) {}  

   Vector2 extents() const { return { size.x * 0.5f, size.y * 0.5f }; }  
   Vector2 min() const { Vector2 e = extents(); return { center.x - e.x, center.y - e.y }; }  
   Vector2 max() const { Vector2 e = extents(); return { center.x + e.x, center.y + e.y }; }  
   

private:
   Vector2 center;
   Vector2 size;
};
