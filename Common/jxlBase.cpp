#include <stdio.h>
#include <stdlib.h>
#include "jxlBase.h"
#include "mdbStruct.h"
#include "TThreadLog.h"
#include "mdbErr.h"

const unsigned char BASE64_CHARSET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const unsigned char BASE64_PADDING = '=';

static unsigned short BASE64_W_CHARSET[1<<12];

static unsigned int BASE64_CHARPOS[1<<8];
static unsigned char BASE64_DECODE_CHARSET[3][1<<16];

static bool bInitEncode = false;
static bool bInitDecode = false;

static bool bIsBigEnd = false;

bool Base::IsBase64 (const unsigned char c)
{
    DecodeInit();
    return (BASE64_CHARPOS[ (unsigned int)c] != 256);
}

void Base::EncodeInit()
{
    if (!bInitEncode)
    {
        unsigned int uiData = 0x12345678;
        if (* (unsigned char*) (&uiData) == 0x12)
        {
            bIsBigEnd = true;
            TADD_NORMAL ("Big-end server.");
        }
        else
        {
            TADD_NORMAL ("Little-end server.");
        }
        //初始化12bit对照表
        for (unsigned int i=0; i< (1<<12); ++i)
        {
            if (bIsBigEnd)
            {
                BASE64_W_CHARSET[i]= (unsigned short) ((BASE64_CHARSET[i>>6] <<8) | BASE64_CHARSET[i & 0x3F]);
            }
            else
            {
                BASE64_W_CHARSET[i]= (unsigned short) (BASE64_CHARSET[i>>6] | (BASE64_CHARSET[i & 0x3F] << 8));
            }
        }

        bInitEncode=true;
    }
}

inline void Base::EncodeAddapt (const char* pInput,const unsigned int iBordWidth,unsigned char* pOutput, unsigned int & iOutLen)
{
#ifdef OS_LINUX
    int iInput0 = 0;
    int iInput1 = 0;
    unsigned int iOutput0=0;
    unsigned int iOutput1=0;
    unsigned int iOutput2=0;
    if (iBordWidth==1)
    {
        iInput0 = pInput[0];
        iOutput0=BASE64_CHARSET[ (iInput0 & 0xFF) >> 2];
        iOutput1=BASE64_CHARSET[ ((iInput0 & 0xFF) << 4) & 0x3F];
        if (bIsBigEnd)
        {
            * (unsigned long*) (&pOutput[0])= (iOutput0<<24) | (iOutput1<<16) | ((BASE64_PADDING<<8) | (BASE64_PADDING));
        }
        else
        {
            * (unsigned long*) (&pOutput[0])=iOutput0 | (iOutput1<<8) | ((BASE64_PADDING<<16) | (BASE64_PADDING<<24));
        }
    }
    else if (iBordWidth==2)
    {
        iInput0 = pInput[0];
        iInput1 = pInput[1];
        iOutput0=BASE64_CHARSET[ (iInput0 & 0xFF) >> 2];
        iOutput1=BASE64_CHARSET[ (((iInput0 & 0xFF) << 4) | ((iInput1 & 0xFF) >> 4)) & 0x3F];
        iOutput2=BASE64_CHARSET[ ((iInput1 & 0xFF) << 2) & 0x3F];
        if (bIsBigEnd)
        {
            * (unsigned long*) (&pOutput[0])= (iOutput0<<24) | (iOutput1<<16) | (iOutput2<<8) | (BASE64_PADDING);
        }
        else
        {
            * (unsigned long*) (&pOutput[0])=iOutput0 | (iOutput1<<8) | (iOutput2<<16) | (BASE64_PADDING<<24);
        }
    }
#else
    if (iBordWidth==1)
    {
        pOutput[0] = BASE64_CHARSET[pInput[0]>>2];
        pOutput[1] = BASE64_CHARSET[ (pInput[0]&0x03)<<4];
        pOutput[2] = BASE64_PADDING;
        pOutput[3] = BASE64_PADDING;
    }
    else if (iBordWidth==2)
    {
        pOutput[0] = BASE64_CHARSET[pInput[0]>>2];
        pOutput[1] = BASE64_CHARSET[ (pInput[0]&0x03)<<4 | pInput[1]>>4];
        pOutput[2] = BASE64_CHARSET[ (pInput[1]&0x0F)<<2];
        pOutput[3] = BASE64_PADDING;
    }
#endif
    iOutLen+=4;
}

