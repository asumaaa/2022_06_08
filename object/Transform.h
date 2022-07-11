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
//���ׂĂ̊|���Z���܂Ƃ߂��֐�
void vecWorldTransform(Vector3* vector_, WorldTransform* worldTransform_);

//WorldTransform��̒�����Ԃ�
float length(WorldTransform worldTransform1, WorldTransform worldTransform2);
//WorldTransform��̃x�N�g���̐��K��
float VecGetX(WorldTransform worldTransform1, WorldTransform worldTransform2);
float VecGetY(WorldTransform worldTransform1, WorldTransform worldTransform2);
float VecGetZ(WorldTransform worldTransform1, WorldTransform worldTransform2);

