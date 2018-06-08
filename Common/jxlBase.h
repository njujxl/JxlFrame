/****************************************************************************************
*@Copyrights  2008，中兴软创（南京）计算机有限公司 开发部 CCB项目--C++框架组
*@                   All rights reserved.
*@Name：        mdbBase.h
*@Description： Base64编码
*@Author:       jiang.xiaolong
*@Date：        2017年11月17日
*@History:
******************************************************************************************/
#ifndef __MDB_BASE_H__
#define __MDB_BASE_H__

class Base
{
public:
    static bool IsBase64 (const unsigned char c);
    static void EncodeInit();
    static inline void EncodeAddapt (const char* pInput,const unsigned int iBordWidth,unsigned char* pOutput, unsigned int & iOutLen);
    static int Base64Encode (const char * pInput, const unsigned int iInputLen, unsigned char * pOutput, unsigned int & iOutLen);
    static void DecodeInit();
    static inline void DecodeAddapt (const unsigned char* pInput,const unsigned int iPaddingNum, char* pOutput, unsigned int & iOutLen);
    static int Base64Decode (const unsigned char * pInput, const unsigned int iInputLen, char * pOutput, unsigned int & iOutLen) ;
};

#endif

