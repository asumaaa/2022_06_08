#include "Vector3.h"
#include "Matrix4.h"
#include <d3d12.h>
#include "WorldTransform.h"

//WorldTransform�̊g��k���̊֐�
void worldTransformScale(WorldTransform* worldTransform_, float x, float y, float z);

//WorldTransform�̕��s�ړ��̊֐�
void worldTransformMove(WorldTransform* worldTransform_, float x, float y, float z);

//WorldTransform�̉�]�̊֐�
void worldTransformRole(WorldTransform* worldTransform_, float x, float y, float z);

//WorldTransform�̃X�P�[�����O�A��]�A���s�ړ����������s����v�Z����
void worldTransformUpdate(WorldTransform* worldTransform_);


//matWorld_�ɃZ�b�g
void worldTransformScaleSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_�ɃZ�b�g
void worldTransformTransrationSet(WorldTransform* worldTransform_, float x, float y, float z);

//matWorld_�ɃZ�b�g
void worldTransformRoleSet(WorldTransform* worldTransform_, float x, float y, float z);