#ifndef _COMMON_UI_H_  
#define _COMMON_UI_H_ 

#ifndef LWA_COLORKEY
#define LWA_COLORKEY 0x01
#endif
#ifndef LWA_ALPHA
#define LWA_ALPHA 0x02
#endif

// dwFlags = LWA_ALPHA ͸���� bAlpha: ��0����������͸��, =255 ��ȫ��͸�� 
// dwFlags = LWA_COLORKEY ָ����ɫ crKey ͸��
BOOL SetWindowAttributes(HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags);
void DealMSG();

#endif