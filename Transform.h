#include "Vector3.h"
#include "Matrix4.h"
#include <d3d12.h>
#include "WorldTransform.h"


//WorldTransformの更新
void worldTransformUpdate(WorldTransform* worldTransform_);


//WorldTransformのとベクトルの掛け算
void worldTransformScale(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformMove(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformRoll(Vector3* vector_,WorldTransform* worldTransform_);
//WorldTransformすべてとベクトルの掛け算
void vecWorldTransform(Vector3* vector_, WorldTransform* worldTransform_);



//matWorld_にセット
void worldTransformScaleSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_にセット
void worldTransformTransrationSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_にセット
void worldTransformRoleSet(WorldTransform* worldTransform_, float x, float y, float z);