int Base::Base64Encode (const char * pInput, const unsigned int iInputLen, unsigned char * pOutput, unsigned int & iOutLen)
{
    int iRet = 0;
    EncodeInit();
    TADD_DETAIL ("iInputLen = [%u]", iInputLen);
    for (int i = 0; i<iInputLen; i++)
    {
        TADD_DETAIL ("\n pInput[%d] = [%d][%c]", i, pInput[i]);
    }
    if (NULL == pInput || iInputLen == 0)
    {
        pOutput[0] = '\0';
        iOutLen = 0;
        return iRet;
    }

    unsigned int iRound=iInputLen/3;
    unsigned int iBordWidth = iInputLen - iRound*3;

    int iInput0 = 0;
    int iInput1 = 0;
    int iInput2 = 0;
    unsigned int iOutput01=0;
    unsigned int iOutput23=0;

    unsigned int i=0;
    iOutLen = 0;
    for (i = 0; i<iRound; i++)
    {
#ifdef OS_LINUX
        iInput0 = pInput[i*3];
        iInput1 = pInput[i*3+1];
        iInput2 = pInput[i*3+2];
        iOutput01=BASE64_W_CHARSET[ ((iInput0 & 0xFF)<<4) | ((iInput1 & 0xFF)>>4)];
        iOutput23=BASE64_W_CHARSET[ ((iInput1 & 0x0F)<<8) |  (iInput2 & 0xFF)];
        if (bIsBigEnd)
        {
            * (unsigned long*) (pOutput+i*4)= (iOutput01<<16) | iOutput23;
        }
        else
        {
            * (unsigned long*) (pOutput+i*4)=iOutput01 | (iOutput23<<16);
        }
#else
        pOutput[i*4+0] = BASE64_CHARSET[pInput[i*3]>>2];
        pOutput[i*4+1] = BASE64_CHARSET[ (pInput[i*3]&0x03)<<4 | pInput[i*3+1]>>4];
        pOutput[i*4+2] = BASE64_CHARSET[ (pInput[i*3+1]&0x0F)<<2 | pInput[i*3+2]>>6];
        pOutput[i*4+3] = BASE64_CHARSET[pInput[i*3+2]&0x3F];
#endif
        iOutLen+=4;
    }
    EncodeAddapt (pInput+iRound*3, iBordWidth, pOutput+iOutLen, iOutLen);
    pOutput[iOutLen] = '\0';
    TADD_DETAIL ("pOutput = [%s], iOutLen = [%u]", pOutput, iOutLen);
    for (i = 0; i<iOutLen; i++)
    {
        TADD_DETAIL ("\n pOutput[%d] = [%d][%hhu]", i, pOutput[i]);
    }
    return iRet;
}

void Base::DecodeInit()
{
    if (!bInitDecode)
    {
        unsigned int uiData = 0x12345678;
        if (* (unsigned char*) (&uiData) == 0x12)
        {
            bIsBigEnd = true;
            TADD_NORMAL ("Big-end server.");
        }
        else
        {
            TADD_NORMAL ("Little-end server.");
        }
        for (unsigned int i = 0; i< (1<<8); i++)
        {
            BASE64_CHARPOS[i] = 256;
        }
        for (unsigned int i = 0; i< (1<<6); i++)
        {
            BASE64_CHARPOS[ (unsigned int)BASE64_CHARSET[i]] = i;
        }
        //初始化3个16bit对照表
        unsigned int iPos1 = 0, iPos2 = 0;
        for (unsigned int i=0; i< (1<<16); ++i)
        {
            iPos1 = BASE64_CHARPOS[i>>8];
            iPos2 = BASE64_CHARPOS[i & 0xFF];
            BASE64_DECODE_CHARSET[0][i]= (unsigned char) (((iPos1 & 0x3F)<<2) | ((iPos2 & 0x3F)>>4));
            BASE64_DECODE_CHARSET[1][i]= (unsigned char) (((iPos1 & 0x0F)<<4) | ((iPos2 & 0x3F)>>2));
            BASE64_DECODE_CHARSET[2][i]= (unsigned char) (((iPos1 & 0x03)<<6) | ((iPos2 & 0x3F)));
        }
        bInitDecode=true;
    }
}

