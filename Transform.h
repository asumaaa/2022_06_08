#include "Vector3.h"
#include "Matrix4.h"
#include <d3d12.h>
#include "WorldTransform.h"

//WorldTransformの拡大縮小の関数
void worldTransformScale(WorldTransform* worldTransform_, float x, float y, float z);

//WorldTransformの平行移動の関数
void worldTransformMove(WorldTransform* worldTransform_, float x, float y, float z);

//WorldTransformの回転の関数
void worldTransformRole(WorldTransform* worldTransform_, float x, float y, float z);


//matWorld_にセット
void worldTransformScaleSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_にセット
void worldTransformTransrationSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_にセット
void worldTransformRoleSet(WorldTransform* worldTransform_, float x, float y, float z);