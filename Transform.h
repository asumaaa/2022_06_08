#include "Vector3.h"
#include "Matrix4.h"
#include <d3d12.h>
#include "WorldTransform.h"


//WorldTransform�̍X�V
void worldTransformUpdate(WorldTransform* worldTransform_);


//WorldTransform�̂ƃx�N�g���̊|���Z
void worldTransformScale(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformMove(Vector3* vector_, WorldTransform* worldTransform_);
void worldTransformRoll(Vector3* vector_,WorldTransform* worldTransform_);
//WorldTransform���ׂĂƃx�N�g���̊|���Z
void vecWorldTransform(Vector3* vector_, WorldTransform* worldTransform_);



//matWorld_�ɃZ�b�g
void worldTransformScaleSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_�ɃZ�b�g
void worldTransformTransrationSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_�ɃZ�b�g
void worldTransformRoleSet(WorldTransform* worldTransform_, float x, float y, float z);