inline void Base::DecodeAddapt (const unsigned char* pInput,const unsigned int iPaddingNum, char* pOutput, unsigned int & iOutLen)
{
    int iInput0=0;
    int iInput1=0;
    int iInput2=0;
    if (iPaddingNum==1)
    {
        iInput0=pInput[0];
        iInput1=pInput[1];
        iInput2=pInput[2];
        if (BASE64_CHARPOS[iInput0] != 256 && BASE64_CHARPOS[iInput1] != 256 && BASE64_CHARPOS[iInput2] != 256)
        {
            pOutput[0] = (char) (BASE64_DECODE_CHARSET[0][ (iInput0<<8) | (iInput1)]);
            pOutput[1] = (char) (BASE64_DECODE_CHARSET[1][ (iInput1<<8) | (iInput2)]);
            pOutput[2] = '\0';
            iOutLen+=2;
        }
        else
        {
            TADD_ERROR ("Invalid BASE64 encoded char [%c%c%c].", pInput[0],pInput[1],pInput[2]);
        }
    }
    else if (iPaddingNum==2)
    {
        iInput0=pInput[0];
        iInput1=pInput[1];
        if (BASE64_CHARPOS[iInput0] != 256 && BASE64_CHARPOS[iInput1] != 256)
        {
            pOutput[0] = (char) (BASE64_DECODE_CHARSET[0][ (iInput0<<8) | (iInput1)]);
            pOutput[1] = '\0';
            iOutLen+=1;
        }
        else
        {
            TADD_ERROR ("Invalid BASE64 encoded char [%c%c].", pInput[0],pInput[1]);
        }
    }
}

int Base::Base64Decode (const unsigned char * pInput, const unsigned int iInputLen, char * pOutput, unsigned int & iOutLen)
{
    int iRet = 0;
    DecodeInit();
    TADD_DETAIL ("pInput = [%s], iInputLen = [%u]", pInput, iInputLen);
    for (int i = 0; i<iInputLen; i++)
    {
        TADD_DETAIL ("\n pInput[%d] = [%d][%hhu]", i, pInput[i]);
    }
    if (NULL == pInput || iInputLen == 0)
    {
        pOutput[0] = '\0';
        iOutLen = 0;
        return iRet;
    }
    unsigned int iPaddingNum = 0;
    if (pInput[iInputLen-1] == BASE64_PADDING)
    {
        iPaddingNum++;
        if (pInput[iInputLen-2] == BASE64_PADDING) iPaddingNum++;
    }

    unsigned int iRound= (iInputLen-iPaddingNum)/4;
    unsigned int iInput0=0;
    unsigned int iInput1=0;
    unsigned int iInput2=0;
    unsigned int iInput3=0;
    unsigned int i=0;
    iOutLen = 0;
    for (i = 0; i<iRound; i++)
    {
        iInput0=pInput[i*4];
        iInput1=pInput[i*4+1];
        iInput2=pInput[i*4+2];
        iInput3=pInput[i*4+3];
        if (BASE64_CHARPOS[iInput0] != 256 && BASE64_CHARPOS[iInput1] != 256 && BASE64_CHARPOS[iInput2] != 256 && BASE64_CHARPOS[iInput3] != 256)
        {
            pOutput[i*3] = (char) (BASE64_DECODE_CHARSET[0][ (iInput0<<8) | (iInput1)]);
            pOutput[i*3+1] = (char) (BASE64_DECODE_CHARSET[1][ (iInput1<<8) | (iInput2)]);
            pOutput[i*3+2] = (char) (BASE64_DECODE_CHARSET[2][ (iInput2<<8) | (iInput3)]);
            iOutLen+=3;
        }
        else
        {
            TADD_ERROR ("Invalid BASE64 encoded char [%c%c%c%c].", pInput[i*4],pInput[i*4+1],pInput[i*4+2],pInput[i*4+3]);
            pOutput[0] = '\0';
            iRet = -1;
            return iRet;
        }
    }
    DecodeAddapt (pInput+iRound*4, iPaddingNum, pOutput+iOutLen, iOutLen);
    pOutput[iOutLen] = '\0';
    TADD_DETAIL ("iOutLen = [%u]", iOutLen);
    for (i = 0; i<iOutLen; i++)
    {
        TADD_DETAIL ("\n pOutput[%d] = [%u][%c]", i, pOutput[i]);
    }
    return iRet;
}

