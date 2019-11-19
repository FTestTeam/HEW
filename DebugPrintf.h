/*--------------------------------------------------------

	DebugPrintf.h������Ďg����
	�쐬��31�N4��24��
	����Ҍ܏\����

--------------------------------------------------------*/

//========================================================

#ifndef _DEBUG_PRINTF_H_
#define _DEBUG_PRINTF_H_

#include <windows.h>
#include <stdio.h>


//�f�o�b�O�p��printf...VS�̏o�̓E�B���h�E�ɏo�͂����
inline void DebugPrintf(const char* pFormat, ...) 
{
//����ȕ��ɏ�����Release�r���h���̓r���h����Ȃ��͈͂��w��ł���
#if defined(_DEBUG) || defined(DEBUG)
	va_list argp;
	char buf[256];
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp);
	va_end(argp);
	OutputDebugStringA(buf);
#endif //_DEBUG || DEBUG
}

#endif // _DEBUG_PRINTF_H_