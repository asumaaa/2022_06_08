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
//すべての掛け算をまとめた関数
void vecWorldTransform(Vector3* vector_, WorldTransform* worldTransform_);

//WorldTransform二つの長さを返す
float length(WorldTransform worldTransform1, WorldTransform worldTransform2);
//WorldTransform二つのベクトルの正規化
float VecGetX(WorldTransform worldTransform1, WorldTransform worldTransform2);
float VecGetY(WorldTransform worldTransform1, WorldTransform worldTransform2);
float VecGetZ(WorldTransform worldTransform1, WorldTransform worldTransform2);


