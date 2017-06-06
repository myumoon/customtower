//=============================================================================
/*!	@file	projectDef.h

	@brief	�v���W�F�N�g�^�C�v�萔�Q

	@author	��� ���V��
	@date	2011/11/15
	@todo	�Ȃ�
	@bug	�Ȃ�
*/
//=============================================================================

#ifndef __PROJECTDEF_H__
#define	__PROJECTDEF_H__


//===========================================================================
/*!
	�v���W�F�N�g�^�C�v

	�e��v���W�F�N�g�^�C�v�̐ݒ�ɉ����ăR�[�h���ω�����B
	�^�C�v��p�����͕K���v���W�F�N�g�^�C�v�Ŕ��肷�鎖
*/
//===========================================================================
enum
{
	PROJECT_TYPE_WIN32,		//!<	32bit�E�B���h�E�Y
	PROJECT_TYPE_WIN64,		//!<	64bit�E�B���h�E�Y
	PROJECT_TYPE_PS2,		//!<	PlayStation2
	PROJECT_TYPE_PS3,		//!<	PlayStation3
	PROJECT_TYPE_PSP,		//!<	PlayStationPortable
	PROJECT_TYPE_DS,		//!<	NintendoDS
	PROJECT_TYPE_WII,		//!<	NintendoWii
	PROJECT_TYPE_XBOX,		//!<	XBOX
	PROJECT_TYPE_XBOX360,	//!<	XBOX360
};



//===========================================================================
/*!
	�X���b�h�^�C�v

	�A�v���P�[�V�����̃X���b�h�^�C�v
*/
//===========================================================================
enum
{
	THREAD_TYPE_SINGLE,		//!<	�V���O���X���b�h
	THREAD_TYPE_MULTI,		//!<	�}���`�X���b�h
};


//===========================================================================
/*!
	�O���t�B�b�N�^�C�v

	PS2���̃R���V���[�}�ł̓v���W�F�N�g�^�C�v�łقڂ����邪�A
 	OpenGL��DirectX�̗l�ȃ��C�u�����Ⴂ�����������ׂ̈ɕ����Ă���
*/
//===========================================================================
#define	GRAPHICS_TYPE_OPENGL		0	//!<	OpenGL
#define	GRAPHICS_TYPE_DIRECTX9		1	//!<	DirectX
#define GRAPHICS_TYPE_SDL			2	//!<	SDL
#define GRAPHICS_TYPE_SDL_OPENGL	3	//!<	SDL+OpenGL
#define	GRAPHICS_TYPE_PS2			4	//!<	PlayStation2
#define	GRAPHICS_TYPE_PS3			5	//!<	PlayStation3
#define	GRAPHICS_TYPE_PSP			6	//!<	PlayStationPortable
#define	GRAPHICS_TYPE_DS			7	//!<	NintendoDS
#define	GRAPHICS_TYPE_WII			8	//!<	NintendoWii
#define	GRAPHICS_TYPE_XBOX			9	//!<	XBOX
#define	GRAPHICS_TYPE_XBOX360		10	//!<	XBOX360



//===========================================================================
/*!
	���C�Z���X�G���A

	�^�[�Q�b�g�ƂȂ鍑�ɂ���Đݒ肪�قȂ镔��������̂ŁA
	������ς��邾���ŃV�X�e�����K������悤�ɂ���
	��Ƀp�b�h������肩�H
*/
//===========================================================================
enum
{
	LICENSE_AREA_JAPAN,	//<!	���{

	LICENSE_AREA_USA,	//<!	�A�����J
	LICENSE_AREA_EURO,	//<!	���B

	LICENSE_AREA_USEU,	//<!	�k�āE���B
};


//===========================================================================
/*
	�t���[�����[�g

	��{�t���[�����[�g�l
*/
//===========================================================================
#define	FRAME_FULL	1	//!<	�t���t���[��
#define	FRAME_60	60	//!<	60�t���[��
#define	FRAME_30	30	//!<	30�t���[��
#define	FRAME_15	15	//!<	15�t���[��




#endif	//	__PROJECTDEF_H__